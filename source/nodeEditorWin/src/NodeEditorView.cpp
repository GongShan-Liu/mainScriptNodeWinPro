#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtCore/QRectF>
#include <QtCore/QPointF>

#include <QDebug>

#include "nodeEditorWin/include/NodeEditorView.h"

NodeEditorView::NodeEditorView(QWidget *parent) : QGraphicsView(parent),
                                                  _deleteSelectionAction(nullptr),
                                                  _clickPos(QPointF(0, 0))
{
    setBackgroundBrush(QColor(47, 47, 47));
    // setDragMode(QGraphicsView::ScrollHandDrag);  // 设置拖拽鼠标形状为手型
    setDragMode(QGraphicsView::NoDrag); // 设置不能拖拽

    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setCacheMode(QGraphicsView::CacheBackground);

    // 创建scene类
    _scene = std::make_shared<NodeEditScene>(nullptr);
    setScene(_scene.get());
    _scene->setSceneRect(this->rect());
}

NodeEditorView::~NodeEditorView()
{
    if (_deleteSelectionAction != nullptr)
    {
        delete _deleteSelectionAction;
        _deleteSelectionAction = nullptr;
    }
}

void NodeEditorView::setScene(QGraphicsScene *scene)
{
    QGraphicsView::setScene(scene);

    // setup actions
    // setup actions

    // 设置delete键功能
    delete _deleteSelectionAction;
    _deleteSelectionAction = new QAction(QStringLiteral("Delete Selection Node"), this);
    _deleteSelectionAction->setShortcut(Qt::Key_Delete);
    connect(_deleteSelectionAction, &QAction::triggered, this, [&] { _scene->deleteSelectNode(); });
    addAction(_deleteSelectionAction);
}

void NodeEditorView::scaleUp()
{
    double const step = 1.1;
    double const factor = std::pow(step, 1.0);

    QTransform t = transform();

    if (t.m11() > 2.0)
        return;

    // 视图缩小
    scale(factor, factor);
}

void NodeEditorView::scaleDown()
{
    double const step = 1.1;
    double const factor = std::pow(step, -1.0);

    // 视图放大
    scale(factor, factor);
}

void NodeEditorView::contextMenuEvent(QContextMenuEvent *event)
{
    if (itemAt(event->pos()))
    {
        QGraphicsView::contextMenuEvent(event);
        return;
    }

    // 在鼠标右键坐标创建上下文菜单
    QMenu viewMenu;
    QAction *createNodeAction = viewMenu.addAction("Create Node");
    // QAction *deleteSlNodeAction = viewMenu.addAction("Delete Select Node");
    QAction *deleteAllNodeAction = viewMenu.addAction("Delete All Node");

    // 获取view坐标在scene的坐标
    QPointF posView = this->mapToScene(event->pos());

    // 创建节点命令连接
    connect(createNodeAction, &QAction::triggered, this,
            [&] {
                QString nodeName = "node_";
                nodeName.append(std::to_string(_scene->getNodeNumber()).c_str());
                _scene->createNode(nodeName, posView.x(), posView.y());
            });

    // connect(deleteSlNodeAction, &QAction::triggered, this, [&] { _scene->deleteSelectNode(); });

    viewMenu.exec(event->globalPos());
}

void NodeEditorView::wheelEvent(QWheelEvent *event)
{
    QPoint delta = event->angleDelta();

    if (delta.y() == 0)
    {
        event->ignore();
        return;
    }

    double const d = delta.y() / std::abs(delta.y());

    // 鼠标向下滚动放大，鼠标向上滚动缩小
    if (d > 0.0)
        scaleUp();
    else
        scaleDown();
}

void NodeEditorView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
    if (scene()->mouseGrabberItem() == nullptr && event->button() == Qt::MidButton)
    {
        // setDragMode(QGraphicsView::ScrollHandDrag);
        viewport()->setCursor(Qt::SizeAllCursor); // 设置鼠标形状为十字型
        _clickPos = mapToScene(event->pos());
    }

    if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier)
    {
        setDragMode(QGraphicsView::RubberBandDrag); // 鼠标左键+ctrl建实现 设置拖拽为框选
    }

    QGraphicsView::mousePressEvent(event);
}

void NodeEditorView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    viewport()->setCursor(Qt::ArrowCursor); // 设置鼠标形状为标准型
    setDragMode(QGraphicsView::NoDrag);     // 设置不能拖拽框选
}

void NodeEditorView::mouseMoveEvent(QMouseEvent *event)
{

    if (scene()->mouseGrabberItem() == nullptr && event->buttons() == Qt::MidButton)
    {
        // 点击鼠标中键实现视图位移，如果shift键按下则无效
        if ((event->modifiers() & Qt::ShiftModifier) == 0)
        {
            QPointF difference = _clickPos - mapToScene(event->pos());
            setSceneRect(sceneRect().translated(difference.x(), difference.y()));
        }
    }

    QGraphicsView::mouseMoveEvent(event);
}

void NodeEditorView::showEvent(QShowEvent *event)
{
    _scene->setSceneRect(this->rect());
    QGraphicsView::showEvent(event);
}

void NodeEditorView::drawBackground(QPainter *painter, const QRectF &r)
{
    QGraphicsView::drawBackground(painter, r);

    // 绘制网格
    auto drawGrid = [&](double gridstep) {
        QRect winRect = rect();
        QPointF tl = mapToScene(winRect.topLeft());
        QPointF br = mapToScene(winRect.bottomRight());

        double left = std::floor(tl.x() / gridstep - 1.0);
        double bottom = std::floor(tl.y() / gridstep - 1.0);
        double right = std::floor(br.x() / gridstep + 1.0);
        double top = std::floor(br.y() / gridstep + 1.0);

        // vertical lines
        for (int l = int(left); l <= int(right); l++)
        {
            QLineF line(l * gridstep, bottom * gridstep,
                        l * gridstep, top * gridstep);

            painter->drawLine(line);
        }

        // horizontal lines
        for (int b = int(bottom); b <= int(top); b++)
        {
            QLineF line(left * gridstep, b * gridstep,
                        right * gridstep, b * gridstep);

            painter->drawLine(line);
        }
    };

    QColor fineGridColor(30, 30, 30); // 设置网格线的颜色
    QPen pfine(fineGridColor, 1.0);  // 设置网格线的颜色和粗度

    // pfine.setWidth(2.5);  // 设置网格线粗度
    painter->setPen(pfine);
    drawGrid(30); // 设置网格距离

    // QColor fc(30, 30, 30);
    // QPen p(fc, 1.0);

    // p.setWidth(3.0);
    // painter->setPen(p);
    // drawGrid(250);
}

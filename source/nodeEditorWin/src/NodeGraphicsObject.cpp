#include "nodeEditorWin/include/NodeGraphicsObject.h"

#include <QDebug>

// 初始化静态变量
std::set<QString> NodeGraphicsObject::nodeNameSet;
int NodeGraphicsObject::nodeCount = 0;

NodeGraphicsObject::NodeGraphicsObject(QGraphicsScene *scene, const QString &nodeName,
                                       QGraphicsItem *parent, int w, int h) : _scene(scene), _nodeName(nodeName),
                                                                              QGraphicsObject(parent), _w(w), _h(h)
{
    setFlag(QGraphicsItem::ItemDoesntPropagateOpacityToChildren, true); // 设置节点透明不传播到子项
    setFlag(QGraphicsItem::ItemIsMovable, true);                        // 设置节点可移动
    setFlag(QGraphicsItem::ItemIsFocusable, true);                      // 设置节点可使用光标
    setFlag(QGraphicsItem::ItemIsSelectable, true);                     // 设置节点可选择
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);        // 设置节点发送场景的坐标变化
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    // 检查名称是否同名，是->获取新的名称
    if (nodeNameSet.count(_nodeName) == 1)
    {
        _nodeName = getNewNodeName(_nodeName);
    };

    // 创建命名框
    _lineEdit = new NodeLineEditWidget(_nodeName);
    nodeNameSet.insert(_nodeName);

    // 键盘输入完成后检查是否重命名
    QObject::connect(_lineEdit, &NodeLineEditWidget::editingFinished, this, &NodeGraphicsObject::lineEditFinishedCmd);

    // 设置命名框在节点的代理部件
    _ellipseSize = 10;
    _widget = new QGraphicsProxyWidget(this);
    _widget->setWidget(_lineEdit);
    _widget->setPos(5 + (_ellipseSize / 2), -35);
    _widget->setMaximumWidth(150);
    _widget->setMinimumHeight(30);

    _rectWidth = 2;
    _rectColor = QColor(0, 0, 0);

    _rectSelectWidth = 4;
    _rectSelectColor = QColor(0, 255, 0);

    _mainBrushColor = QColor(80, 160, 240);
    _subBrushColor = QColor(0, 255, 10);

    // 创建端口
    _inpPort = new NodePort(this, _ellipseSize, _h / 2, _ellipseSize);
    _outPort = new NodePort(this, _w - _ellipseSize, _h / 2, _ellipseSize, 1);

    // 边界值
    _rect = QRectF(_rectSelectWidth + _ellipseSize,
                   _rectSelectWidth,
                   _w - (_ellipseSize * 2) - (_rectSelectWidth * 2),
                   _h - (_rectSelectWidth * 2));

    // 场景中添加当前节点
    _scene->addItem(this);

    // 节点+1
    nodeCount++;
}

NodeGraphicsObject::~NodeGraphicsObject()
{
    // 节点数据库清除删除的节点和节点-1
    nodeNameSet.erase(_nodeName);
    nodeCount--;

    if (_lineEdit != nullptr)
    {
        delete _lineEdit;
        _lineEdit = nullptr;
    };

    if (_inpPort != nullptr)
    {
        delete _inpPort;
        _inpPort = nullptr;
    }

    if (_outPort != nullptr)
    {
        delete _outPort;
        _outPort = nullptr;
    }
}

void NodeGraphicsObject::drawBoundingRect(QPainter *p, int &penWidth, QColor &penColor, QColor &brushColor)
{

    QPen rectPen = QPen();
    rectPen.setWidth(penWidth);
    rectPen.setColor(penColor);
    p->setPen(rectPen);

    p->setBrush(QBrush(brushColor));
    p->drawRoundedRect(_rect.x(), _rect.y(), _rect.width(), _rect.height(), 10, 10);
}

QRectF NodeGraphicsObject::boundingRect() const
{
    return _rect;
}

void NodeGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    QPen p = painter->pen();
    QBrush b = painter->brush();

    // 设置节点选择和不选择的显示模式
    if (!isSelected())
    {
        qDebug() << this->scenePos();
        this->drawBoundingRect(painter, _rectWidth, _rectColor, _mainBrushColor);
    }
    else
    {
        this->drawBoundingRect(painter, _rectSelectWidth, _rectSelectColor, _mainBrushColor);
    }
}

void NodeGraphicsObject::setNodeName(const QString &name)
{
    // 设置节点的名称，并检查是否重命名
    // 是->：自动重新获取新的名称
    // 否->：更新命名并刷新节点数据库的名称
    if (nodeNameSet.count(name) == 1)
    {
        _nodeName = getNewNodeName(_nodeName);
        nodeNameSet.erase(name);
        nodeNameSet.insert(_nodeName);
    }
    else
    {
        nodeNameSet.erase(_nodeName);
        _nodeName = name;
        nodeNameSet.insert(_nodeName);
    }

    _lineEdit->setText(_nodeName);

    // for (std::set<QString>::iterator it = nodeNameSet.begin(); it != nodeNameSet.end(); it++)
    // {
    //     qDebug() << *it;
    // }
}

QString NodeGraphicsObject::getNodeName(void)
{
    _nodeName = _lineEdit->text();
    return _nodeName;
}

void NodeGraphicsObject::lineEditFinishedCmd(void)
{
    QString &newNodeName = _lineEdit->text();

    //检查名称是否重命名
    // 否->：删去节点数据库中旧的名称，更新新的命名
    // 是->：恢复旧的名称
    if (nodeNameSet.count(newNodeName) == 0)
    {
        nodeNameSet.erase(_nodeName);
        _nodeName = newNodeName;
        nodeNameSet.insert(_nodeName);
        // qDebug() << "change ok\n";
        // for (std::set<QString>::iterator it = nodeNameSet.begin(); it != nodeNameSet.end(); it++)
        // {
        //     qDebug() << *it;
        // }
    }
    else
    {
        if (newNodeName != _nodeName)
        {
            _lineEdit->setText(_nodeName);
            // qDebug() << "recover\n";
            // for (std::set<QString>::iterator it = nodeNameSet.begin(); it != nodeNameSet.end(); it++)
            // {
            //     qDebug() << *it;
            // }
        };
        // qDebug() << "not change";
    }
}

QString NodeGraphicsObject::getNewNodeName(QString &s)
{
    // 获取新的节点名称
    int num = 1;
    QString newNodeName = s;

    // 循环查询输入的名称后缀+数字是否在节点数据库?
    // 是->：继续循环
    // 否->：停止返回名称
    while (true)
    {
        newNodeName.append(std::to_string(num).c_str());
        if (nodeNameSet.count(newNodeName) == 0)
            break;

        if (num == 100000)
        {
            qDebug() << "Not get new nameing of the node.";
            break;
        }

        num++;
    }

    return newNodeName;
}

void NodeGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // 鼠标是左键点击
    if (event->button() == Qt::LeftButton)
    {
        QTransform transform;
        QGraphicsItem *item = _scene->itemAt(event->scenePos(), transform);

        // 如果鼠标位置在端口，则节点设置为无法拖动
        if (item && item->type() == NodePort::Type)
        {
            setFlag(QGraphicsItem::ItemIsMovable, false);
        }
    }
    QGraphicsObject::mousePressEvent(event);
}

void NodeGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // 鼠标为左键释放，设置节点可以拖动
    if (event->button() == Qt::LeftButton)
    {
        setFlag(QGraphicsItem::ItemIsMovable);
    }

    QGraphicsObject::mouseReleaseEvent(event);
}

void NodeGraphicsObject::keyReleaseEvent(QKeyEvent *event)
{
    // 如果键盘释放的是enter键，那么命名框结束输入状态
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        if (_widget->hasFocus())
        {
            _widget->clearFocus();
        }
    }
    QGraphicsObject::keyReleaseEvent(event);
}

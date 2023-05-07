#ifndef NODEGRAPHICSOBJECT_H
#define NODEGRAPHICSOBJECT_H

#include <set>

#include <QtWidgets>

#include "NodeLineEditWidget.h"
#include "NodePort.h"

class NodeGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    // 设置节点的类型编号
    enum
    {
        Type = QGraphicsItem::UserType + 3
    };

    static std::set<QString> nodeNameSet; // 记录所有的节点的名称
    static int nodeCount; // 记录节点的数量

    explicit NodeGraphicsObject(QGraphicsScene *scene, const QString &nodeName,
                                QGraphicsItem *parent = nullptr, int w = 200, int h = 50);
    ~NodeGraphicsObject();

    NodeGraphicsObject(const NodeGraphicsObject &n) = delete;
    NodeGraphicsObject &operator=(const NodeGraphicsObject &n) = delete;

    // 节点的边界
    QRectF boundingRect() const override;

    // 绘制节点的边界
    void drawBoundingRect(QPainter *p, int &penWidth, QColor &penColor, QColor &brushColor);

    // 设置和获取节点的名称
    void setNodeName(const QString &name);
    QString getNodeName(void);

    // 获取节点的输入和输出端口
    inline NodePort *getInpPort() { return _inpPort; }
    inline NodePort *getOutPort() { return _outPort; }

    // 返回名称框的部件指针
    inline NodeLineEditWidget *getLineEdit(void) { return _lineEdit; }

    // 返回节点的类型编号
    inline int type() const { return Type; }

protected:
    // 绘制节点
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    
    // 节点的鼠标点击和鼠标释放事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // 节点的键盘释放事件
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    int _w;
    int _h;
    int _ellipseSize;
    QRectF _rect;

    int _rectWidth;
    QColor _rectColor;

    int _rectSelectWidth;
    QColor _rectSelectColor;

    QColor _mainBrushColor;
    QColor _subBrushColor;

    QString _nodeName;
    QGraphicsProxyWidget *_widget;
    NodeLineEditWidget *_lineEdit;

    QGraphicsScene *_scene;

    NodePort *_inpPort;
    NodePort *_outPort;

    // 名称框在键盘输入结束后触发的命令
    // 检查名称是否重命名
    void lineEditFinishedCmd(void);

    // 获取新的节点名称
    QString getNewNodeName(QString &s);
};

#endif

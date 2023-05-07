/*** 
 * 创建节点连接线
***/

#ifndef NODECONNECTIONOBJECT_H
#define NODECONNECTIONOBJECT_H

#include <QtWidgets>
#include <QtWidgets/QGraphicsPathItem>
#include <QtWidgets/QGraphicsObject>

#include "NodeEditNamespace.h"



class NodeConnectionObject : public QGraphicsPathItem
{
public:
    // 设置连接线的类型编号
    enum
    {
        Type = QGraphicsItem::UserType + 2
    };

    NodeConnectionObject(QGraphicsItem *parent);
    ~NodeConnectionObject(void) = default;

    // 设置连接线的输入点和输出点
    void setPosOut(const QPointF &p);
    void setPosInp(const QPointF &p);

    // 设置连接线两点的节点端口
    void setPortOut(QGraphicsItem *portOut);
    void setPortInp(QGraphicsItem *portInp);

    // 获取连接线两点的节点端口
    QGraphicsItem *getPortOut(void);
    QGraphicsItem *getPortInp(void);

    // 刷新连接线
    void upConnectPath();

    // 返回连接线的类型编号
    inline int type() const { return Type; }

private:
    QPointF _posInp;
    QPointF _posOut;

    QGraphicsItem *_portInp;
    QGraphicsItem *_portOut;
};

#endif

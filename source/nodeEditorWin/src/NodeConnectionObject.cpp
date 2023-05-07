#include "nodeEditorWin/include/NodeConnectionObject.h"


NodeConnectionObject::NodeConnectionObject(QGraphicsItem *parent) : QGraphicsPathItem(parent),
                                                                    _portInp(nullptr),
                                                                    _portOut(nullptr)
{
    setPen(QPen(Qt::black, 2));
    setBrush(Qt::NoBrush);
    setZValue(-1);
}

void NodeConnectionObject::setPosOut(const QPointF &p)
{
    _posOut = p;
}

void NodeConnectionObject::setPosInp(const QPointF &p)
{
    _posInp = p;
}

void NodeConnectionObject::setPortOut(QGraphicsItem *itemOut)
{
    _portOut = itemOut;
}

void NodeConnectionObject::setPortInp(QGraphicsItem *itemInp)
{
    _portInp = itemInp;
}

QGraphicsItem *NodeConnectionObject::getPortOut(void)
{
    return _portOut;
}

QGraphicsItem *NodeConnectionObject::getPortInp(void)
{
    return _portInp;
}

void NodeConnectionObject::upConnectPath()
{
    // 获取节点端口的场景坐标
    if (_portInp != nullptr && _portOut != nullptr)
    {
        _posInp = _portInp->scenePos();
        _posOut = _portOut->scenePos();
    }

    // 创建连接线对象
    QPainterPath pt;

    // 设置连接线的起始点
    pt.moveTo(_posOut);

    qreal dx = _posInp.x() - _posOut.x();
    qreal dy = _posInp.y() - _posOut.y();

    QPointF ctr1(_posOut.x() + dx * 0.25, _posOut.y() + dy * 0.1);
    QPointF ctr2(_posOut.x() + dx * 0.75, _posOut.y() + dy * 0.9);

    // 设置连接线的结束点
    pt.cubicTo(ctr1, ctr2, _posInp);

    // 更新连接线
    setPath(pt);
}


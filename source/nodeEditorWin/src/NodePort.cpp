#include "NodeEditorWin/include/NodePort.h"

NodePort::NodePort(QGraphicsItem *parent, qreal x, qreal y, qreal radius, bool portState) : QGraphicsPathItem(parent),
                                                                                            _portType(portState),
                                                                                            _con(nullptr),
                                                                                            _outPort(nullptr),
                                                                                            _inpPort(nullptr)
{
    this->setFlags(QGraphicsItem::ItemSendsScenePositionChanges);
    QPainterPath p;
    p.addEllipse(-radius, -radius, 2 * radius, 2 * radius); // 设置端口的中心点和半径
    this->setBrush(QBrush(QColor(255, 255, 255)));          // 设置端口的颜色
    this->setPath(p);
    this->setPos(x, y); // 设置端口的坐标
}

void NodePort::setConnect(NodeConnectionObject *con)
{
    _con = con;
}

bool NodePort::isConnect(void)
{
    if (_con == nullptr)
        return false;

    return true;
}

void NodePort::deleteConnect(void)
{
    if (_con != nullptr)
    {
        delete _con;
    }

    if (_outPort != nullptr)
    {
        // 恢复输出端口的属性默认值
        _outPort->setConnect(nullptr);
        _outPort->deleteConnect();
    }

    // 恢复端口的属性默认值
    _con = nullptr;
    _outPort = nullptr;
    _inpPort = nullptr;
}

void NodePort::deleteOldConnect(void)
{
    if (_con != nullptr)
    {
        delete _con;
    }

    if (_inpPort != nullptr)
    {
        // 恢复输入端口的属性默认值
        _inpPort->setConnect(nullptr);
        _inpPort->deleteConnect();
    }

    // 恢复端口的属性默认值
    _con = nullptr;
    _outPort = nullptr;
    _inpPort = nullptr;
}

void NodePort::setOutPort(NodePort *p)
{
    _outPort = p;
}

NodePort *NodePort::getOutPort(void)
{
    return _outPort;
}

void NodePort::setInpPort(NodePort *p)
{
    _inpPort = p;
}

NodePort *NodePort::getInpPort(void)
{
    return _inpPort;
}

QVariant NodePort::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged && _con)
    {
        // 更新连接线
        _con->upConnectPath();
    }

    return value;
}

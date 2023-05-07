/***
 * 创建节点的端口
 ***/
#ifndef NODEPORT_H
#define NODEPORT_H

#include <QtWidgets>

#include "NodeConnectionObject.h"


class NodePort : public QGraphicsPathItem
{

public:
    // 设置端口的类型编号
    enum
    {
        Type = QGraphicsItem::UserType + 1
    };

    // 设置端口的状态编号
    enum
    {
        TypeInput = 0,
        TypeOutput = 1
    };

    explicit NodePort(QGraphicsItem *parent, qreal x, qreal y, qreal radius, bool portState = 0);
    ~NodePort() = default;

    // 获取类型编号 和 状态编号
    inline int type() const { return Type; }
    inline int getPortType() { return _portType; }

    // 设置连接线对象 或 连接线状态
    void setConnect(NodeConnectionObject *con);
    bool isConnect(void);

    // 删去当前连接线和过去的连接线
    void deleteConnect(void);
    void deleteOldConnect(void);

    // 设置和获取输入的端口
    void setInpPort(NodePort *p);
    NodePort *getInpPort(void);

    // 设置和获取输出的端口
    void setOutPort(NodePort *p);
    NodePort *getOutPort(void);

protected:
    // 端口位置变化后更新连接线的位置
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    int _portType;

    NodePort *_outPort;
    NodePort *_inpPort;

    NodeConnectionObject *_con;
};

#endif


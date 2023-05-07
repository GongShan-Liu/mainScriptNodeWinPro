#include "nodeEditorWin/include/NodeEditScene.h"

NodeEditScene::NodeEditScene(QObject *parent) : QGraphicsScene(parent),
                                                _con(nullptr),
                                                _nodeNumber(1),
                                                _port(nullptr)
{
}

NodeEditScene::~NodeEditScene(void)
{
    if (_con != nullptr)
    {
        delete _con;
        _con = nullptr;
    };
}

void NodeEditScene::createNode(const QString &name, qreal x, qreal y)
{
    // 如果节点名称不重复，则创建节点
    if (NodeGraphicsObject::nodeNameSet.count(name) == 0)
    {
        std::shared_ptr<NodeGraphicsObject> nodePtr = std::make_shared<NodeGraphicsObject>(this, name);
        NodeLineEditWidget *lineExt = nodePtr.get()->getLineEdit();
        _nodeData.insert(std::make_pair(lineExt, nodePtr));
        _nodeData[lineExt]->setPos(x, y); // 设置节点坐标为鼠标位置
        _nodeNumber++;
    }
    
}

void NodeEditScene::deleteSelectNode(void)
{
    for (QGraphicsItem *item : this->selectedItems())
    {
        if (NodeGraphicsObject *n = qgraphicsitem_cast<NodeGraphicsObject *>(item))
        {
            // 清除所选的节点在节点数据库的记录
            NodeLineEditWidget *lineExt = n->getLineEdit();
            if (_nodeData.count(lineExt) == 1)
            {
                NodePort *outPort = _nodeData[lineExt].get()->getOutPort();
                NodePort *inpPort = _nodeData[lineExt].get()->getInpPort();

                // 删去端口的连接
                if (outPort->isConnect())
                {
                    outPort->deleteConnect();
                }

                if (inpPort->isConnect())
                {
                    inpPort->deleteOldConnect();
                }

                _nodeData.erase(lineExt);
            }

            // for (std::set<QString>::iterator it = NodeGraphicsObject::nodeNameSet.begin(); it != NodeGraphicsObject::nodeNameSet.end(); it++)
            // {
            //     qDebug() << *it;
            // }
            // qDebug() << NodeGraphicsObject::nodeCount;
        };
    };
}

void NodeEditScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _port = nullptr; // 端口初始值

    // 创建节点端口的连接线
    if (event->button() == Qt::LeftButton)
    {
        QTransform transform;
        QGraphicsItem *item = this->itemAt(event->scenePos(), transform);

        // 存在对象并且对象类型是：端口类型
        if (item && item->type() == NodePort::Type)
        {
            // 存在对象的父对象是：节点对象
            if (auto *n = qgraphicsitem_cast<NodeGraphicsObject *>(item->parentItem()))
            {
                NodeLineEditWidget *lineExt = n->getLineEdit();

                // 节点对象存在节点数据库中
                if (_nodeData.count(lineExt) == 1) //
                {
                    _port = _nodeData[lineExt].get()->getOutPort();

                    // 对象的场景坐标等于端口的场景坐标并且端口的状态类型是可输出
                    if (item->scenePos() == _port->scenePos() && _port->getPortType() == NodePort::TypeOutput)
                    {
                        // 可输出的端口是否连接过
                        if (_port->isConnect())
                        {
                            // 删去连接过的连接线
                            // 恢复输入端口和输出端口的默认初始值
                            _port->deleteConnect();
                        }

                        // 创建连接线对象指针
                        _con = new NodeConnectionObject(Q_NULLPTR);

                        // 连接线对象添加到场景
                        this->addItem(_con);

                        // 设置连接线对象的数据
                        _con->setPortOut(item);
                        _con->setPosInp(item->scenePos());
                        _con->setPosOut(event->scenePos());
                        _con->upConnectPath();

                        // 端口设置连接线对象
                        _port->setConnect(_con);
                    }
                }
            }
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void NodeEditScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // 在鼠标移动中的循环更新连接线对象
    if (_con != nullptr)
    {
        _con->setPosInp(event->scenePos());
        _con->upConnectPath();
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void NodeEditScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // 完成节点端口的连接线
    if (_con != nullptr && event->button() == Qt::LeftButton)
    {
        QTransform transform;
        QGraphicsItem *item = this->itemAt(event->scenePos(), transform);

        // 存在对象并且对象类型是：端口类型
        if (item && item->type() == NodePort::Type)
        {
            // 存在对象的父对象是：节点对象
            if (auto *n = qgraphicsitem_cast<NodeGraphicsObject *>(item->parentItem()))
            {
                NodeLineEditWidget *lineExt = n->getLineEdit();

                // 节点对象存在节点数据库中
                if (_nodeData.count(lineExt) == 1)
                {
                    NodePort *p = _nodeData[lineExt].get()->getInpPort();

                    // 对象的场景坐标等于端口的场景坐标并且端口的状态类型是可输入
                    if (item->scenePos() == p->scenePos() && p->getPortType() == NodePort::TypeInput)
                    {
                        // 输入的端口是否曾经被输入过
                        if (p->isConnect())
                        {
                            // 删去曾经输入过的连接线
                            // 恢复输入端口和输出端口的默认初始值
                            p->deleteOldConnect();
                        }

                        // 设置连接线对象的数据
                        _con->setPosInp(event->scenePos());
                        _con->setPortInp(item);
                        _con->upConnectPath();

                        // 设置输入端口的连接线对象和输入对象
                        p->setConnect(_con);
                        p->setInpPort(_port);

                        // 设置输出端口的输出对象
                        _port->setOutPort(p);

                        _con = nullptr;
                    }
                    else
                    {
                        // 删除连接线对象并恢复输出端口的默认初始值
                        delete _con;
                        _con = nullptr;
                        _port->setConnect(nullptr);
                        _port->deleteConnect();
                    }
                }
                else
                {
                    // 删除连接线对象并恢复输出端口的默认初始值
                    delete _con;
                    _con = nullptr;
                    _port->setConnect(nullptr);
                    _port->deleteConnect();
                }
            }
            else
            {
                // 删除连接线对象并恢复输出端口的默认初始值
                delete _con;
                _con = nullptr;
                _port->setConnect(nullptr);
                _port->deleteConnect();
            }
        }
        else
        {
            // 删除连接线对象并恢复输出端口的默认初始值
            delete _con;
            _con = nullptr;
            _port->setConnect(nullptr);
            _port->deleteConnect();
        }
    }

    QGraphicsScene::mouseReleaseEvent(event);
}
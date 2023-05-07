#ifndef NODEEDITSCENE_H
#define NODEEDITSCENE_H

#include <string>
#include <map>

#include <QtWidgets>
#include <QtWidgets/QGraphicsScene>

#include "nodeEditorWin/include/NodeGraphicsObject.h"
#include "nodeEditorWin/include/NodeConnectionObject.h"

class NodeEditScene : public QGraphicsScene
{

public:
    explicit NodeEditScene(QObject *parent);
    ~NodeEditScene(void);

    NodeEditScene(const NodeEditScene &n) = delete;
    NodeEditScene &operator=(const NodeEditScene &n) = delete;

    // 创建节点和删去所选节点
    void createNode(const QString &name, qreal x = 0, qreal y = 0);
    void deleteSelectNode(void);

    // 获取节点的序号
    inline int getNodeNumber(void) { return _nodeNumber; }

protected:
    // 场景鼠标的点击、移动、释放的事件 
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int _nodeNumber;

    NodeConnectionObject *_con; // 节点连接线对象
    NodePort *_port; // 端口对象

    // 存储节点数据的map
    std::map<NodeLineEditWidget *, std::shared_ptr<NodeGraphicsObject>> _nodeData;
};

#endif

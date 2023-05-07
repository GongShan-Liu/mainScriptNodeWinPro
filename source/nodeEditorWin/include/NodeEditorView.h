#ifndef NODEEDITORWIN_H
#define NODEEDITORWIN_H

#include <string>

#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsView>
#include <QtGui/QMouseEvent>

#include "NodeEditScene.h"

class NodeEditorView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit NodeEditorView(QWidget *parent = Q_NULLPTR);
    ~NodeEditorView();

    NodeEditorView(const NodeEditorView &n) = delete;
    NodeEditorView &operator=(const NodeEditorView &n) = delete;

    void setScene(QGraphicsScene *scene);

public Q_SLOTS:
    void scaleUp();   // 鼠标滚动缩小
    void scaleDown(); // 鼠标滚动放大

protected:
    void contextMenuEvent(QContextMenuEvent *event) override; // 设置鼠标右键菜单
    void wheelEvent(QWheelEvent *event) override;      // 设置鼠标中键滚动缩放视图
    void mousePressEvent(QMouseEvent *event) override; // 设置鼠标中键位移视图
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override; // 设置鼠标中键位移视图的更新
    void showEvent(QShowEvent *event) override;

    // 绘制背景网格
    void drawBackground(QPainter *painter, const QRectF &r) override;

private:
    QAction *_deleteSelectionAction;

    QPointF _clickPos;
    std::shared_ptr<NodeEditScene> _scene; // view中唯一的scene类
};

#endif

#ifndef DOCKWIN_H
#define DOCKWIN_H

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QWidget>

// 子窗口为浮动窗口
class DockWin : public QDockWidget
{
    Q_OBJECT
public:
    explicit DockWin(QWidget *parent);
    ~DockWin(void);
    
    // 设置窗口浮动时可以最小化、最大化
    void topLevelChangedCmd(void);

    // 设置UI
    void setWin(char *title, char *objName, QWidget *widget);
};

#endif
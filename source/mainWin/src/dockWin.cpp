#include "mainWin/include/dockWin.h"

DockWin::DockWin(QWidget *parent) : QDockWidget(parent)
{

    this->resize(640, 480);
    this->setEnabled(true);
    this->setFloating(true);
    this->setVisible(false);
    QObject::connect(this, &QDockWidget::topLevelChanged, this, &DockWin::topLevelChangedCmd);
}

DockWin::~DockWin(void)
{
}

void DockWin::topLevelChangedCmd(void)
{
    // 设置窗口浮动时可以最小化、最大化
    if (this->isFloating())
    {
        this->setWindowFlags(Qt::CustomizeWindowHint |
                             Qt::Window | Qt::WindowMinimizeButtonHint |
                             Qt::WindowMaximizeButtonHint |
                             Qt::WindowCloseButtonHint);

        if (!this->isVisible())
            this->show();
    }
}

void DockWin::setWin(char *title, char *objName, QWidget *widget)
{
    this->setWindowTitle(title);
    this->setObjectName(QString::fromUtf8(objName));
    this->setWidget(widget);
    this->topLevelChangedCmd();
    if (!this->isVisible())
        this->show();
}

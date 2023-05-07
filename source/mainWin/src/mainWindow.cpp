#include <QtWidgets/QApplication>
#include "mainWin/include/mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // 主窗口UI
    _setupUI();
}

MainWindow::~MainWindow()
{
    if (scriptEditorAction != NULL)
    {
        delete scriptEditorAction;
        scriptEditorAction = NULL;
    }

    if (nodeEditorAction != NULL)
    {
        delete nodeEditorAction;
        nodeEditorAction = NULL;
    }

    if (menuwindows != NULL)
    {
        delete menuwindows;
        menuwindows = NULL;
    }

    if (menuBar != NULL)
    {
        delete menuBar;
        menuBar = NULL;
    }

    if (mainToolBar != NULL)
    {
        delete mainToolBar;
        mainToolBar = NULL;
    }

    if (statusBar != NULL)
    {
        delete statusBar;
        statusBar = NULL;
    }

    if (centralWidget != NULL)
    {
        delete centralWidget;
        centralWidget = NULL;
    }

    if (scriptEditorWidget != NULL)
    {
        delete scriptEditorWidget;
        scriptEditorWidget = NULL;
    }

    if (scriptEditorDock != NULL)
    {
        delete scriptEditorDock;
        scriptEditorDock = NULL;
    }
}

void MainWindow::_setupUI(void)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("mainScriptNodeWinProClass"));
    this->setEnabled(true);
    this->resize(1080, 720);

    // 脚本编辑窗口action
    scriptEditorAction = new QAction(this);
    scriptEditorAction->setObjectName(QString::fromUtf8("scriptEditorAction"));

    // 节点编辑action
    nodeEditorAction = new QAction(this);
    nodeEditorAction->setObjectName(QString::fromUtf8("nodeEditorAction"));

    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setCentralWidget(centralWidget);

    // 主窗口菜单栏
    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 750, 23));

    menuwindows = new QMenu(menuBar);
    menuwindows->setObjectName(QString::fromUtf8("menuwindows"));
    this->setMenuBar(menuBar);

    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    this->addToolBar(Qt::TopToolBarArea, mainToolBar);

    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    this->setStatusBar(statusBar);

    // 脚本编辑窗口
    scriptEditorDock = new DockWin(this);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(1), scriptEditorDock);

    // 节点编辑窗口
    nodeEditorDock = new DockWin(this);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(1), nodeEditorDock);

    // 菜单栏按钮
    menuBar->addAction(menuwindows->menuAction());
    menuwindows->addAction(scriptEditorAction);
    menuwindows->addAction(nodeEditorAction);

    _retranslateUi();
    _connectCmd();

    QMetaObject::connectSlotsByName(this);

    scriptEditorWidget = nullptr;
    nodeEditor= nullptr;
} // setupUi

void MainWindow::_retranslateUi(void)
{
    this->setWindowTitle(QApplication::translate("mainScriptNodeWinProClass", "MainWinScript", nullptr));
    scriptEditorAction->setText(QApplication::translate("mainScriptNodeWinProClass", "ScriptEditor", nullptr));
    nodeEditorAction->setText(QApplication::translate("mainScriptNodeWinProClass", "NodeEditor", nullptr));
    menuwindows->setTitle(QApplication::translate("mainScriptNodeWinProClass", "Windows", nullptr));
} // retranslateUi

void MainWindow::_connectCmd(void)
{   
    // 菜单按钮连接到命令
    QObject::connect(scriptEditorAction, &QAction::triggered, this, &MainWindow::openScriptEditorWin);
    QObject::connect(nodeEditorAction, &QAction::triggered, this, &MainWindow::openNodeEditorWin);
}

void MainWindow::openScriptEditorWin(void)
{
    // 脚本编辑窗口
    if (!scriptEditorDock->isVisible())
    {
        if (scriptEditorWidget == nullptr)
            scriptEditorWidget = new ScriptEditorWidget();

        scriptEditorDock->setWin("Script Editor Windows", "scriptEditorDock", scriptEditorWidget);
    }
}

void MainWindow::openNodeEditorWin(void)
{
    // 节点编辑窗口
    if (!nodeEditorDock->isVisible())
    {
        if (nodeEditor == nullptr)
            nodeEditor = new NodeEditorView(Q_NULLPTR);

        nodeEditorDock->setWin("Node Editor Windows", "nodeEditorDock", nodeEditor);
    }
}
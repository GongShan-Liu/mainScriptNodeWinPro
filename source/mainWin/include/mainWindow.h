#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "dockWin.h"
#include "scriptEditorWin/include/scriptEditorWidgets.h"
#include "nodeEditorWin/include/NodeEditorView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // 窗口action
    QAction *scriptEditorAction;
    QAction *nodeEditorAction;

    // 主窗口变量
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuwindows;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    // 脚本编辑窗口变量
    ScriptEditorWidget *scriptEditorWidget;
    DockWin *scriptEditorDock;

    // 节点编辑窗口变量
    NodeEditorView *nodeEditor;
    DockWin *nodeEditorDock;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MainWindow(const MainWindow &m) = delete;
    MainWindow &operator=(const MainWindow &m) = delete;

    void openScriptEditorWin(void); // 打开脚本编辑窗口
    void openNodeEditorWin(void);   // 打开节点编辑窗口

private:
    // 主窗口UI 
    void _setupUI(void);
    void _retranslateUi(void);

    void _connectCmd(void); // action连接到命令
};

#endif
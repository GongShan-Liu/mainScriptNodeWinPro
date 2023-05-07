#ifndef SCRIPTEDITORWIDGETS_H
#define SCRIPTEDITORWIDGETS_H

#include <string>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QSplitter>
#include <QtCore/QString>
#include <QtWidgets/QPushButton>

#include "feedbackFrame.h"
#include "scriptTextFrame.h"
#include "pyLibs/include/catchpystd.h"

// 脚本编辑器部件
class ScriptEditorWidget : public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout *scriptEditorVBLy;
    QSplitter *scriptEditorSpt;

    FeedbackFrame *scriptEditorFb;
    ScriptTextFrame *scriptTextEditWin;

    explicit ScriptEditorWidget(void);
    ~ScriptEditorWidget(void);

    ScriptEditorWidget(const ScriptEditorWidget &s) = delete;
    ScriptEditorWidget &operator=(const ScriptEditorWidget &s) = delete;

private:
    // 运行代码变量
    repystd::CatchStdData *runCode;

    QString textEdit;

    // 获取输出和错误的变量
    std::string out;
    std::string err;

    // 设置UI和输出浏览框
    void _setupUI(void);
    void _outBrowse(void);
};

#endif
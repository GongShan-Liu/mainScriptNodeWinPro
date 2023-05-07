#include "scriptEditorWin/include/scriptEditorWidgets.h"

ScriptEditorWidget::ScriptEditorWidget(void)
{
    _setupUI();
    runCode = new repystd::CatchStdData();
    runCode->setStd();
}

ScriptEditorWidget::~ScriptEditorWidget(void)
{
    if (scriptEditorVBLy != NULL)
    {
        delete scriptEditorVBLy;
        scriptEditorVBLy = NULL;
    }

    if (scriptEditorFb != NULL)
    {
        delete scriptEditorFb;
        scriptEditorFb = NULL;
    }
        
    if (scriptTextEditWin != NULL)
    {
        delete scriptTextEditWin;
        scriptTextEditWin = NULL;
    }

    if (scriptEditorSpt != NULL)
    {
        delete scriptEditorSpt;
        scriptEditorSpt =NULL;
    }
        

    if (runCode != NULL)
    {
        delete runCode;
        runCode = NULL;
    }
        
}

// 设置UI
void ScriptEditorWidget::_setupUI()
{
    // ScriptEditorWidget contents
    this->setObjectName(QString::fromUtf8("scriptEditorWidgets"));

    scriptEditorVBLy = new QVBoxLayout(this);
    scriptEditorVBLy->setSpacing(6);
    scriptEditorVBLy->setContentsMargins(11, 11, 11, 11);
    scriptEditorVBLy->setObjectName(QString::fromUtf8("scriptEditorvLy"));

    scriptEditorSpt = new QSplitter(this);
    scriptEditorSpt->setObjectName(QString::fromUtf8("scriptEditorSpt"));
    scriptEditorSpt->setOrientation(Qt::Vertical);

    scriptEditorFb = new FeedbackFrame(this);
    scriptEditorSpt->addWidget(scriptEditorFb);

    scriptTextEditWin = new ScriptTextFrame((QWidget *)scriptEditorSpt);

    scriptEditorSpt->addWidget(scriptTextEditWin->scriptTextLy);
    scriptEditorVBLy->addWidget(scriptEditorSpt);

    //
    QObject::connect(scriptTextEditWin->enterBtn, &QPushButton::clicked, this, &ScriptEditorWidget::_outBrowse);
}

// 设置输出浏览框
void ScriptEditorWidget::_outBrowse(void)
{
    textEdit = scriptTextEditWin->scriptTextEdit->toPlainText();
    scriptEditorFb->append(textEdit);

    // 获取脚本编辑框的内容并运行
    runCode->pyRunString(textEdit.toStdString());

    // 获取输出和错误
    out = runCode->getOut();
    err = runCode->getErr();

    // 把信息输出到浏览框
    if (out != "")
        scriptEditorFb->append(out.c_str());

    if (err != "")
        scriptEditorFb->append(err.c_str());
}
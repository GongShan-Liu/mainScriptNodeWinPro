#include "scriptEditorWin/include/scriptTextFrame.h"

ScriptTextFrame::ScriptTextFrame(QWidget *parent)
{
    _setupUI(parent);
}

ScriptTextFrame::~ScriptTextFrame(void)
{
    if (scriptTextEdit != NULL)
    {
        delete scriptTextEdit;
        scriptTextEdit = NULL;
    }

    if (enterBtn != NULL)
    {
        delete enterBtn;
        enterBtn = NULL;
    }

    if (scriptTextHBLy != NULL)
    {
        delete scriptTextHBLy;
        scriptTextHBLy = NULL;
    }

    if (scriptTextLy != NULL)
    {
        delete scriptTextLy;
        scriptTextLy = NULL;
    }
}

// 设置UI
void ScriptTextFrame::_setupUI(QWidget *parent)
{
    _parent = parent;
    scriptTextLy = new QWidget(parent);
    scriptTextLy->setObjectName(QString::fromUtf8("scriptTextLy"));

    scriptTextHBLy = new QHBoxLayout(scriptTextLy);
    scriptTextHBLy->setSpacing(6);
    scriptTextHBLy->setContentsMargins(11, 11, 11, 11);
    scriptTextHBLy->setObjectName(QString::fromUtf8("scriptTextLy"));
    scriptTextHBLy->setContentsMargins(0, 0, 0, 0);

    // 创建文件编辑
    scriptTextEdit = new QTextEdit(scriptTextLy);
    scriptTextEdit->setObjectName(QString::fromUtf8("scriptTextEdit"));

    // 创建按钮
    enterBtn = new QPushButton(scriptTextLy);
    enterBtn->setObjectName(QString::fromUtf8("enterBtn"));
    enterBtn->setMinimumSize(QSize(0, 50));

    // 添加部件
    scriptTextHBLy->addWidget(scriptTextEdit);
    scriptTextHBLy->addWidget(enterBtn);

    _retranslateUI();
}

void ScriptTextFrame::_retranslateUI(void)
{
    enterBtn->setText(QString::fromUtf8("Enter"));
}
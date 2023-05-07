#include "scriptEditorWin/include/feedbackFrame.h"

// 反馈框UI
FeedbackFrame::FeedbackFrame(QWidget *parent) : QTextBrowser(parent)
{
    this->setObjectName(QString::fromUtf8("feedbackBrowser"));
}
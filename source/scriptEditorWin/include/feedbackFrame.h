#ifndef FEEDBACKFRAME_H
#define FEEDBACKFRAME_H

#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

// 反馈框
class FeedbackFrame : public QTextBrowser
{
    Q_OBJECT
public:
    explicit FeedbackFrame(QWidget* parent);
    ~FeedbackFrame(void) = default;
};



#endif
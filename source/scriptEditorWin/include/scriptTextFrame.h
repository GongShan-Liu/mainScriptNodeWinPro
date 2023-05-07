#ifndef SCRIPTTEXTFRAME_H
#define SCRIPTTEXTFRAME_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>

// 脚本编辑框
class ScriptTextFrame : public QObject
{
    Q_OBJECT
public:
    QWidget *scriptTextLy;
    QHBoxLayout *scriptTextHBLy;
    QTextEdit *scriptTextEdit;
    QPushButton *enterBtn;

    explicit ScriptTextFrame(QWidget *parent);
    ~ScriptTextFrame(void);

    ScriptTextFrame(const ScriptTextFrame &s) = delete;
    ScriptTextFrame &operator=(const ScriptTextFrame &s) = delete;

private:
    QWidget *_parent;
    void _setupUI(QWidget *parent);  // 设置UI
    void _retranslateUI(void);
};

#endif
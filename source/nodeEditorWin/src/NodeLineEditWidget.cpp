#include "nodeEditorWin/include/NodeLineEditWidget.h"
// #include <QDebug>

NodeLineEditWidget::NodeLineEditWidget(const QString &s, QWidget *parent) : QLineEdit(parent)
{
    this->setupUi();
    this->setFocusPolicy(Qt::ClickFocus); // 设置光标策略为：点击
    this->setText(s);
    this->setContextMenuPolicy(Qt::NoContextMenu); // 设置无上下文菜单

    _text = s; // 获取初始的名称
    _defualFont = QFont("Times", 15); // 设置初始的格式
    this->setFont(_defualFont);
}

void NodeLineEditWidget::focusInEvent(QFocusEvent *event)
{
    // 输入框边界颜色更改为蓝色和变粗
    this->setStyleSheet("border:2px solid rgb(0, 120, 170);background-color: rgb(47, 47, 47);color: rgb(255, 255, 255);");
    this->setFont(QFont("Times", 10));  // 字体变小
    QLineEdit::focusInEvent(event);
}

void NodeLineEditWidget::focusOutEvent(QFocusEvent *event)
{
    this->editFinalCmd(); // 检查输入框是否为空
    QLineEdit::focusOutEvent(event);  // 恢复默认格式
}

void NodeLineEditWidget::setupUi(void)
{
    // 默认输入框格式
    this->setStyleSheet("background: transparent;color: rgb(255, 255, 255);border-width: 0;border-style: outset;");
    this->setFont(_defualFont);
}

void NodeLineEditWidget::editFinalCmd(void)
{
    this->setupUi();
    QString text = this->text();
    // 检查输入框是否为空?
    //  是->：设置为前名称
    //  否->: 获取新的名称
    if (text == "")
    {
        this->setText(_text);
    }
    else
    {
        _text = text;
    }

}



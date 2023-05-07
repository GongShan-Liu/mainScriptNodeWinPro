/***
 * 创建节点的名称框
 ***/
#ifndef NODELINEEDITWIDGET_H
#define NODELINEEDITWIDGET_H

#include <QtWidgets>
#include <QString>

#include "NodeEditNamespace.h"



class NodeLineEditWidget : public QLineEdit
{

public:
    explicit NodeLineEditWidget(const QString &s, QWidget *parent = nullptr);
    ~NodeLineEditWidget() = default;

protected:
    // 光标进入和退出事件
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    QString _text;
    QFont _defualFont;

    // 默认输入框
    void setupUi(void);

    // 编辑完成后触发的命令
    // 检查输入框是否为空
    void editFinalCmd(void); 
};

#endif

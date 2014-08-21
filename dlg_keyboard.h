/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_keyboard.h

* 功能描述: 自定义大键盘

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#ifndef DLG_KEYBOARD_H
#define DLG_KEYBOARD_H

#include <QDialog>
#include <QSignalMapper>

namespace Ui {
class Dlg_Keyboard;
}

class Dlg_Keyboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Keyboard(QWidget *parent = 0);
    ~Dlg_Keyboard();

private:
    Ui::Dlg_Keyboard *ui;

private:
    QSignalMapper  sglMapL;
public:
    QString m_str;
private slots:
    void on_btnShift_clicked();
    void on_btnEnter_clicked();
    void on_btnQuit_clicked();
    void on_btnBack_clicked();
    void on_btn_clicked(int ibtn);
};

#endif // DLG_KEYBOARD_H

//==========================================================================================
// End of file.
//==========================================================================================

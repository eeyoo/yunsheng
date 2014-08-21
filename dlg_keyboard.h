/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_keyboard.h

* ��������: �Զ�������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
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

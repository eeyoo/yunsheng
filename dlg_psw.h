/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_psw.h

* ��������: ���ּ���ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef DLG_PSW_H
#define DLG_PSW_H

#include <QDialog>
#include <QSignalMapper>

namespace Ui {
    class Dlg_Psw;
}

class Dlg_Psw : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Psw(QWidget *parent = 0);
    ~Dlg_Psw();

private:
    QSignalMapper  sglMapL;
private:
    Ui::Dlg_Psw *ui;
public:
    QString m_str;
private slots:
    void on_btnBack_clicked();
    void on_btn_clicked(int ibtn);
    void on_btnQuit_K_clicked();
    void on_btnOK_K_clicked();
};

#endif // DLG_PSW_H

//==========================================================================================
// End of file.
//==========================================================================================

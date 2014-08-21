/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_reset.h

* ��������: ��λ����

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef DLG_RESET_H
#define DLG_RESET_H

#include <QDialog>

namespace Ui {
    class Dlg_Reset;
}

class Dlg_Reset : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Reset(QWidget *parent = 0);
    ~Dlg_Reset();

    bool chkRstOK();

private:
    Ui::Dlg_Reset *ui;

private slots:
    void on_btnQuit_clicked();
    void on_btnOK_clicked();
    void UpdateSet();
};

#endif // DLG_RESET_H

//==========================================================================================
// End of file.
//==========================================================================================

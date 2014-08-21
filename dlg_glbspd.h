/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_glbspd.h

* ��������: �Զ����Ǳ�ؼ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef DLG_GLBSPD_H
#define DLG_GLBSPD_H

#include <QDialog>

class Dashboard;

namespace Ui {
class Dlg_GlbSpd;
}

class Dlg_GlbSpd : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_GlbSpd(QWidget *parent = 0);
    ~Dlg_GlbSpd();

private slots:
    void on_leGlbSpd_clicked();
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_btnAdd_clicked();

    void on_btnSub_clicked();

private:
    Ui::Dlg_GlbSpd *ui;
    Dashboard *mBoard;
    double mVal; //ȫ���ٶȰٷֱ�

};

#endif // DLG_GLBSPD_H

//==========================================================================================
// End of file.
//==========================================================================================

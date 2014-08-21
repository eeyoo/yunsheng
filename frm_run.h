/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_run.h

* ��������: ����ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef FRM_RUN_H
#define FRM_RUN_H

#include "twidget.h"
#include <QModelIndex>
#include <QTime>

namespace Ui {
    class Frm_Run;
}

class Frm_Run : public TWidget
{
    Q_OBJECT

public:
    enum Run_Model
    {
        R_MANA,R_AUTO,R_SPRD,R_SSTP
    };
public:
    Frm_Run::Run_Model r_model;
public:
    Frm_Run();
    ~Frm_Run();

    void UpdateUI();
public:
    Ui::Frm_Run *ui;

private:
    int m_iSAdr;
    QTime prdTim;

private slots:
    void on_tblV_Pro_clicked(QModelIndex index);
    void setVisible(bool visible);
    void on_btnDld_clicked();
    void on_btnSPrd_clicked();
    void on_btnSStp_clicked();
};

#endif // FRM_RUN_H

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_teach.h

* ��������: ʾ�̱��ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef FRM_TEACH_H
#define FRM_TEACH_H

#include "twidget.h"
#include <QSignalMapper>
#include <QModelIndex>

namespace Ui {
    class Frm_Teach;
}

class Frm_Teach : public TWidget
{
    Q_OBJECT

public:
    Frm_Teach();
    ~Frm_Teach();
public:
    Ui::Frm_Teach *ui;

private:
    void InitBtn();
    void InitTim();
public:
    int         m_iCmd;
    bool        m_bModify;
    bool        m_bStk;
private:
    QSignalMapper  sglMapT;
    QSignalMapper  sglMapL;
public slots:
    void on_tabCmd_currentChanged(int index);
    void on_btn_clicked(int ibtn);
    void on_leT_clicked(int ile);

private slots:
    void on_leStkN_clicked();
    void on_leNoO_clicked();
    void on_leNoI_clicked();
    void on_lePosR_clicked();
    void on_lePosD_clicked();
    void on_btnOK_clicked();
    void on_btnBck_clicked();
    void on_btnAhd_clicked();
    void on_btnSve_clicked();
    void on_btnDel_clicked();
    void setVisible(bool visible);
    void on_tblV_Pro_clicked(QModelIndex index);
};

#endif // FRM_TEACH_H

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_pros.cpp

* ��������: ��Ʒ�����ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/


#include "frm_pros.h"
#include "ui_frm_pros.h"
#include "dlg_psw.h"
#include "tcom.h"

/*************************************************************************
* ��������: Frm_ProS
* ��    ��: ���캯��
* �������: 
* �������: ��
* �� �� ֵ: 
*************************************************************************/
Frm_ProS::Frm_ProS() :
    
    ui(new Ui::Frm_ProS)
{
    ui->setupUi(this);
    //setAutoFillBackground(true);
}
/*************************************************************************
* ��������: ~Frm_ProS
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: 
*************************************************************************/
Frm_ProS::~Frm_ProS()
{
    delete ui;
}
/*************************************************************************
* ��������: on_lePlnPrd_clicked
* ��    ��: ����ƻ���������
* �������: ��
* �������: ��
* �� �� ֵ: 
*************************************************************************/
void Frm_ProS::on_lePlnPrd_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->lePlnPrd->setText(dlg.m_str);
        com05.para.pln_prd = dlg.m_str.toInt();

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com05));
    }
}
/*************************************************************************
* ��������: on_leBadPrd_clicked
* ��    ��: ���벻����������
* �������: ��
* �������: ��
* �� �� ֵ: 
*************************************************************************/
void Frm_ProS::on_leBadPrd_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->leBadPrd->setText(dlg.m_str);
        com05.para.bad_prd = dlg.m_str.toInt();

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com05));
    }
}
/*************************************************************************
* ��������: on_leCirTim_clicked
* ��    ��: ����ѭ����ʱ
* �������: ��
* �������: ��
* �� �� ֵ: 
*************************************************************************/
void Frm_ProS::on_leCirTim_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->leCirTim->setText(dlg.m_str);
        com05.para.cir_tim = dlg.m_str.toInt();

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com05));
    }
}
/*************************************************************************
* ��������: on_leRstTim_clicked
* ��    ��: ���븴λʱ��
* �������: ��
* �������: ��
* �� �� ֵ: 
*************************************************************************/
void Frm_ProS::on_leRstTim_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->leRstTim->setText(dlg.m_str);
        com05.para.rst_tim = dlg.m_str.toInt();

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com05));
    }
}
/*************************************************************************
* ��������: on_leSprVal_clicked
* ��    ��: ����������
* �������: ��
* �������: ��
* �� �� ֵ: 
*************************************************************************/
void Frm_ProS::on_leSprVal_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->leSprVal->setText(dlg.m_str);
        com05.para.spr_val = dlg.m_str.toInt();

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com05));
    }
}

//==========================================================================================
// End of file.
//==========================================================================================

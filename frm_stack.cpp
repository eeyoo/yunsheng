/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_stack.cpp

* ��������: �ѵ������ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#include "frm_stack.h"
#include "ui_frm_stack.h"
#include "dlg_manu.h"
#include "tcmd.h"
#include "dlg_psw.h"
#include "twidmana.h"
#include "twarn.h"
#include "dlg_stackmanage.h"
#include "dlg_keyboard.h"

/*************************************************************************
* ��������: Frm_Stack
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Stack::Frm_Stack() :
    
    ui(new Ui::Frm_Stack)
{
    ui->setupUi(this);
    bSve = false;
    //setAutoFillBackground(true);
}
/*************************************************************************
* ��������: ~Frm_Stack
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Stack::~Frm_Stack()
{
    delete ui;
}
/*************************************************************************
* ��������: on_leReadypoint_clicked
* ��    ��: ������ý��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_leReadypoint_clicked()
{
    Dlg_Manu dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted){
        ui->leReadypoint->setText(QString("%1,%2").arg(comF0.rpara.xpos)
                                                     .arg(comF0.rpara.y1pos));
        bSve = false;
    }
}
/*************************************************************************
* ��������: on_leStartPoint_clicked
* ��    ��: ������öѵ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_leStartPoint_clicked()
{
    Dlg_Manu dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted){
        ui->leStartPoint->setText(QString("%1,%2").arg(comF0.rpara.xpos)
                                                     .arg(comF0.rpara.y1pos));
        bSve = false;
    }
}
/*************************************************************************
* ��������: on_leStackSpd_clicked
* ��    ��: ���öѵ��ٶ�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_leStackSpd_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted){
        ui->leStackSpd->setText(dlg.m_str);
        bSve = false;
    }
}
/*************************************************************************
* ��������: on_leStkNumX_clicked
* ��    ��: X����ѵ�����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_leStkNumX_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted){
        ui->leStkNumX->setText(dlg.m_str);
        bSve = false;
    }
}
/*************************************************************************
* ��������: on_leStkInterX_clicked
* ��    ��: X������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_leStkInterX_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted){
        ui->leStkInterX->setText(dlg.m_str);
        bSve = false;
    }
}
/*************************************************************************
* ��������: on_leStkNumY_clicked
* ��    ��: Y����ѵ�����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_leStkNumY_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted){
        ui->leStkNumY->setText(dlg.m_str);
        bSve = false;
    }
}
/*************************************************************************
* ��������: on_leStkInterY_clicked
* ��    ��: Y������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_leStkInterY_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted){
        ui->leStkInterY->setText(dlg.m_str);
        bSve = false;
    }
}
/*************************************************************************
* ��������: GetData
* ��    ��: ��ȡ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::GetData()
{
    QString strT;

    strT = ui->leReadypoint->text();
    for(int i = 0; i < 2; i++){
        com06.para.entP[i] = strT.left(strT.indexOf(",")).toInt();
        strT = strT.right(strT.length() - strT.indexOf(",") - 1);
    }

    strT = ui->leStartPoint->text();
    for(int i = 0; i < 2; i++){
        com06.para.stkP[i] = strT.left(strT.indexOf(",")).toInt();
        strT = strT.right(strT.length() - strT.indexOf(",") - 1);
    }

    strT = ui->leStackSpd->text();
    for(int i = 0; i < 2; i++){
        com06.para.spd[i] = strT.toInt();
    }

    QComboBox* cbbOdr[] = {ui->cbBoxOrderFst1,ui->cbBoxOrderFst2};
    for(int i = 0; i < 2; i++){
        com06.para.odr[i] = cbbOdr[i]->currentIndex() + 1;
    }

    QComboBox* cbbDir[] = {ui->cbBoxOrientX,ui->cbBoxOrientY};
    TLineEdit* leNum[]  = {ui->leStkNumX,ui->leStkNumY};
    TLineEdit* leDis[]  = {ui->leStkInterX,ui->leStkInterY};
    for(int i = 0; i < 2; i++){
        com06.para.opt[i].dir = cbbDir[i]->currentIndex() + 1;
        com06.para.opt[i].num = leNum[i]->text().toInt();
        com06.para.opt[i].dis = leDis[i]->text().toInt();
    }
}
/*************************************************************************
* ��������: SetData
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::SetData()
{
    QString strT;

    strT = QString("%1,%2").arg(com06.para.entP[0])
                              .arg(com06.para.entP[1]);
    ui->leReadypoint->setText(strT);

    strT = QString("%1,%2").arg(com06.para.stkP[0])
                              .arg(com06.para.stkP[1]);
    ui->leStartPoint->setText(strT);

    ui->leStackSpd->setText(QString("%1").arg(com06.para.spd[0]));

    QComboBox* cbbOdr[] = {ui->cbBoxOrderFst1,ui->cbBoxOrderFst2};
    for(int i = 0; i < 2; i++){
        cbbOdr[i]->setCurrentIndex(com06.para.odr[i] - 1);
    }

    QComboBox* cbbDir[] = {ui->cbBoxOrientX,ui->cbBoxOrientY};
    TLineEdit* leNum[]  = {ui->leStkNumX,ui->leStkNumY};
    TLineEdit* leDis[]  = {ui->leStkInterX,ui->leStkInterY};
    for(int i = 0; i < 2; i++){
        cbbDir[i]->setCurrentIndex(com06.para.opt[i].dir - 1);
        leNum[i]->setText(QString("%1").arg(com06.para.opt[i].num));
        leDis[i]->setText(QString("%1").arg(com06.para.opt[i].dis));
    }
}
/*************************************************************************
* ��������: on_btnOk_clicked
* ��    ��: ���ȷ����ť�����Ͷѵ�����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_btnOk_clicked()
{
    if(!bSve){
        warn.ShowW2L(TWarn::W_STK_SVE);
        return;
    }

    GetData();

    switch(stk_t){
    case SET:
        widMana->SwitchWM(this,TWidMana::ST_HIDE);
        break;
    case TEACH:
        widMana->SwitchWM(&widMana->frm_teach);
        break;
    default:
        break;
    }

    //QMutexLocker locker(&mutex_com);
    //pComBuf2.push_back((TCom*)&com06);
}
/*************************************************************************
* ��������: on_btnStkOpen_clicked
* ��    ��: ����򿪰�ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_btnStkOpen_clicked()
{
    Dlg_StackManage dlg;
    dlg.setModal(true);

    if(dlg.exec() == QDialog::Accepted){
        QFile *file = new QFile();
        file->setFileName(QString("%1/%2")
                          .arg(widMana->strStkP).arg(dlg.m_strN));
        file->open(QIODevice::ReadOnly);
        file->reset();

        file->read((char*)(&com06.para),sizeof(com06.para));

        SetData();

        file->close();
        file->deleteLater();

        strN = dlg.m_strN.left(dlg.m_strN.length()-4);
        bSve = true;
    }
}
/*************************************************************************
* ��������: on_btnStkSave_clicked
* ��    ��: ����ѵ�����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_btnStkSave_clicked()
{
    Dlg_Keyboard dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        QFile *file = new QFile();
        file->setFileName(QString("%1/%2.stk")
                          .arg(widMana->strStkP).arg(dlg.m_str));
        file->open(QIODevice::WriteOnly);
        file->reset();

        GetData();

        file->write((char*)(&com06.para),sizeof(com06.para));

        file->close();
        file->deleteLater();

        strN = dlg.m_str;
        bSve = true;

    #ifdef EMBEDED_ARM
        system("sync");
    #endif
    }
}
/*************************************************************************
* ��������: on_btnStkDel_clicked
* ��    ��: ɾ���ѵ�����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_btnStkDel_clicked()
{
    Dlg_StackManage dlg;
    dlg.setModal(true);

    if(dlg.exec() == QDialog::Accepted){
        if(QFile::remove(QString("%1/%2").arg(widMana->strStkP).arg(dlg.m_strN)))
        {
            bSve = false;
            #ifdef EMBEDED_ARM
                system("sync");
            #endif
        }
    }
}
/*************************************************************************
* ��������: on_btnCancel_clicked
* ��    ��: �˳��ѵ�����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Stack::on_btnCancel_clicked()
{
    widMana->SwitchWM(this,TWidMana::ST_HIDE);
}

//==========================================================================================
// End of file.
//==========================================================================================

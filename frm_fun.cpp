/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_fun.cpp

* ��������: ������ѡ���ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/


#include "frm_fun.h"
#include "ui_frm_fun.h"
#include "twidmana.h"
#include "dlg_teach.h"
#include "dlg_psw.h"
#include "dlg_run_mod_sel.h"
#include "dlg_time.h"
#include "dlg_authority.h"
#include "tcmd.h"

/*************************************************************************
* ��������: Frm_Fun
* ��    ��: ���캯��
* �������: 
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Fun::Frm_Fun() :
    ui(new Ui::Frm_Fun)
{
    ui->setupUi(this);
    //setAutoFillBackground(true);
    ui->btnTeach->setFocus();
}
/*************************************************************************
* ��������: ~Frm_Fun
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Fun::~Frm_Fun()
{
    delete ui;
}
/*************************************************************************
* ��������: on_btnTeach_clicked
* ��    ��: ���ʾ�̰�ť������ʾ�̽���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnTeach_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!usr.CheckUsr(TUsr::Administrator))
        return;
    /*Dlg_Teach dlg;
    if(dlg.exec() == QDialog::Accepted)
        widMana->SwitchWM(&widMana->frm_teach);*/
    widMana->SwitchWM(&widMana->frm_prom);
    //ui->btnAuthority->click();
}
/*************************************************************************
* ��������: on_btnSysS_clicked
* ��    ��: ���ϵͳ���ð�ť������ϵͳ���û���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnSysS_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!usr.CheckUsr(TUsr::Administrator))
        return;
    /*Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)*/
        widMana->SwitchWM(&widMana->frm_setup);
}
/*************************************************************************
* ��������: on_btnUsrS_clicked
* ��    ��: ����û����ð�ť�������û����û���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnUsrS_clicked()
{
    /*Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)*/
        //widMana->SwitchWM(&widMana->frm_usrs);
}
/*************************************************************************
* ��������: on_btnRun_clicked
* ��    ��: ������а�ť���������л���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnRun_clicked()
{
    if(!usr.CheckUsr(TUsr::Operator))
        return;
    /*Dlg_Run_Mod_Sel dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        widMana->frm_run.r_model = dlg.r_model;
        switch(dlg.r_model)
        {
        case Frm_Run::R_AUTO:
        case Frm_Run::R_SSTP:
        case Frm_Run::R_SPRD:
            widMana->SwitchWM(&widMana->frm_run);
            break;
        case Frm_Run::R_MANA:
            widMana->SwitchWM(&widMana->frm_mana);
            break;
        default:
            break;
        }
    }*/
    widMana->SwitchWM(&widMana->frm_run);
}
/*************************************************************************
* ��������: on_btnTimS_clicked
* ��    ��: ���ʱ�����ð�ť������ʱ�����û���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnTimS_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!usr.CheckUsr(TUsr::Operator))
        return;

    Dlg_Time dlg;
    dlg.exec();
}
/*************************************************************************
* ��������: on_btnLang_clicked
* ��    ��: ����������ð�ť�������������û���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnLang_clicked()
{
    widMana->SwitchWM(&widMana->frm_lang);
}
/*************************************************************************
* ��������: on_btnPdtS_clicked
* ��    ��: �����Ʒ���ð�ť�������Ʒ���û���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnPdtS_clicked()
{
    widMana->SwitchWM(&widMana->frm_pros);
}
/*************************************************************************
* ��������: on_btnStkS_clicked
* ��    ��: ����ѵ����ð�ť������ѵ�����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnStkS_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;
    if(!usr.CheckUsr(TUsr::Administrator))
        return;

    widMana->frm_stack.stk_t = Frm_Stack::SET;
    widMana->SwitchWM(&widMana->frm_stack);
}
/*************************************************************************
* ��������: on_btnLog_clicked
* ��    ��: ���ϵͳ��Ϣ��ť������ϵͳ��Ϣ����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnLog_clicked()
{
    if(!usr.CheckUsr(TUsr::Operator))
        return;

    widMana->SwitchWM(&widMana->frm_view);
}
/*************************************************************************
* ��������: on_btnMonitor_clicked
* ��    ��: ������Ӱ�ť��������ӻ���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnMonitor_clicked()
{
    if(!usr.CheckUsr(TUsr::Operator))
        return;

    widMana->SwitchWM(&widMana->frm_monit);
}
/*************************************************************************
* ��������: on_btnAuthority_clicked
* ��    ��: ����û�����ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnAuthority_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!usr.CheckUsr(TUsr::Operator))
        return;

    Dlg_Authority dlg;
    dlg.setModal(true);
    dlg.exec();
}
/*************************************************************************
* ��������: on_btnManufacturer_clicked
* ��    ��: �������ά����ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnManufacturer_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!usr.CheckUsr(TUsr::Manufacturer))
        return;

    widMana->SwitchWM(&widMana->frm_mftr);
}
/*************************************************************************
* ��������: on_btnHelp_clicked
* ��    ��: ���������ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::on_btnHelp_clicked()
{
    if(!usr.CheckUsr(TUsr::Operator))
        return;

    widMana->SwitchWM(&widMana->frm_hlp);
}
/*************************************************************************
* ��������: OnQdec
* ��    ��: ��Ӧ��ת����
* �������: qt ��ת�����״̬
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Fun::OnQdec(QDECT qt)
{
    QWidget *pW[] = {(QWidget*)ui->btnTeach,(QWidget*)ui->btnRun,(QWidget*)ui->btnSysS,
                     (QWidget*)ui->btnStkS,(QWidget*)ui->btnTimS,(QWidget*)ui->btnMonitor,
                     (QWidget*)ui->btnLog,(QWidget*)ui->btnAuthority,(QWidget*)ui->btnHelp,
                     (QWidget*)ui->btnManufacturer};

    static QWidget  *pCW = NULL;
    static int      PrsT = 0;    //�������
    static int      iCur = 0;    //��ǰ��ȡ����ؼ�
    static int      iS   = sizeof(pW)/sizeof(QWidget*);
    //�ж��н���Ŀؼ�
    for(iCur = 0; iCur < iS; iCur++){
        if(pW[iCur]->hasFocus()){
            break;
        }
    }

    /*switch(qt){
    case AHD:
        iCur++;
        if(iCur >= iSize)
            iCur = 0;

        btn[iCur]->setFocus();
        break;
    case BCK:
        iCur--;
        if(iCur < 0)
            iCur = iSize - 1;

        btn[iCur]->setFocus();
        break;
    case PRS:
        if(iCur >= 0 && iCur < iSize)
            btn[iCur]->click();
        break;
    default:
        break;
    }*/
    switch(qt){
    case AHD:
        if((PrsT > 0) && (pCW == pW[iCur])){
            DoAhd(pCW,&PrsT);
        }else{
            PrsT = 0;
            iCur++;
            iCur %= iS;

            pW[iCur]->setFocus();
        }
        break;
    case BCK:
        if((PrsT > 0) && (pCW == pW[iCur])){
            DoBck(pCW,&PrsT);
        }else{
            PrsT = 0;
            iCur--;
            if(iCur < 0)
                iCur = iS -1;

            pW[iCur]->setFocus();
        }
        break;
    case PRS:
        if(iCur >= 0 && iCur < iS){
            if(DoPrs(pW[iCur],&PrsT)){
                pCW = pW[iCur];
                PrsT++;
            }else{
                pCW = NULL;
                PrsT = 0;
            }
        }
        break;
    default:
        break;
    }
}

//==========================================================================================
// End of file.
//==========================================================================================

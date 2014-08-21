/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_fun.cpp

* 功能描述: 主功能选择文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
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
* 函数名称: Frm_Fun
* 功    能: 构造函数
* 输入参数: 
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_Fun::Frm_Fun() :
    ui(new Ui::Frm_Fun)
{
    ui->setupUi(this);
    //setAutoFillBackground(true);
    ui->btnTeach->setFocus();
}
/*************************************************************************
* 函数名称: ~Frm_Fun
* 功    能: 析构函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_Fun::~Frm_Fun()
{
    delete ui;
}
/*************************************************************************
* 函数名称: on_btnTeach_clicked
* 功    能: 点击示教按钮，进入示教界面
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: on_btnSysS_clicked
* 功    能: 点击系统设置按钮，进入系统设置画面
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: on_btnUsrS_clicked
* 功    能: 点击用户设置按钮，进入用户设置画面
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Fun::on_btnUsrS_clicked()
{
    /*Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)*/
        //widMana->SwitchWM(&widMana->frm_usrs);
}
/*************************************************************************
* 函数名称: on_btnRun_clicked
* 功    能: 点击运行按钮，进入运行画面
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: on_btnTimS_clicked
* 功    能: 点击时间设置按钮，进入时间设置画面
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: on_btnLang_clicked
* 功    能: 点击语言设置按钮，进入语言设置画面
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Fun::on_btnLang_clicked()
{
    widMana->SwitchWM(&widMana->frm_lang);
}
/*************************************************************************
* 函数名称: on_btnPdtS_clicked
* 功    能: 点击产品设置按钮，进入产品设置画面
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Fun::on_btnPdtS_clicked()
{
    widMana->SwitchWM(&widMana->frm_pros);
}
/*************************************************************************
* 函数名称: on_btnStkS_clicked
* 功    能: 点击堆叠设置按钮，进入堆叠画面
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: on_btnLog_clicked
* 功    能: 点击系统信息按钮，进入系统信息画面
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Fun::on_btnLog_clicked()
{
    if(!usr.CheckUsr(TUsr::Operator))
        return;

    widMana->SwitchWM(&widMana->frm_view);
}
/*************************************************************************
* 函数名称: on_btnMonitor_clicked
* 功    能: 点击监视按钮，进入监视画面
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Fun::on_btnMonitor_clicked()
{
    if(!usr.CheckUsr(TUsr::Operator))
        return;

    widMana->SwitchWM(&widMana->frm_monit);
}
/*************************************************************************
* 函数名称: on_btnAuthority_clicked
* 功    能: 点击用户管理按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: on_btnManufacturer_clicked
* 功    能: 点击厂家维护按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: on_btnHelp_clicked
* 功    能: 点击帮助按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Fun::on_btnHelp_clicked()
{
    if(!usr.CheckUsr(TUsr::Operator))
        return;

    widMana->SwitchWM(&widMana->frm_hlp);
}
/*************************************************************************
* 函数名称: OnQdec
* 功    能: 响应旋转编码
* 输入参数: qt 旋转编码的状态
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Fun::OnQdec(QDECT qt)
{
    QWidget *pW[] = {(QWidget*)ui->btnTeach,(QWidget*)ui->btnRun,(QWidget*)ui->btnSysS,
                     (QWidget*)ui->btnStkS,(QWidget*)ui->btnTimS,(QWidget*)ui->btnMonitor,
                     (QWidget*)ui->btnLog,(QWidget*)ui->btnAuthority,(QWidget*)ui->btnHelp,
                     (QWidget*)ui->btnManufacturer};

    static QWidget  *pCW = NULL;
    static int      PrsT = 0;    //点击次数
    static int      iCur = 0;    //当前获取焦点控件
    static int      iS   = sizeof(pW)/sizeof(QWidget*);
    //判断有焦点的控件
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

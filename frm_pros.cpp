/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_pros.cpp

* 功能描述: 产品设置文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/


#include "frm_pros.h"
#include "ui_frm_pros.h"
#include "dlg_psw.h"
#include "tcom.h"

/*************************************************************************
* 函数名称: Frm_ProS
* 功    能: 构造函数
* 输入参数: 
* 输出参数: 无
* 返 回 值: 
*************************************************************************/
Frm_ProS::Frm_ProS() :
    
    ui(new Ui::Frm_ProS)
{
    ui->setupUi(this);
    //setAutoFillBackground(true);
}
/*************************************************************************
* 函数名称: ~Frm_ProS
* 功    能: 析构函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 
*************************************************************************/
Frm_ProS::~Frm_ProS()
{
    delete ui;
}
/*************************************************************************
* 函数名称: on_lePlnPrd_clicked
* 功    能: 输入计划生产数量
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 
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
* 函数名称: on_leBadPrd_clicked
* 功    能: 输入不良生产数量
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 
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
* 函数名称: on_leCirTim_clicked
* 功    能: 输入循环超时
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 
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
* 函数名称: on_leRstTim_clicked
* 功    能: 输入复位时间
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 
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
* 函数名称: on_leSprVal_clicked
* 功    能: 输入喷雾间隔
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 
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

/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_run.cpp

* 功能描述: 程序运行画面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#include "frm_run.h"
#include "ui_frm_run.h"
#include "tcmd.h"
#include "twarn.h"
#include "tconfig.h"
#include "dlg_authority.h"

/*************************************************************************
* 函数名称: Frm_Run
* 功    能: 构造函数
* 输入参数: parent
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_Run::Frm_Run() :
    
    ui(new Ui::Frm_Run)
{
    ui->setupUi(this);
    //setAutoFillBackground(true);

    ui->tblV_Pro->setModel(com20.modelPro);
    ui->tblV_Pro->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tblV_Pro->setSelectionMode(QAbstractItemView::NoSelection);
    //ui->tblV_Pro->setStyleSheet("selection-background-color: green");
    //ui->tblV_Pro->setAlternatingRowColors(true);
    //ui->tblV_Pro->setStyleSheet("QTableView{background-color: rgb(250, 250, 115);"
    //                            "alternate-background-color: rgb(141, 163, 215);}");
    ui->tblV_Pro->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblV_Pro->setIconSize(QSize(42,42));

    ui->tblV_Pro->setColumnWidth(0,80);
    ui->tblV_Pro->setColumnWidth(1,50);
    ui->tblV_Pro->setColumnWidth(2,300);
    ui->tblV_Pro->horizontalHeader()->hide();

    ui->tblV_Pro->setFocus(Qt::MouseFocusReason);
    ui->tblV_Pro->verticalHeader()->setResizeMode(0,QHeaderView::Fixed);
    ui->tblV_Pro->verticalHeader()->setResizeMode(1,QHeaderView::Fixed);


}
/*************************************************************************
* 函数名称: ~Frm_Run
* 功    能: 析构函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_Run::~Frm_Run()
{
    delete ui;
}
/*************************************************************************
* 函数名称: setVisible
* 功    能: 初始化窗口显示，设置程序行的宽度
* 输入参数: visible	true显示，false隐藏
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Run::setVisible(bool visible)
{
    QWidget::setVisible(visible);

    if(visible)
    {
        ui->tblV_Pro->setColumnWidth(0,80);
        ui->tblV_Pro->setColumnWidth(1,50);
        ui->tblV_Pro->setColumnWidth(2,300);
        ui->tblV_Pro->horizontalHeader()->hide();

        for(int i = 0;i<com20.modelPro->rowCount();i++)
        {
            ui->tblV_Pro->setRowHeight(i,50);
            /*QStandardItem *item = modelPro->item(i,0);
            if(((TCmd*)item)->cmd_wid == TCmd::WID_MOVES)
            {
                ui->tableView->setSpan(i,0,2,1);
            }*/
        }
    }
    ui->tblV_Pro->selectRow(0);

    m_iSAdr = 1;
}
/*************************************************************************
* 函数名称: UpdateUI
* 功    能: 根据接收的数据更新UI
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Run::UpdateUI()
{
    ui->tblV_Pro->selectRow(comF0.rpara.radd);
    QCheckBox *cb[] = {ui->cb1,ui->cb2,ui->cb3,ui->cb4,ui->cb5,ui->cb6,ui->cb7};
    int iNum = 0, iPos = 0;
    for(int i = 0; i < sizeof(cb)/sizeof(QCheckBox*); i++){
        iNum = i/8; iPos = i%8;
        cb[i]->setChecked((comF0.rpara.in[iNum] >> iPos) & 0x01);
    }

    //printf("radd:%d,rc:%d\n",comF0.rpara.radd,com20.modelPro->rowCount());
    static bool bsrt = true;
    if(bsrt){
        prdTim.start();
        bsrt = false;
    }
    static bool bCount = false;
    if(comF0.rpara.radd != 1)
        bCount = true;

    if(comF0.rpara.radd == 1 && bCount){
        ui->leFinish->setText(QString("%1").arg(config.cfg.curPrd));
        ui->leRemain->setText(QString("%1").arg(com05.para.pln_prd - config.cfg.curPrd));
        ui->lePrdTim->setText(QString("%1").arg(prdTim.restart() / 1000));
        config.cfg.curPrd++;

        bCount = false;
    }
}
/*************************************************************************
* 函数名称: on_tblV_Pro_clicked
* 功    能: 点击示教程序，发送单步指令
* 输入参数: index	点击的命令行
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Run::on_tblV_Pro_clicked(QModelIndex index)
{
    /*if(r_model == R_SSTP)
    {
        if(m_iSAdr >= com20.modelPro->rowCount()-1)
            m_iSAdr=1;

        comE0.para.adr      = m_iSAdr;
        comE0.para.runtype  = TComE0::SGL_STP;
        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)&comE0);

        m_iSAdr++;
    }*/
}
/*************************************************************************
* 函数名称: on_btnDld_clicked
* 功    能: 下载程序
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Run::on_btnDld_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    //warn.ShowW2L(0);
    QMutexLocker locker(&mutex_com);
    if(com20.bNewForSnd)
    {
        memcpy(&com06.para,&comStk.para,sizeof(com06.para));

        /*for(int i = 1; i < com20.modelPro->rowCount() - 1; i++){
            TCmd *itemCmd=(TCmd*)com20.modelPro->item(i,1);
            if(itemCmd->para.action == TCmd::STACK){
                pComBuf2.push_back((TCom*)&com06);
                break;
            }
        }*/
        //com20.bNewForSnd = false;
        pComBuf2.push_back((TCom*)&com06);

        pComBuf2.push_back((TCom*)&com20);
    }
}
/*************************************************************************
* 函数名称: on_btnSPrd_clicked
* 功    能: 单周期
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Run::on_btnSPrd_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!widMana->bTri)
        return;

    QMutexLocker locker(&mutex_com);
    comE0.para.runtype  = TComE0::SGL_CYCLE;
    pComBuf2.push_back((TCom*)&comE0);
}
/*************************************************************************
* 函数名称: on_btnSStp_clicked
* 功    能: 单步运行
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Run::on_btnSStp_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;
    if(!widMana->bTri)
        return;

    if(m_iSAdr >= com20.modelPro->rowCount()-1)
        m_iSAdr=1;

    comE0.para.adr      = m_iSAdr;
    comE0.para.runtype  = TComE0::SGL_STP;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)&comE0);

    m_iSAdr++;
}

//==========================================================================================
// End of file.
//==========================================================================================

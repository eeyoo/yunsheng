/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_generrelayoutput.cpp

* 功能描述: 输出设置

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.8.20

* 修	改:
**************************************************************************************/

#include "dlg_generrelayoutput.h"
#include "ui_dlg_generrelayoutput.h"
#include "twidmana.h"
#include "treadcmd.h"
#include "qa5driver.h"

/*************************************************************************
* 函数名称: Dlg_GenerRelayOutput
* 功   能: 构造函数
* 输入参数: QWidget *parent 父类句柄
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_GenerRelayOutput::Dlg_GenerRelayOutput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_GenerRelayOutput)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    a5drv.buzzer_off();

    QPushButton *btn[] = {ui->O1,ui->O2,ui->O3,ui->O4,ui->O5,ui->O6,ui->O7,ui->O8};
    for(int i = 0;i<sizeof(btn)/sizeof(QPushButton*);i++)
    {
        sglMapL.setMapping(btn[i],i);
        connect(btn[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));

        if(i < readCmd.CmdO.size()){
            btn[i]->setText(readCmd.CmdO[i].cmdTil);
        }
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_btn_clicked(int)));

    widMana->bDialog = true;
}
/*************************************************************************
* 函数名称: Dlg_GenerRelayOutput
* 功   能: 析构函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_GenerRelayOutput::~Dlg_GenerRelayOutput()
{
    widMana->bDialog = false;
    delete ui;
}
/*************************************************************************
* 函数名称: on_btn_clicked
* 功    能: 响应QPushButton点击事件
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_GenerRelayOutput::on_btn_clicked(int ibtn)
{
    QPushButton *btn[] = {ui->O1,ui->O2,ui->O3,ui->O4,ui->O5,ui->O6,ui->O7,ui->O8};

    QString strBtn = btn[ibtn]->objectName();
    strBtn = strBtn.right(strBtn.length()-1);
    iO = strBtn.toInt() - 1;

    widMana->bDialog = false;
    QDialog::accept();
}
/*************************************************************************
* 函数名称: on_btnOk_clicked
* 功   能: 点击确定按钮
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_GenerRelayOutput::on_btnOk_clicked()
{
    QDialog::reject();
}
/*************************************************************************
* 函数名称: on_btnCancel_clicked
* 功   能: 点击取消按钮
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_GenerRelayOutput::on_btnCancel_clicked()
{
    QDialog::reject();
}

//==========================================================================================
// End of file.
//==========================================================================================

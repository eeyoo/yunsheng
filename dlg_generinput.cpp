/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_generinput.cpp

* 功能描述: 输入设置

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.8.20

* 修	改:
**************************************************************************************/

#include "dlg_generinput.h"
#include "ui_dlg_generinput.h"
#include "twidmana.h"
#include "treadcmd.h"
#include "qa5driver.h"

/*************************************************************************
* 函数名称: Dlg_GenerInput
* 功   能: 构造函数
* 输入参数: QWidget *parent 父类句柄
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_GenerInput::Dlg_GenerInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_GenerInput)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    a5drv.buzzer_off();

    QPushButton *btn[] = {ui->I1,ui->I2,ui->I3,ui->I4,ui->I5,ui->I6,ui->I7,
                          ui->I8,ui->I9,ui->I10,ui->I11,ui->I12,ui->I13,ui->I14,
                          ui->I15,ui->I16,ui->I17,ui->I18,ui->I19,ui->I20,ui->I21,
                          ui->I22,ui->I23,ui->I24,ui->I25,ui->I26,ui->I27,ui->I28,
                          ui->I29,ui->I30,ui->I31,ui->I32,ui->I33,ui->I34};
    for(int i = 0;i<sizeof(btn)/sizeof(QPushButton*);i++)
    {
        sglMapL.setMapping(btn[i],i);
        connect(btn[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));

        if(i < readCmd.CmdI.size()){
            btn[i]->setText(readCmd.CmdI[i].cmdTil);
        }
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_btn_clicked(int)));

    widMana->bDialog = true;
}
/*************************************************************************
* 函数名称: Dlg_GenerInput
* 功   能: 析构函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_GenerInput::~Dlg_GenerInput()
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
void Dlg_GenerInput::on_btn_clicked(int ibtn)
{
    iI = ibtn;
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
void Dlg_GenerInput::on_btnOk_clicked()
{
    QDialog::reject();
}
/*************************************************************************
* 函数名称: on_btnCancel_clicked
* 功   能: 点击取消按钮
* 输入参数: QWidget *parent 父类句柄
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_GenerInput::on_btnCancel_clicked()
{
    QDialog::reject();
}

//==========================================================================================
// End of file.
//==========================================================================================

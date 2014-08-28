/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_genercrysoutput.cpp

* 功能描述: 输出设置

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.8.20

* 修	改:
**************************************************************************************/

#include "dlg_genercrysoutput.h"
#include "ui_dlg_genercrysoutput.h"
#include "twidmana.h"
#include "qa5driver.h"

/*************************************************************************
* 函数名称: Dlg_GenerCrysOutput
* 功   能: 构造函数
* 输入参数: QWidget *parent 父类句柄
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_GenerCrysOutput::Dlg_GenerCrysOutput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_GenerCrysOutput)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    a5drv.buzzer_off();

    QPushButton *btn[] = {ui->O9,ui->O10,ui->O11,ui->O12,ui->O13,ui->O14,ui->O15,ui->O16,
                          ui->O17,ui->O18,ui->O19,ui->O20,ui->O21,ui->O22,ui->O23,ui->O24,
                          ui->O25,ui->O26};
    for(int i = 0;i<sizeof(btn)/sizeof(QPushButton*);i++)
    {
        sglMapL.setMapping(btn[i],i);
        connect(btn[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));

        if((i + 8) < readCmd.CmdO.size()){
            btn[i]->setText(readCmd.CmdO[i + 8].cmdTil);
        }
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_btn_clicked(int)));

    widMana->bDialog = true;
}
/*************************************************************************
* 函数名称: Dlg_GenerCrysOutput
* 功   能: 析构函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_GenerCrysOutput::~Dlg_GenerCrysOutput()
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
void Dlg_GenerCrysOutput::on_btn_clicked(int ibtn)
{
    QPushButton *btn[] = {ui->O9,ui->O10,ui->O11,ui->O12,ui->O13,ui->O14,ui->O15,ui->O16,
                          ui->O17,ui->O18,ui->O19,ui->O20,ui->O21,ui->O22,ui->O23,ui->O24,
                          ui->O25,ui->O26};

    QString strBtn = btn[ibtn]->objectName();
    strBtn = strBtn.right(strBtn.length()-1);
    iO = strBtn.toInt() - 1;

    widMana->bDialog = false;
    QDialog::accept();
}
/*************************************************************************
* 函数名称: on_btnCancel_clicked
* 功   能: 点击取消按钮
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_GenerCrysOutput::on_btnCancel_clicked()
{
    QDialog::reject();
}
/*************************************************************************
* 函数名称: on_btnOk_clicked
* 功   能: 点击确定按钮
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_GenerCrysOutput::on_btnOk_clicked()
{
    QDialog::reject();
}

//==========================================================================================
// End of file.
//==========================================================================================

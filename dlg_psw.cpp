/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_psw.cpp

* 功能描述: 数字键盘文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#include "dlg_psw.h"
#include "ui_dlg_psw.h"
#include "qa5driver.h"
#include "twidmana.h"
/*************************************************************************
* 函数名称: Dlg_Psw
* 功    能: 构造函数，初始化QPushButton消息数组
* 输入参数: QWidget *parent
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Psw::Dlg_Psw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Psw)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    QPushButton *btn[] = {ui->btn46,ui->btn48,ui->btn49,ui->btn50,ui->btn51,
                        ui->btn52,ui->btn53,ui->btn54,ui->btn55,ui->btn56,ui->btn57};
    for(int i = 0;i<sizeof(btn)/sizeof(QPushButton*);i++)
    {
        sglMapL.setMapping(btn[i],i);
        connect(btn[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_btn_clicked(int)));

    a5drv.buzzer_off();
    widMana->bDialog = true;
}
/*************************************************************************
* 函数名称: ~Dlg_Psw
* 功    能: 析构函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Psw::~Dlg_Psw()
{
    delete ui;
}
/*************************************************************************
* 函数名称: on_btn_clicked
* 功    能: 响应QPushButton点击事件
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Psw::on_btn_clicked(int ibtn)
{
    QPushButton *btn[] = {ui->btn46,ui->btn48,ui->btn49,ui->btn50,ui->btn51,
                        ui->btn52,ui->btn53,ui->btn54,ui->btn55,ui->btn56,ui->btn57};
    QString strBtn = btn[ibtn]->objectName();
    strBtn = strBtn.right(strBtn.length()-3);

    quint8 asc = (quint8)strBtn.toInt();
    m_str = ui->le_input->text();
    m_str += asc;

    ui->le_input->setText(m_str);
}
/*************************************************************************
* 函数名称: on_btnOK_K_clicked
* 功    能: 点击确定按钮，退出
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Psw::on_btnOK_K_clicked()
{
    widMana->bDialog = false;
    QDialog::accept();
}
/*************************************************************************
* 函数名称: on_btnQuit_K_clicked
* 功    能: 点击退出按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Psw::on_btnQuit_K_clicked()
{
    widMana->bDialog = false;
    QDialog::reject();
}
/*************************************************************************
* 函数名称: on_btnBack_clicked
* 功    能: 点击退格按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Psw::on_btnBack_clicked()
{
    m_str = ui->le_input->text();
    m_str = m_str.left(m_str.length()-1);
    ui->le_input->setText(m_str);
}

//==========================================================================================
// End of file.
//==========================================================================================

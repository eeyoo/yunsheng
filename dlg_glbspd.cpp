/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_glbspd.cpp

* 功能描述: 自定义仪表控件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include <QtGui>

#include "dlg_glbspd.h"
#include "ui_dlg_glbspd.h"
#include "dashboard.h"
#include "dlg_psw.h"
#include "tcmd.h"
#include "twidmana.h"

/*************************************************************************
* 函数名称: Dlg_GlbSpd
* 功   能: 构造函数
* 输入参数: QWidget *parent 父类句柄
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_GlbSpd::Dlg_GlbSpd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_GlbSpd),
    mVal(0.0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->leGlbSpd->setText(QString("%1").arg(com02.para[0].whlvel));

    //Dashboard board(ui->spdWidget);
    mBoard = new Dashboard(ui->spdWidget);
    connect(ui->leGlbSpd, SIGNAL(textChanged(QString)), mBoard, SLOT(setHand(QString)));
    //connect(ui->btnAdd, SIGNAL(clicked()), mBoard, SLOT(setHand(QString)));
    mBoard->show();
    mBoard->setHand(ui->leGlbSpd->text());

    widMana->bDialog = true;
}
/*************************************************************************
* 函数名称: Dlg_GlbSpd
* 功   能: 析构函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_GlbSpd::~Dlg_GlbSpd()
{
    delete ui;
}
/*************************************************************************
* 函数名称: on_btnOk_clicked
* 功   能: 点击确定按钮
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_GlbSpd::on_btnOk_clicked()
{
    for(int i = 0; i < 5; i++)
        com02.para[0].whlvel = ui->leGlbSpd->text().toInt();
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)&com02);

    widMana->SavePara();
    widMana->InitParaUI();

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
void Dlg_GlbSpd::on_btnCancel_clicked()
{
    widMana->bDialog = false;
    QDialog::reject();
}
/*************************************************************************
* 函数名称: on_btnAdd_clicked
* 功   能: 增加指针
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_GlbSpd::on_btnAdd_clicked()
{
    mVal = ui->leGlbSpd->text().toInt();
    mVal++;
    if (mVal > 100)
        mVal = 100;
    //mVal++;
    ui->leGlbSpd->setText(QString::number(mVal));

    //qDebug() << QString::number(mVal);
}
/*************************************************************************
* 函数名称: on_btnSub_clicked
* 功   能: 减少指针
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_GlbSpd::on_btnSub_clicked()
{
    mVal = ui->leGlbSpd->text().toInt();

    mVal--;
    if (mVal < 0)
        mVal = 0;
    //mVal--;
    ui->leGlbSpd->setText(QString::number(mVal));
    //qDebug() << QString::number(mVal);
}
/*************************************************************************
* 函数名称: on_leGlbSpd_clicked
* 功   能: 点击文本框，输入指针值
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_GlbSpd::on_leGlbSpd_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec()==QDialog::Accepted)
    {
        if(dlg.m_str.toInt() > 100)
            return;

        ui->leGlbSpd->setText(dlg.m_str);
    }
}

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_time.cpp

* 功能描述: 时间设置文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#include "dlg_time.h"
#include "ui_dlg_time.h"
#include "qa5driver.h"
#include "twidmana.h"
#include "analogclock.h"

#include <cmath>
#include <QTime>
#include <QDate>
/*************************************************************************
* 函数名称: Dlg_Time
* 功    能: 构造函数
* 输入参数: QWidget *parent
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Time::Dlg_Time(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Time)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    clock = new AnalogClock(ui->widget);
    clock->show();

    a5drv.buzzer_off();
    /*QString strT;
    for(int i=0;i<360;i++){
        QString str=QString("%1,").arg(sin((double)i*3.1415/180));
        strT += str;

        if(i%10 == 0)
            strT += "\n";
    }
    ui->te->setText(strT);*/
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    ui->de->setDate(date);
    ui->te->setTime(time);

    connect(ui->btnDateAdd, SIGNAL(clicked()), ui->de, SLOT(stepUp()));
    connect(ui->btnDateSub, SIGNAL(clicked()), ui->de, SLOT(stepDown()));

    connect(ui->btnTimeAdd, SIGNAL(clicked()), ui->te, SLOT(stepUp()));
    connect(ui->btnTimeSub, SIGNAL(clicked()), ui->te, SLOT(stepDown()));

    widMana->bDialog = true;
}
/*************************************************************************
* 函数名称: ~Dlg_Time
* 功    能: 析构函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Time::~Dlg_Time()
{
    delete ui;
}
/*************************************************************************
* 函数名称: on_btnQuit_clicked
* 功    能: 退出，不设置时间
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Time::on_btnQuit_clicked()
{
    widMana->bDialog = false;
    QDialog::reject();

}
/*************************************************************************
* 函数名称: on_btnOK_clicked
* 功    能: 设置时间
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Time::on_btnOK_clicked()
{
    QDate date = ui->de->date();
    QTime time = ui->te->time();

    QString strTim=QString("date -s ");
    QString str;
    str = QString("%1.").arg(date.year());
    strTim += str;

    if(date.month() < 10)
        str = QString("0%1.").arg(date.month());
    else
        str = QString("%1.").arg(date.month());
    strTim += str;

    if(date.day() < 10)
        str = QString("0%1-").arg(date.day());
    else
        str = QString("%1-").arg(date.day());
    strTim += str;

    if(time.hour() < 10)
        str = QString("0%1:").arg(time.hour());
    else
        str = QString("%1:").arg(time.hour());
    strTim += str;

    if(time.minute() < 10)
        str = QString("0%1:").arg(time.minute());
    else
        str = QString("%1:").arg(time.minute());
    strTim += str;

    if(time.second() < 10)
        str = QString("0%1").arg(time.second());
    else
        str = QString("%1").arg(time.second());
    strTim += str;

#ifdef EMBEDED_ARM
    system(strTim.toLatin1().data());
    system("hwclock -w");
#endif

    widMana->bDialog = false;
    QDialog::accept();
}

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_reset.cpp

* 功能描述: 复位界面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include "dlg_reset.h"
#include "ui_dlg_reset.h"
#include "twidmana.h"
#include "tcmd.h"

#include <QTimer>


/*************************************************************************
* 函数名称: Dlg_Reset
* 功   能: 构造函数
* 输入参数: QWidget *parent 父类句柄
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Reset::Dlg_Reset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Reset)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    widMana->bDialog = true;
}
/*************************************************************************
* 函数名称: Dlg_Reset
* 功   能: 析构函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Reset::~Dlg_Reset()
{
    delete ui;
}
/*************************************************************************
* 函数名称: on_btnOK_clicked
* 功   能: 开始复位
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Reset::on_btnOK_clicked()
{
    QMutexLocker locker(&mutex_com);
    memset(&comE0.para,sizeof(comE0.para),0);
    comE0.para.runtype  = TComE0::REST;
    pComBuf2.push_back((TCom*)&comE0);


    QTimer *timer = new QTimer(this);
    timer->start(1000);//一秒钟
    connect(timer,SIGNAL(timeout()),this,SLOT(UpdateSet()));
}
/*************************************************************************
* 函数名称: UpdateSet
* 功    能: 更新复位显示
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Reset::UpdateSet()
{
    static int iT = 0;
    QString strT = QObject::tr("复位中，请稍后");
    for(int i = 0; i < iT; i++){
        strT += QString(".");
    }
    ui->lblT->setText(strT);

    iT++;
    iT%=6;

    if(chkRstOK()){
        QDialog::accept();

        widMana->bDialog = false;
    }
}
/*************************************************************************
* 函数名称: chkRstOK
* 功    能: 判断复位是否成功
* 输入参数: 无
* 输出参数: 无
* 返 回 值: true 成功， false 失败
*************************************************************************/
bool Dlg_Reset::chkRstOK()
{
    /*quint8 axisp[] = {com02.para[0].axisp,com02.para[1].axisp,com02.para[2].axisp,
                      com02.para[3].axisp,com02.para[4].axisp};
    quint32 pos[] = {comF0.rpara.xpos,comF0.rpara.y1pos,comF0.rpara.z1pos,
                    comF0.rpara.y2pos,comF0.rpara.z2pos};

    for(int i = 0; i < sizeof(axisp)/sizeof(quint8); i++){
        if((axisp[i] == TCom02::ENABLE) && (pos[i] != 0)){
            return false;
        }
    }*/
    if(comF0.rpara.sub_sta == TComF0::IDLE)
        return true;
    else
        return false;
}
/*************************************************************************
* 函数名称: on_btnQuit_clicked
* 功   能: 取消复位操作
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Reset::on_btnQuit_clicked()
{
    QDialog::reject();
    widMana->bDialog = false;

    QMutexLocker locker(&mutex_com);
    memset(&comE0.para,sizeof(comE0.para),0);
    comE0.para.runtype  = TComE0::STOP;
    pComBuf2.push_back((TCom*)&comE0);
}

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_mana.cpp

* 功能描述: 手动运行画面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/


#include "frm_mana.h"
#include "ui_frm_mana.h"
#include "tcmd.h"
/*************************************************************************
* 函数名称: Frm_Mana
* 功    能: 构造函数
* 输入参数: 
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_Mana::Frm_Mana() :
    
    ui(new Ui::Frm_Mana)
{
    ui->setupUi(this);
    //setAutoFillBackground(true);

    InitRbSig();
    InitCbSig();
}
/*************************************************************************
* 函数名称: ~Frm_Mana
* 功    能: 析构函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_Mana::~Frm_Mana()
{
    delete ui;
}
/*************************************************************************
* 函数名称: InitRbSig
* 功    能: 初始化QRadioButton消息数组
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Mana::InitRbSig()
{
    QRadioButton *rb[] = {ui->rb1,ui->rb2,ui->rb3,ui->rb4,ui->rb5,ui->rb6,ui->rb7};
    for(int i = 0;i<sizeof(rb)/sizeof(QRadioButton*);i++)
    {
        sglMapRb.setMapping(rb[i],i);
        connect(rb[i], SIGNAL(clicked()), &sglMapRb, SLOT(map()));
    }
    connect(&sglMapRb,SIGNAL(mapped(int)),this,SLOT(on_rb_clicked(int)));
}
/*************************************************************************
* 函数名称: InitCbSig
* 功    能: 初始化QCheckBox消息数组
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Mana::InitCbSig()
{
    QCheckBox *cb[] = {ui->cb1,ui->cb2,ui->cb3,ui->cb4,ui->cb5,ui->cb6,
                        ui->cb7,ui->cb8,ui->cb9,ui->cb10,ui->cb11};
    for(int i = 0;i<sizeof(cb)/sizeof(QCheckBox*);i++)
    {
        sglMapCb.setMapping(cb[i],i);
        connect(cb[i], SIGNAL(clicked()), &sglMapCb, SLOT(map()));
    }
    connect(&sglMapCb,SIGNAL(mapped(int)),this,SLOT(on_cb_clicked(int)));
}
/*************************************************************************
* 函数名称: on_rb_clicked
* 功    能: 响应QRadioButton点击事件
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Mana::on_rb_clicked(int irb)
{
    QRadioButton *rb[] = {ui->rb1,ui->rb2,ui->rb3,ui->rb4,ui->rb5,ui->rb6,ui->rb7};
    if(rb[irb]->isChecked())
    {
        iCurCmd = irb;
    }
}
/*************************************************************************
* 函数名称: on_cb_clicked
* 功    能: 响应QCheckBox点击事件
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Mana::on_cb_clicked(int icb)
{
    QCheckBox *cb[] = {ui->cb1,ui->cb2,ui->cb3,ui->cb4,ui->cb5,ui->cb6,
                        ui->cb7,ui->cb8,ui->cb9,ui->cb10,ui->cb11};
    //cmd_Out->para.action = TCmd::ROT+icb;
    cmd_Out->para.dist    = cb[icb]->checkState()?1:0;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)cmd_Out);
}

//==========================================================================================
// End of file.
//==========================================================================================

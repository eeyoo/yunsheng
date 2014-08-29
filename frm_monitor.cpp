/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: Frm_Monitor.cpp

* 功能描述: 监视画面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include "frm_monitor.h"
#include "ui_frm_monitor.h"
#include "tcmd.h"
#include "treadcmd.h"

/*************************************************************************
* 函数名称: Frm_Monitor
* 功   能: 构造函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_Monitor::Frm_Monitor() :
    
    ui(new Ui::Frm_Monitor)
{
    ui->setupUi(this);

    /*QCheckBox *cbO[] = {ui->cbO1,ui->cbO2,ui->cbO3,ui->cbO4,ui->cbO5,ui->cbO6,ui->cbO7,
                       ui->cbO8,ui->cbO9,ui->cbO10,ui->cbO11,ui->cbO12,ui->cbO13,ui->cbO14,
                       ui->cbO15,ui->cbO16,ui->cbO17,ui->cbO18,ui->cbO19,ui->cbO20,ui->cbO21,
                       ui->cbO22,ui->cbO23,ui->cbO24,ui->cbO25,ui->cbO26,ui->cbO27,ui->cbO28};
    for(int i = 0;i<sizeof(cbO)/sizeof(QCheckBox*);i++)
    {
        sglMapCb.setMapping(cbO[i],i);
        connect(cbO[i], SIGNAL(clicked()), &sglMapCb, SLOT(map()));
    }
    connect(&sglMapCb,SIGNAL(mapped(int)),this,SLOT(on_cbO_clicked(int)));*/
    QCheckBox *cbI[] = {ui->cbI1,ui->cbI2,ui->cbI3,ui->cbI4,ui->cbI5,ui->cbI6,ui->cbI7,
                       ui->cbI8,ui->cbI9,ui->cbI10,ui->cbI11,ui->cbI12,ui->cbI13,ui->cbI14,
                       ui->cbI15,ui->cbI16,ui->cbI17,ui->cbI18,ui->cbI19,ui->cbI20,ui->cbI21,
                       ui->cbI22,ui->cbI23,ui->cbI24,ui->cbI25,ui->cbI26,ui->cbI27,ui->cbI28,
                       ui->cbI29,ui->cbI30,ui->cbI31,ui->cbI32,ui->cbI33,ui->cbI34,ui->cbI35,
                       ui->cbI36,ui->cbI37,ui->cbI38,ui->cbI39,ui->cbI40,ui->cbI41,ui->cbI42,
                       ui->cbI43,ui->cbI44};

    QCheckBox *cbO[] = {ui->cbO1,ui->cbO2,ui->cbO3,ui->cbO4,ui->cbO5,ui->cbO6,ui->cbO7,
                       ui->cbO8,ui->cbO9,ui->cbO10,ui->cbO11,ui->cbO12,ui->cbO13,ui->cbO14,
                       ui->cbO15,ui->cbO16,ui->cbO17,ui->cbO18,ui->cbO19,ui->cbO20,ui->cbO21,
                       ui->cbO22,ui->cbO23,ui->cbO24,ui->cbO25,ui->cbO26,ui->cbO27,ui->cbO28};

    for(int i = 0; i < sizeof(cbI)/sizeof(QCheckBox*); i++){
        if(i < readCmd.CmdI.size()){
            cbI[i]->setText(readCmd.CmdI[i].cmdTil);
        }
    }

    for(int i = 0; i < sizeof(cbO)/sizeof(QCheckBox*); i++){
        if(i < readCmd.CmdO.size()){
            cbO[i]->setText(readCmd.CmdO[i].cmdTil);
        }
    }
}
/*************************************************************************
* 函数名称: Frm_Monitor
* 功   能: 析构函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_Monitor::~Frm_Monitor()
{
    delete ui;
}
/*************************************************************************
* 函数名称: on_cbO_clicked
* 功    能: 响应输出点击事件
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Monitor::on_cbO_clicked(int icb)
{
    QCheckBox *cbO[] = {ui->cbO1,ui->cbO2,ui->cbO3,ui->cbO4,ui->cbO5,ui->cbO6,ui->cbO7,
                       ui->cbO8,ui->cbO9,ui->cbO10,ui->cbO11,ui->cbO12,ui->cbO13,ui->cbO14,
                       ui->cbO15,ui->cbO16,ui->cbO17,ui->cbO18,ui->cbO19,ui->cbO20,ui->cbO21,
                       ui->cbO22,ui->cbO23,ui->cbO24,ui->cbO25,ui->cbO26,ui->cbO27,ui->cbO28};

    cmd_Out->para.action = TCmd::OUTPUT+icb;
    cmd_Out->para.dist    = cbO[icb]->checkState()?1:0;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)cmd_Out);
}
/*************************************************************************
* 函数名称: UpdateIO
* 功    能: 更新IO显示
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Monitor::UpdateIO()
{
    if(!isVisible())
        return;
    QCheckBox *cbI[] = {ui->cbI1,ui->cbI2,ui->cbI3,ui->cbI4,ui->cbI5,ui->cbI6,ui->cbI7,
                       ui->cbI8,ui->cbI9,ui->cbI10,ui->cbI11,ui->cbI12,ui->cbI13,ui->cbI14,
                       ui->cbI15,ui->cbI16,ui->cbI17,ui->cbI18,ui->cbI19,ui->cbI20,ui->cbI21,
                       ui->cbI22,ui->cbI23,ui->cbI24,ui->cbI25,ui->cbI26,ui->cbI27,ui->cbI28,
                       ui->cbI29,ui->cbI30,ui->cbI31,ui->cbI32,ui->cbI33,ui->cbI34,ui->cbI35,
                       ui->cbI36,ui->cbI37,ui->cbI38,ui->cbI39,ui->cbI40,ui->cbI41,ui->cbI42,
                       ui->cbI43,ui->cbI44};

    QCheckBox *cbO[] = {ui->cbO1,ui->cbO2,ui->cbO3,ui->cbO4,ui->cbO5,ui->cbO6,ui->cbO7,
                       ui->cbO8,ui->cbO9,ui->cbO10,ui->cbO11,ui->cbO12,ui->cbO13,ui->cbO14,
                       ui->cbO15,ui->cbO16,ui->cbO17,ui->cbO18,ui->cbO19,ui->cbO20,ui->cbO21,
                       ui->cbO22,ui->cbO23,ui->cbO24,ui->cbO25,ui->cbO26,ui->cbO27,ui->cbO28};

    int iNum,iPos;
    for(int i = 0;i<sizeof(cbI)/sizeof(QCheckBox*);i++){
        iNum = i /8; iPos = i % 8;
        cbI[i]->setChecked((comF0.rpara.in[iNum]>>iPos) & 0x01);
    }

    for(int i = 0;i<sizeof(cbO)/sizeof(QCheckBox*);i++){
        iNum = i /8; iPos = i % 8;
        cbO[i]->setChecked((comF0.rpara.out[iNum]>>iPos) & 0x01);
    }
}

//==========================================================================================
// End of file.
//==========================================================================================

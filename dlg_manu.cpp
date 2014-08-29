/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_manu.cpp

* 功能描述: 手动界面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/


#include "dlg_manu.h"
#include "ui_dlg_manu.h"
#include "dlg_psw.h"
#include "tcmd.h"
#include "twidmana.h"
#include "treadcmd.h"
#include "qa5driver.h"
#include "tconfig.h"
#include "dlg_reset.h"

/*************************************************************************
* 函数名称: Dlg_Manu
* 功   能: 构造函数
* 输入参数: QWidget *parent 父类句柄
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Manu::Dlg_Manu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Manu)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    widMana->bDialog = true;

    m_iCurCmd = 0;

    QCheckBox *cbO[] = {ui->cbO1,ui->cbO2,ui->cbO3,ui->cbO4,ui->cbO5,ui->cbO6,ui->cbO7,
                        ui->cbO8,ui->cbO9,ui->cbO10,ui->cbO11,ui->cbO12,ui->cbO13,ui->cbO14,
                        ui->cbO15,ui->cbO16,ui->cbO17,ui->cbO18,ui->cbO19,ui->cbO20,ui->cbO21,
                        ui->cbO22,ui->cbO23,ui->cbO24,ui->cbO25,ui->cbO26,ui->cbO27,ui->cbO28};
    for(int i = 0;i<sizeof(cbO)/sizeof(QCheckBox*);i++)
    {
        if(i < readCmd.CmdO.size())
         cbO[i]->setText(readCmd.CmdO[i].cmdTil);

        sglMapCb.setMapping(cbO[i],i);
        connect(cbO[i], SIGNAL(clicked()), &sglMapCb, SLOT(map()));
    }
    connect(&sglMapCb,SIGNAL(mapped(int)),this,SLOT(on_cbO_clicked(int)));

    UpdateOut();

    a5drv.buzzer_off();

    widMana->bDialog = true;


    ui->pbMSpd->setRange(0,100);
    ui->pbMSpd->setValue(com02.para[0].gears);
}
/*************************************************************************
* 函数名称: Dlg_Manu
* 功   能: 析构函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Manu::~Dlg_Manu()
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
void Dlg_Manu::on_cbO_clicked(int icb)
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
* 函数名称: UpdateOut
* 功    能: 更新IO显示
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::UpdateOut()
{
    QCheckBox *cbO[] = {ui->cbO1,ui->cbO2,ui->cbO3,ui->cbO4,ui->cbO5,ui->cbO6,ui->cbO7,
                       ui->cbO8,ui->cbO9,ui->cbO10,ui->cbO11,ui->cbO12,ui->cbO13,ui->cbO14,
                       ui->cbO15,ui->cbO16,ui->cbO17,ui->cbO18,ui->cbO19,ui->cbO20,ui->cbO21,
                       ui->cbO22,ui->cbO23,ui->cbO24,ui->cbO25,ui->cbO26,ui->cbO27,ui->cbO28};

    int iNum,iPos;
    for(int i = 0;i<sizeof(cbO)/sizeof(QCheckBox*);i++){
        iNum = i /8; iPos = i % 8;
        cbO[i]->setChecked((comF0.rpara.out[iNum]>>iPos) & 0x01);
    }
}
/*************************************************************************
* 函数名称: on_lePos_clicked
* 功    能: 点击输入运动位置
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_lePos_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec()==QDialog::Accepted)
    {
        QString strT = dlg.m_str;
        strT = strT.right(strT.length() - strT.indexOf('.') - 1);
        if((strT.length() > 2) && (strT != dlg.m_str))
            return;

        ui->lePos->setText(dlg.m_str);
    }
}
/*************************************************************************
* 函数名称: on_btnUp_pressed
* 功    能: 按下UP按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnUp_pressed()
{
    if(!widMana->bTri)
        return;

    quint8 axis[] = {TCom::X,TCom::Y1,TCom::Z1,TCom::Y2,TCom::Z2,TCom::Y1,TCom::Z1};
    comE0.para.runtype = TComE0::JOG;
    comE0.para.jogT    = TComE0::JOG_ADD;
    comE0.para.jogA    = axis[m_iCurCmd]+0xF;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&comE0));
}
/*************************************************************************
* 函数名称: on_btnUp_released
* 功    能: 释放UP按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnUp_released()
{
    quint8 axis[] = {TCom::X,TCom::Y1,TCom::Z1,TCom::Y2,TCom::Z2,TCom::Y1,TCom::Z1};
    comE0.para.runtype = TComE0::JOG;
    comE0.para.jogT    = TComE0::JOG_STP;
    comE0.para.jogA    = axis[m_iCurCmd]+0xF;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&comE0));
}
/*************************************************************************
* 函数名称: on_btnDwn_pressed
* 功    能: 按下DOWN按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnDwn_pressed()
{
    if(!widMana->bTri)
        return;

    quint8 axis[] = {TCom::X,TCom::Y1,TCom::Z1,TCom::Y2,TCom::Z2,TCom::Y1,TCom::Z1};
    comE0.para.runtype = TComE0::JOG;
    comE0.para.jogT    = TComE0::JOG_SUB;
    comE0.para.jogA    = axis[m_iCurCmd]+0xF;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&comE0));
}
/*************************************************************************
* 函数名称: on_btnDwn_released
* 功    能: 释放DOWN按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnDwn_released()
{
    quint8 axis[] = {TCom::X,TCom::Y1,TCom::Z1,TCom::Y2,TCom::Z2,TCom::Y1,TCom::Z1};
    comE0.para.runtype = TComE0::JOG;
    comE0.para.jogT    = TComE0::JOG_STP;
    comE0.para.jogA    = axis[m_iCurCmd]+0xF;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&comE0));
}
/*************************************************************************
* 函数名称: on_btnServoX_clicked
* 功    能: 按下伺服X轴
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnServoX_clicked()
{
    m_iCurCmd = 0;
    SetBtnChk();
}
/*************************************************************************
* 函数名称: on_btnServoY1_clicked
* 功    能: 按下伺服Y1轴
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnServoY1_clicked()
{
    m_iCurCmd = 1;
    SetBtnChk();
}
/*************************************************************************
* 函数名称: on_btnServoZ1_clicked
* 功    能: 按下伺服Z1轴
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnServoZ1_clicked()
{
    m_iCurCmd = 2;
    SetBtnChk();
}
/*************************************************************************
* 函数名称: on_btnServoY2_clicked
* 功    能: 按下伺服Y2轴
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnServoY2_clicked()
{
    m_iCurCmd = 3;
    SetBtnChk();
}
/*************************************************************************
* 函数名称: on_btnServoZ2_clicked
* 功    能: 按下伺服Z2轴
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnServoZ2_clicked()
{
    m_iCurCmd = 4;
    SetBtnChk();
}
/*************************************************************************
* 函数名称: SetBtnChk
* 功    能: 设置按钮的下沉效果
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::SetBtnChk()
{
    QPushButton *btn[]={ui->btnServoX,ui->btnServoY1,ui->btnServoZ1,
                        ui->btnServoY2,ui->btnServoZ2};//,ui->btnServoY1Y2,ui->btnServoZ1Z2};

    for(int i=0; i<sizeof(btn) / sizeof(QPushButton*); i++)
    {
        btn[i]->setChecked(false);
    }
    btn[m_iCurCmd]->setChecked(true);
    iCurCmd   = m_iCurCmd;
}
/*************************************************************************
* 函数名称: InitBtn
* 功    能: 初始化轴选择按钮
* 输入参数: iCmd    当前操作的轴
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::InitBtn(int iCmd)
{
    QPushButton *btn[]={ui->btnServoX,ui->btnServoY1,ui->btnServoZ1,
                        ui->btnServoY2,ui->btnServoZ2};//,ui->btnServoY1Y2,ui->btnServoZ1Z2};

    for(int i=0;i<sizeof(btn)/sizeof(QPushButton*);i++){
        if(i == iCmd){
            btn[i]->setChecked(true);
        }else{
            btn[i]->setEnabled(false);
        }
    }

    m_iCurCmd = iCmd;
    iCurCmd   = iCmd;
}
/*************************************************************************
* 函数名称: on_btnStp_clicked
* 功    能: 按下停止按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnStp_clicked()
{
    QMutexLocker locker(&mutex_com);
    memset(&comE0.para,sizeof(comE0.para),0);
    comE0.para.runtype  = TComE0::STOP;
    pComBuf2.push_back((TCom*)&comE0);
}
/*************************************************************************
* 函数名称: on_btnRun_clicked
* 功    能: 按下运行按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnRun_clicked()
{
    if(!widMana->bTri)
        return;

    quint8 spd[]    ={com02.para[0].manS,com02.para[1].manS,com02.para[2].manS,com02.para[3].manS,
                      com02.para[4].manS,com02.para[0].manS,com02.para[1].manS};
    quint32 pos[]   ={comF0.rpara.xpos,comF0.rpara.y1pos,comF0.rpara.z1pos,comF0.rpara.y2pos,
                      comF0.rpara.z2pos,comF0.rpara.y1pos,comF0.rpara.z1pos};

    TCmd_Mov* cmd[] ={cmd_movX,cmd_movY1,cmd_movZ1,cmd_movY2,cmd_movZ2,cmd_movY,cmd_movZ};


    cmd[m_iCurCmd]->para.dist   = ui->lePos->text().toDouble() * 100.0 +
                                    ((ui->rbAbsPos->isChecked())?0:pos[m_iCurCmd]);
    cmd[m_iCurCmd]->para.spd    =  spd[m_iCurCmd];
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)cmd[m_iCurCmd]);
}
/*************************************************************************
* 函数名称: on_btnOk_clicked
* 功    能: 点击确定按钮，退出
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnOk_clicked()
{
    widMana->bDialog = false;
    widMana->bDialog = false;
    QDialog::accept();
}
/*************************************************************************
* 函数名称: on_btnCancel_clicked
* 功    能: 点击退出按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnCancel_clicked()
{
    widMana->bDialog = false;
    QDialog::reject();
}
/*************************************************************************
* 函数名称: on_btnSpeedHigh_clicked
* 功    能: 点击高速按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnSpeedHigh_clicked()
{
    /*quint8 *spd[]    ={&com02.para[0].manS,&com02.para[1].manS,&com02.para[2].manS,&com02.para[3].manS,
                       &com02.para[4].manS,&com02.para[0].manS,&com02.para[1].manS};

    *spd[m_iCurCmd] += 25;

    if(*spd[m_iCurCmd] > 100)
        *spd[m_iCurCmd] = 100;*/

    com02.para[0].gears +=25;
    if(com02.para[0].gears > 100)
        com02.para[0].gears = 100;

    ui->pbMSpd->setValue(com02.para[0].gears);

    for(int i = 1; i < 5; i++){
        com02.para[i].gears = com02.para[0].gears;
    }

    widMana->SavePara();

    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)&com02);
}
/*************************************************************************
* 函数名称: on_btnSpeedLow_clicked
* 功    能: 点击低速按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnSpeedLow_clicked()
{
    /*quint8 *spd[]    ={&com02.para[0].manS,&com02.para[1].manS,&com02.para[2].manS,&com02.para[3].manS,
                       &com02.para[4].manS,&com02.para[0].manS,&com02.para[1].manS};


    if(*spd[m_iCurCmd] > 25)
        *spd[m_iCurCmd] -= 25;
    else
        *spd[m_iCurCmd] = 0;*/

    com02.para[0].gears -= 25;
    if(com02.para[0].gears < 25)
        com02.para[0].gears = 25;

    ui->pbMSpd->setValue(com02.para[0].gears);

    for(int i = 1; i < 5; i++){
        com02.para[i].gears = com02.para[0].gears;
    }

    widMana->SavePara();

    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)&com02);
}
/*************************************************************************
* 函数名称: on_btnReset_clicked
* 功    能: 点击复位按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Manu::on_btnReset_clicked()
{
    Dlg_Reset dlg;
    dlg.setModal(true);
    dlg.exec();
}

//==========================================================================================
// End of file.
//==========================================================================================

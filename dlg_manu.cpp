/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_manu.cpp

* ��������: �ֶ�����

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
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
* ��������: Dlg_Manu
* ��   ��: ���캯��
* �������: QWidget *parent ������
* �������: ��
* �� �� ֵ: ��
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
* ��������: Dlg_Manu
* ��   ��: ��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_Manu::~Dlg_Manu()
{
    delete ui;
}
/*************************************************************************
* ��������: on_cbO_clicked
* ��    ��: ��Ӧ�������¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
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
* ��������: UpdateOut
* ��    ��: ����IO��ʾ
* �������: ��
* �������: ��
* �� �� ֵ: ��
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
* ��������: on_lePos_clicked
* ��    ��: ��������˶�λ��
* �������: ��
* �������: ��
* �� �� ֵ: ��
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
* ��������: on_btnUp_pressed
* ��    ��: ����UP��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
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
* ��������: on_btnUp_released
* ��    ��: �ͷ�UP��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
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
* ��������: on_btnDwn_pressed
* ��    ��: ����DOWN��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
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
* ��������: on_btnDwn_released
* ��    ��: �ͷ�DOWN��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
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
* ��������: on_btnServoX_clicked
* ��    ��: �����ŷ�X��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Manu::on_btnServoX_clicked()
{
    m_iCurCmd = 0;
    SetBtnChk();
}
/*************************************************************************
* ��������: on_btnServoY1_clicked
* ��    ��: �����ŷ�Y1��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Manu::on_btnServoY1_clicked()
{
    m_iCurCmd = 1;
    SetBtnChk();
}
/*************************************************************************
* ��������: on_btnServoZ1_clicked
* ��    ��: �����ŷ�Z1��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Manu::on_btnServoZ1_clicked()
{
    m_iCurCmd = 2;
    SetBtnChk();
}
/*************************************************************************
* ��������: on_btnServoY2_clicked
* ��    ��: �����ŷ�Y2��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Manu::on_btnServoY2_clicked()
{
    m_iCurCmd = 3;
    SetBtnChk();
}
/*************************************************************************
* ��������: on_btnServoZ2_clicked
* ��    ��: �����ŷ�Z2��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Manu::on_btnServoZ2_clicked()
{
    m_iCurCmd = 4;
    SetBtnChk();
}
/*************************************************************************
* ��������: SetBtnChk
* ��    ��: ���ð�ť���³�Ч��
* �������: ��
* �������: ��
* �� �� ֵ: ��
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
* ��������: InitBtn
* ��    ��: ��ʼ����ѡ��ť
* �������: iCmd    ��ǰ��������
* �������: ��
* �� �� ֵ: ��
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
* ��������: on_btnStp_clicked
* ��    ��: ����ֹͣ��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Manu::on_btnStp_clicked()
{
    QMutexLocker locker(&mutex_com);
    memset(&comE0.para,sizeof(comE0.para),0);
    comE0.para.runtype  = TComE0::STOP;
    pComBuf2.push_back((TCom*)&comE0);
}
/*************************************************************************
* ��������: on_btnRun_clicked
* ��    ��: �������а�ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
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
* ��������: on_btnOk_clicked
* ��    ��: ���ȷ����ť���˳�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Manu::on_btnOk_clicked()
{
    widMana->bDialog = false;
    widMana->bDialog = false;
    QDialog::accept();
}
/*************************************************************************
* ��������: on_btnCancel_clicked
* ��    ��: ����˳���ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Manu::on_btnCancel_clicked()
{
    widMana->bDialog = false;
    QDialog::reject();
}
/*************************************************************************
* ��������: on_btnSpeedHigh_clicked
* ��    ��: ������ٰ�ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
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
* ��������: on_btnSpeedLow_clicked
* ��    ��: ������ٰ�ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
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
* ��������: on_btnReset_clicked
* ��    ��: �����λ��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
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

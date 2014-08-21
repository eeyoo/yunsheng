/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: tcmd.cpp

* ��������: �Զ�������ָ���ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#include "tcmd.h"
#include "ui_frm_teach.h"
#include "twidmana.h"
#include "tlineedit.h"

/*************************************************************************
* ��������: TCmd
* ��    ��: ���캯��
* �������: fileName
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCmd::TCmd(const QString &fileName)
        :QStandardItem((QIcon)(fileName),QString(""))
{
    cls_typ = CLS_BSE;
}
/*************************************************************************
* ��������: Id2Til
* ��    ��: ת��Id������
* �������: Id	��Ҫת����Id
* �������: ��
* �� �� ֵ: ת���õı���
*************************************************************************/
QString TCmd::Id2Til(CMDID Id)
{
    return QString("");
}
/*************************************************************************
* ��������: ConsCombiItem
* ��    ��: �������Item
* �������: ��
* �������: ��
* �� �� ֵ: ���Item
*************************************************************************/
QStandardItem* TCmd::ConsCombiItem()
{
    if(para.combin == 0)
        return new QStandardItem(QObject::tr(""));

    return new QStandardItem(QObject::tr("ͬ��%1").arg(para.combin));
}
/*************************************************************************
* ��������: OnSave
* ��    ��: ����ʾ������
* �������: file	�����ļ���ָ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCmd::OnSave(QFile *file)
{
    file->write((char*)(&para),sizeof(para));
}
/*************************************************************************
* ��������: OnOpen
* ��    ��: ��ʾ������
* �������: file	���ļ���ָ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCmd::OnOpen(QFile *file)
{
    file->read((char*)(&para),sizeof(para));
}





/*************************************************************************
* ��������: TCmd_Mov
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCmd_Mov::TCmd_Mov()
        :TCmd(":/Icon/Btn/Res/btn/motor.png")
{
    cls_typ = CLS_MOV;
    memset(&para,0,sizeof(STR_PARA));

    //ͨѶ����
    com_add  = COM7F;
    eptNum   = 1;
}
/*************************************************************************
* ��������: ConsPara
* ��    ��: �����������
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_Mov::ConsPara()
{
    /*QPushButton *btn[]={widMana->frm_teach.ui->btnR1,widMana->frm_teach.ui->btnR2,
                         widMana->frm_teach.ui->btnR3,widMana->frm_teach.ui->btnR4,
                         widMana->frm_teach.ui->btnR5,widMana->frm_teach.ui->btnR6,
                         widMana->frm_teach.ui->btnR7};

    for(int i = 0; i < sizeof(btn)/sizeof(QPushButton*); i++){
        if(btn[i]->isChecked()){
            para.action = i + XMOV;
        }
    }

    para.dist   = widMana->frm_teach.ui->leRPos->text().toDouble() * 100.0;
    para.spd    = widMana->frm_teach.ui->leRSpd->text().toInt();
    para.wattim = widMana->frm_teach.ui->leRTim->text().toInt();*/
    if(para.action == TCmd::UMOV){
        para.dist   = widMana->frm_teach.ui->lePosR->text().toDouble() * 100.0;
        para.spd    = widMana->frm_teach.ui->leSpdR->text().toInt();
        para.wattim = widMana->frm_teach.ui->leTimR->text().toInt();
    }else{
        para.dist   = widMana->frm_teach.ui->lePosD->text().toDouble() * 100.0;
        para.spd    = widMana->frm_teach.ui->leSpdD->text().toInt();
        para.wattim = widMana->frm_teach.ui->leTimD->text().toInt();
    }
}
/*************************************************************************
* ��������: getCmdTit
* ��    ��: ��ȡ����ı���
* �������: ��
* �������: ��
* �� �� ֵ: �������
*************************************************************************/
QString TCmd_Mov::getCmdTit()
{
    float dist = ((float)para.dist) / 100.0;
    if(para.action == TCmd::UMOV){
        return QObject::tr("%1:�Ƕ�%2���ٶ�%3����ʱ%4")
                        .arg(Id2Til((CMDID)para.action))
                        .arg(QString::number(dist,'f',2))
                        .arg(para.spd)
                        .arg(para.wattim);
    }else{
        return QObject::tr("%1:λ��%2���ٶ�%3����ʱ%4")
                        .arg(Id2Til((CMDID)para.action))
                        .arg(QString::number(dist,'f',2))
                        .arg(para.spd)
                        .arg(para.wattim);
    }

}
/*************************************************************************
* ��������: ConsTitItem
* ��    ��: ��������Item
* �������: ��
* �������: ��
* �� �� ֵ: ����Item
*************************************************************************/
QStandardItem* TCmd_Mov::ConsTitItem()
{
    return new QStandardItem(getCmdTit());
}
/*************************************************************************
* ��������: OnCmdClk
* ��    ��: ��Ӧ����ĵ����¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCmd_Mov::OnCmdClk()
{
    widMana->frm_teach.ui->tabCmd->setCurrentIndex(0);
    widMana->frm_teach.on_btn_clicked(para.action - X1MOV);

    if(para.action == TCmd::UMOV){
        double dist = ((double)para.dist) / 100.0;
        widMana->frm_teach.ui->lePosR->setText(QString::number(dist,'f',2));
        widMana->frm_teach.ui->leSpdR->setText(QString("%1").arg(para.spd));
        widMana->frm_teach.ui->leTimR->setText(QString("%1").arg(para.wattim));
    }else{
        double dist = ((double)para.dist) / 100.0;
        widMana->frm_teach.ui->lePosD->setText(QString::number(dist,'f',2));
        widMana->frm_teach.ui->leSpdD->setText(QString("%1").arg(para.spd));
        widMana->frm_teach.ui->leTimD->setText(QString("%1").arg(para.wattim));
    }

}
/*************************************************************************
* ��������: snd
* ��    ��: �����������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_Mov::snd()
{
    //������ת��
    /*int ipls[] = {0,1,2,3,4,3,4};
    int index = ipls[para.action - XMOV];
    para.dist = (para.dist * 1000) / com02.para[index].pls_equ;*/

    //printf("dist:%d;pls_equ:%d\n",para.dist,com02.para[index].pls_equ);

    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;
    //printf("iS:%d,iF:%d\n",iS,iF);
    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;

        //for(int j = 0;j<1000;j++);
        //printf("%x %x %x %x %x %x %x %x\n",canS.data[0],canS.data[1],canS.data[2],canS.data[3],
        //                                   canS.data[4],canS.data[5],canS.data[6],canS.data[7]);

        SndFrame(&canS);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_Mov::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[2] != 'A')||(pd[3] != 'C')||(pd[4] != 'K'))
        return false;

    return true;
}
/*************************************************************************
* ��������: Id2Til
* ��    ��: ת��Id������
* �������: Id	��Ҫת����Id
* �������: ��
* �� �� ֵ: ת���õı���
*************************************************************************/
QString TCmd_Mov::Id2Til(CMDID Id)
{
    //printf("%x\n",(int)Id);

    for(int i=0;i<readCmd.CmdM.size();i++)
    {
        if(Id == readCmd.CmdM[i].cmdId)
        {
            //printf("%s\n",readCmd.CmdM[i].cmdTil.toAscii().data());
            return readCmd.CmdM[i].cmdTil;
        }
    }
    return QString("");
}












/*************************************************************************
* ��������: TCmd_In
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCmd_In::TCmd_In()
        :TCmd(":/Res/image/inicon.PNG")
{
    cls_typ = CLS_IO;
    memset(&para,0,sizeof(STR_PARA));

    //ͨѶ����
    com_add  = COM7F;
    eptNum   = 1;
}
/*************************************************************************
* ��������: ConsPara
* ��    ��: �����������
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_In::ConsPara()
{
    /*if(ioT == SPECIAL){
        QPushButton *btn[]={widMana->frm_teach.ui->btnI1,widMana->frm_teach.ui->btnI2,
                            widMana->frm_teach.ui->btnI3,widMana->frm_teach.ui->btnI4,
                            widMana->frm_teach.ui->btnI5,widMana->frm_teach.ui->btnI6,
                            widMana->frm_teach.ui->btnI7,widMana->frm_teach.ui->btnI8,
                            widMana->frm_teach.ui->btnI9};
        for(int i = 0; i < sizeof(btn)/sizeof(QPushButton*); i++){
            if(btn[i]->isChecked()){
                para.action = i + INPUT;
            }
        }

        para.dist   = widMana->frm_teach.ui->cbStaIS->isChecked()?1:0;
        para.wattim = widMana->frm_teach.ui->leTimIS->text().toInt();
    }else if(ioT == GENERAL){
        int aa = widMana->frm_teach.ui->leNoIG->text().toInt();
        para.action = widMana->frm_teach.ui->leNoIG->text().toInt() + INPUT;
        para.dist   = widMana->frm_teach.ui->cbStaIG->isChecked()?1:0;
        para.wattim = widMana->frm_teach.ui->leTimIG->text().toInt();
    }*/

    TLineEdit *ple = (TLineEdit*)widMana->frm_teach.ui->leNoI;
    para.action = ple->iMark + INPUT;
    para.dist   = widMana->frm_teach.ui->cbStaI->isChecked()?1:0;
    para.wattim = widMana->frm_teach.ui->leTimI->text().toInt();
}
/*************************************************************************
* ��������: getCmdTit
* ��    ��: ��ȡ�������
* �������: ��
* �������: ��
* �� �� ֵ: �������
*************************************************************************/
QString TCmd_In::getCmdTit()
{
    return QObject::tr("%1:%2,��ʱ%3")
                    .arg(Id2Til((CMDID)para.action))
                    .arg(para.dist == 1?QObject::tr("��"):QObject::tr("��"))
                    .arg(para.wattim);
}
/*************************************************************************
* ��������: ConsTitItem
* ��    ��: ��������Item
* �������: ��
* �������: ��
* �� �� ֵ: ����Item
*************************************************************************/
QStandardItem* TCmd_In::ConsTitItem()
{
    return new QStandardItem(getCmdTit());
}
/*************************************************************************
* ��������: OnCmdClk
* ��    ��: ��Ӧ������¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCmd_In::OnCmdClk()
{
    widMana->frm_teach.ui->tabCmd->setCurrentIndex(1);
    widMana->frm_teach.on_btn_clicked(5);

    widMana->frm_teach.ui->cbStaI->setChecked(para.dist == 1?true:false);
    widMana->frm_teach.ui->leTimI->setText(QString("%1").arg(para.wattim));
    TLineEdit *ple = (TLineEdit*)widMana->frm_teach.ui->leNoI;
    ple->setText(Id2Til((CMDID)para.action));
    ple->iMark = para.action - TCmd::INPUT;

    /*widMana->frm_teach.ui->tabCmd->setCurrentIndex(1);
    if(para.action < (INPUT + 9)){
        widMana->frm_teach.on_btn_clicked(para.action - XMOV);
        widMana->frm_teach.ui->cbStaIS->setChecked(para.dist == 1?true:false);
        widMana->frm_teach.ui->leTimIS->setText(QString("%1").arg(para.wattim));
   }else{
       widMana->frm_teach.on_btn_clicked(16);
       widMana->frm_teach.ui->cbStaIG->setChecked(para.dist == 1?true:false);
       widMana->frm_teach.ui->leTimIG->setText(QString("%1").arg(para.wattim));
       widMana->frm_teach.ui->leNoIG->setText(QString("%1").arg(para.action - INPUT));
   }*/
}
/*************************************************************************
* ��������: snd
* ��    ��: ������������
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_In::snd()
{
    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;
    //printf("iS:%d,iF:%d\n",iS,iF);
    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;

        //for(int j = 0;j<1000;j++);
        SndFrame(&canS);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_In::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[2] != 'A')||(pd[3] != 'C')||(pd[4] != 'K'))
        return false;

    return true;
}
/*************************************************************************
* ��������: Id2Til
* ��    ��: ת��Id������
* �������: Id	��Ҫת����Id
* �������: ��
* �� �� ֵ: ת���õı���
*************************************************************************/
QString TCmd_In::Id2Til(CMDID Id)
{
    for(int i=0;i<readCmd.CmdI.size();i++)
    {
        if(Id == readCmd.CmdI[i].cmdId)
        {
            return readCmd.CmdI[i].cmdTil;
        }
    }
    return QString("%1").arg(Id - TCmd::INPUT);
}















/*************************************************************************
* ��������: TCmd_Out
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCmd_Out::TCmd_Out()
        :TCmd(":/Res/image/icon_output1_gpio.png")
{
    cls_typ = CLS_IO;
    memset(&para,0,sizeof(STR_PARA));

    //ͨѶ����
    com_add  = COM7F;
    eptNum   = 1;
}
/*************************************************************************
* ��������: ConsPara
* ��    ��: �����������
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_Out::ConsPara()
{
    /*if(ioT == SPECIAL){
        QPushButton *btn[]={widMana->frm_teach.ui->btnO1,widMana->frm_teach.ui->btnO2,
                            widMana->frm_teach.ui->btnO3,widMana->frm_teach.ui->btnO4,
                            widMana->frm_teach.ui->btnO5,widMana->frm_teach.ui->btnO6,
                            widMana->frm_teach.ui->btnO7,widMana->frm_teach.ui->btnO8,
                            widMana->frm_teach.ui->btnO9,widMana->frm_teach.ui->btnO10};
        for(int i = 0; i < sizeof(btn)/sizeof(QPushButton*); i++){
            if(btn[i]->isChecked()){
                para.action = i + OUTPUT;
            }
        }

        para.dist   = widMana->frm_teach.ui->cbStaOS->isChecked()?1:0;
        para.wattim = widMana->frm_teach.ui->leTimOS->text().toInt();
    }else if(ioT == GENERAL){
        para.action = widMana->frm_teach.ui->leNoOG->text().toInt() + OUTPUT;
        para.dist   = widMana->frm_teach.ui->cbStaOG->isChecked()?1:0;
        para.wattim = widMana->frm_teach.ui->leTimOG->text().toInt();
    }*/
    TLineEdit *ple = (TLineEdit*)(widMana->frm_teach.ui->leNoO);

    para.action = ple->iMark + OUTPUT;
    para.dist   = widMana->frm_teach.ui->cbStaO->isChecked()?1:0;
    para.wattim = widMana->frm_teach.ui->leTimO->text().toInt();

    if(para.action > (OUTPUT + 8)){
        this->setIcon(QIcon(":/Res/image/icon_output2_gpio.png"));
    }
}
/*************************************************************************
* ��������: getCmdTit
* ��    ��: ��ȡ�������
* �������: ��
* �������: ��
* �� �� ֵ: �������
*************************************************************************/
QString TCmd_Out::getCmdTit()
{
    return QObject::tr("%1:%2,��ʱ%3")
                    .arg(Id2Til((CMDID)para.action))
                    .arg(para.dist == 1?QObject::tr("��"):QObject::tr("��"))
                    .arg(para.wattim);
}
/*************************************************************************
* ��������: ConsTitItem
* ��    ��: ��������Item
* �������: ��
* �������: ��
* �� �� ֵ: ����Item
*************************************************************************/
QStandardItem* TCmd_Out::ConsTitItem()
{
    return new QStandardItem(getCmdTit());
}
/*************************************************************************
* ��������: OnCmdClk
* ��    ��: ��Ӧ������¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCmd_Out::OnCmdClk()
{
    widMana->frm_teach.ui->tabCmd->setCurrentIndex(1);
    if(para.action < (OUTPUT + 8)){
        widMana->frm_teach.on_btn_clicked(6);
    }else{
        widMana->frm_teach.on_btn_clicked(7);
    }
    TLineEdit* ple = (TLineEdit*)(widMana->frm_teach.ui->leNoO);
    ple->setText(Id2Til((CMDID)para.action));
    ple->iMark = para.action - OUTPUT;
    widMana->frm_teach.ui->cbStaO->setChecked(para.dist == 1?true:false);
    widMana->frm_teach.ui->leTimO->setText(QString("%1").arg(para.wattim));

    /*widMana->frm_teach.ui->tabCmd->setCurrentIndex(2);
    if(para.action < (OUTPUT0)){
        widMana->frm_teach.on_btn_clicked(para.action - OUTPUT7);
        widMana->frm_teach.ui->cbStaOS->setChecked(para.dist == 1?true:false);
        widMana->frm_teach.ui->leTimOS->setText(QString("%1").arg(para.wattim));
   }
    else{
       widMana->frm_teach.on_btn_clicked(170);
       widMana->frm_teach.ui->cbStaOG->setChecked(para.dist == 1?true:false);
       widMana->frm_teach.ui->leTimOG->setText(QString("%1").arg(para.wattim));
       widMana->frm_teach.ui->leNoOG->setText(QString("%1").arg(para.action - OUTPUT));
   }*/
}
/*************************************************************************
* ��������: snd
* ��    ��: ������������
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_Out::snd()
{
    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;
    //printf("iS:%d,iF:%d\n",iS,iF);
    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;

        //for(int j = 0;j<1000;j++);
        SndFrame(&canS);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_Out::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[2] != 'A')||(pd[3] != 'C')||(pd[4] != 'K'))
        return false;

    return true;
}
/*************************************************************************
* ��������: Id2Til
* ��    ��: ת��Id������
* �������: Id	��Ҫת����Id
* �������: ��
* �� �� ֵ: ת���õı���
*************************************************************************/
QString TCmd_Out::Id2Til(CMDID Id)
{
    for(int i=0;i<readCmd.CmdO.size();i++)
    {
        if(Id == readCmd.CmdO[i].cmdId)
        {
            return readCmd.CmdO[i].cmdTil;
        }
    }
    return QString("%1").arg(Id - OUTPUT);
}



/*************************************************************************
* ��������: TCmd_Stk
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCmd_Stk::TCmd_Stk()
        :TCmd(":/Res/image/icon_stack.png")
{
    cls_typ = CLS_STK;
    memset(&para,0,sizeof(STR_PARA));

    //ͨѶ����
    com_add  = COM7F;
    eptNum   = 1;
}
/*************************************************************************
* ��������: ConsPara
* ��    ��: ��������Ĳ���
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_Stk::ConsPara()
{
    para.action = STACK;
    para.wattim = widMana->frm_teach.ui->leTimS->text().toInt();
    STK_PARA *sp = (STK_PARA*)(&para);

    QString strT = widMana->frm_teach.ui->leStkN->text();
    int i=0;
    for(i =0; i < strT.length(); i++){
        if(i >= 7)
            break;

        sp->name[i] = (quint8)strT.at(i).toAscii();
    }
    sp->name[i] = (quint8)('\0');

    memcpy(&comStk.para,&com06.para,sizeof(com06.para));
}
/*************************************************************************
* ��������: getCmdTit
* ��    ��: ��ȡ�������
* �������: ��
* �������: ��
* �� �� ֵ: �������
*************************************************************************/
QString TCmd_Stk::getCmdTit()
{
    STK_PARA *sp = (STK_PARA*)(&para);

    QString strT;
    for(int i = 0; i < 8; i++){
        if(sp->name[i] == (quint8)('\0'))
            break;
        strT += (char)sp->name[i];
    }
    return QObject::tr("%1%2,��ʱ%3")
                    .arg(Id2Til((CMDID)para.action))
                    .arg(strT)
                    .arg(para.wattim);
}
/*************************************************************************
* ��������: ConsTitItem
* ��    ��: ��������Item
* �������: ��
* �������: ��
* �� �� ֵ: ����Item
*************************************************************************/
QStandardItem* TCmd_Stk::ConsTitItem()
{
    return new QStandardItem(getCmdTit());
}
/*************************************************************************
* ��������: OnCmdClk
* ��    ��: ��Ӧ����ĵ����¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCmd_Stk::OnCmdClk()
{
    /*widMana->frm_teach.ui->tabCmd->setCurrentIndex(3);
    widMana->frm_teach.on_btn_clicked(28);
    widMana->frm_teach.ui->leTimS->setText(QString("%1").arg(para.wattim));

    STK_PARA *sp = (STK_PARA*)(&para);
    QString strT;
    for(int i = 0; i < 8; i++){
        if(sp->name[i] == 255)
            break;
        strT += (char)sp->name[i];
    }

    widMana->frm_teach.ui->leStkN->setText(strT);*/
}
/*************************************************************************
* ��������: snd
* ��    ��: �����������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_Stk::snd()
{
    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;
    //printf("iS:%d,iF:%d\n",iS,iF);
    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;

        //for(int j = 0;j<1000;j++);
        SndFrame(&canS);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У��������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool TCmd_Stk::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[2] != 'A')||(pd[3] != 'C')||(pd[4] != 'K'))
        return false;

    return true;
}
/*************************************************************************
* ��������: Id2Til
* ��    ��: ת��Id������
* �������: Id	��Ҫת����Id
* �������: ��
* �� �� ֵ: ת���õı���
*************************************************************************/
QString TCmd_Stk::Id2Til(CMDID Id)
{
    for(int i=0;i<readCmd.CmdS.size();i++)
    {
        if(Id == readCmd.CmdS[i].cmdId)
        {
            return readCmd.CmdS[i].cmdTil;
        }
    }
    return QString("");
}







/*************************************************************************
* ��������: CreateMX1
* ��    ��: ����X1��������
* �������: ��
* �������: ��
* �� �� ֵ: ��������
*************************************************************************/
TCmd* CreateMX1()
{
    TCmd_Mov *cmd = new TCmd_Mov;
    cmd->para.action = TCmd::X1MOV;
    cmd->setIcon(QIcon(":/Res/image/icon_servo_x1.png"));
    //cmd->mt = TCmd::DIR;
    return cmd;
}
/*************************************************************************
* ��������: CreateMZ1
* ��    ��: ����Z1��������
* �������: ��
* �������: ��
* �� �� ֵ: ��������
*************************************************************************/
TCmd* CreateMZ1()
{
    TCmd_Mov *cmd = new TCmd_Mov;
    cmd->para.action = TCmd::Z1MOV;
    cmd->setIcon(QIcon(":/Res/image/icon_servo_z1.png"));
    //cmd->mt = TCmd::DIR;
    return cmd;
}
/*************************************************************************
* ��������: CreateMU
* ��    ��: ����U��������
* �������: ��
* �������: ��
* �� �� ֵ: ��������
*************************************************************************/
TCmd* CreateMU()
{
    TCmd_Mov *cmd = new TCmd_Mov;
    cmd->para.action = TCmd::UMOV;
    cmd->setIcon(QIcon(":/Res/image/icon_servo_u.png"));
    //cmd->mt = TCmd::ROT;
    return cmd;
}
/*************************************************************************
* ��������: CreateMX2
* ��    ��: ����X2��������
* �������: ��
* �������: ��
* �� �� ֵ: ��������
*************************************************************************/
TCmd* CreateMX2()
{
    TCmd_Mov *cmd = new TCmd_Mov;
    cmd->para.action = TCmd::X2MOV;
    cmd->setIcon(QIcon(":/Res/image/icon_servo_x2.png"));
    //cmd->mt = TCmd::DIR;
    return cmd;
}
/*************************************************************************
* ��������: CreateMZ2
* ��    ��: ����Z2��������
* �������: ��
* �������: ��
* �� �� ֵ: ��������
*************************************************************************/
TCmd* CreateMZ2()
{
    TCmd_Mov *cmd = new TCmd_Mov;
    cmd->para.action = TCmd::Z2MOV;
    cmd->setIcon(QIcon(":/Res/image/icon_servo_z2.png"));
    //cmd->mt = TCmd::DIR;
    return cmd;
}
/*************************************************************************
* ��������: CreateI
* ��    ��: ������������
* �������: ��
* �������: ��
* �� �� ֵ: ��������
*************************************************************************/
TCmd* CreateI()
{
    TCmd *cmd = new TCmd_In;
    cmd->setIcon(QIcon(":/Res/image/icon_input_gpio.png"));
    //((TCmd_In*)cmd)->ioT  = TCmd::SPECIAL;
    return cmd;
}
/*************************************************************************
* ��������: CreateO
* ��    ��: �����������
* �������: ��
* �������: ��
* �� �� ֵ: �������
*************************************************************************/
TCmd* CreateO()
{
    TCmd *cmd = new TCmd_Out;
    //((TCmd_Out*)cmd)->ioT  = TCmd::SPECIAL;
    return cmd;
}
/*************************************************************************
* ��������: CreateStk
* ��    ��: �����ѵ�����
* �������: ��
* �������: ��
* �� �� ֵ: �ѵ�����
*************************************************************************/
TCmd* CreateStk()
{
    return new TCmd_Stk;
}

/*****************��������***********************/
Create_Cmd create_cmd[] =
{
    CreateMX1,CreateMZ1,CreateMU,CreateMX2,CreateMZ2,
    CreateI,CreateO,CreateO,CreateStk
};								



TCmd*            pCurCmd;               //��ǰ�ֶ���������
int              iCurCmd = 0;		//��ǰ��������
TCmd_Mov*        cmd_movX;              //�ֶ� X���˶�����ͨѶ
TCmd_Mov*        cmd_movY1;		//�ֶ� Y1���˶�����ͨѶ
TCmd_Mov*        cmd_movZ1;		//�ֶ� Z1���˶�����ͨѶ
TCmd_Mov*        cmd_movY2;		//�ֶ� Y2���˶�����ͨѶ
TCmd_Mov*        cmd_movZ2;		//�ֶ� Z2���˶�����ͨѶ
TCmd_Mov*        cmd_movY;		//�ֶ� Y���˶�����ͨѶ
TCmd_Mov*        cmd_movZ;		//�ֶ� Z���˶�����ͨѶ
/*ROT,OVRTRN,BRC1,BRC2,BRC3,SCK1,SCK2,RES1,RES2,
        BLT,ERR,STK,AUX*/
TCmd_In*          cmd_In;		//�ֶ� ��������ͨѶ
TCmd_Out*         cmd_Out;		//�ֶ� �������ͨѶ

//==========================================================================================
// End of file.
//==========================================================================================

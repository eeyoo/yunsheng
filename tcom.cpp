/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: tcom.cpp

* ��������: ͨѶ���ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#include "tcom.h"
#include "tcmd.h"
#include "ui_mainwindow.h"
#include "ui_frm_run.h"
#include "twidmana.h"
#include "twarn.h"

#include <QTextCodec>

//#include <QDebug>
/*************************************************************************
* ��������: TCom
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCom::TCom()
{
}
/*************************************************************************
* ��������: snd
* ��    ��: ����ͨѶ��
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom::snd()
{
}
/*************************************************************************
* ��������: rcv
* ��    ��: ���շ������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom::rcv()
{
#ifdef EMBEDED_ARM
    vecRcv.clear();
    while(true)
    {
        //for(int i = 50000;i>-1;i--);
        //sleep(10);
        CAN_Frame canR;
        memset(&canR,0,sizeof(canR));
        //printf("3\n");
        //��ʱ����
        if(!a5drv.can_rcv(&canR))
        {
            //printf("can_rcv failure\n");

            return false;
        }
        //printf("4\n");
        //iRcvT++;
        //if(iRcvT>2000)
        //    return false;
        //printf("%x %x %x %x %x %x %x %x\n",canR.data[0],canR.data[1],canR.data[2],canR.data[3],
        //                                 canR.data[4],canR.data[5],canR.data[6],canR.data[7]);
        //if(!a5drv.can_rcv(&canR))
        //    return false;
        //printf("ID:%x\n",canR.canId);
        //�������ӵڶ�֡��ʼ�����֡��ַ�͵�ǰ��ַ��ͬ������֡��Ŵ��ڵ��ڵ�ǰ��ţ�����Ϊ����
        /*if(rcvAdd! = 0x00)
        {
            if(canR.data[0] != rcvAdd)
                return false;

            if(canR.data[1] >= rcvCurF)
                return false;
        }*/

        //qDebug("Id:%x,No:%x",canR.canId,canR.data[1]);
        //qDebug("ID:%x",canR.canId);
        if(canR.canId == 0x122)
        {
            vecRcv.push_back(canR);

            //iRcvT=0;
            //���ݽ������
            if(canR.data[1] == 0x01){

                if(com_add == COMF3){   //����ʾ�̳���
                    if(canR.data[0] == COMF3)
                        return true;
                }else{

                    if(canR.data[0] != com_add){
                        vecRcv.clear();
                        continue;
                    }

                    return true;
                }
            }
        }
    }
#endif
    return true;
}
/*************************************************************************
* ��������: DoCom
* ��    ��: ִ��һ������ͨѶ
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom::DoCom()
{
#ifdef EMBEDED_ARM
    static int iT = 0;

    for(int i = 0;i<3;i++)
    {
        if(snd())
        {
            //for(int i = 500000;i>-1;i--);
            //sleep(10);
            if(rcv())
            {
                if(chk())
                {
                    //qDebug("UpdateUI(true)");
                    UpdateUI(true);
                    iT = 0;
                    return true;
                }
            }
        }
    }

    //qDebug("UpdateUI(false)");

    if(iT == 10){
        warn.ShowW2L(TWarn::W_COM);
    }else if(iT < 10){
        widMana->mainW->ui->lblWarn->setText(QString(""));
    }

    iT++;

#endif
    UpdateUI(false);
    return false;
}
/*************************************************************************
* ��������: chk
* ��    ��: У��������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom::chk()
{
    //return true;
    if(vecRcv.empty())
        return false;

    quint8 iS = vecRcv.size();

    //printf("iS:%d\n",iS);
    if(com_add == COMF3)
        return true;

    //У����յ�֡���Ƿ�Ϊ����ֵ
    if(eptNum != 0)
    {
        if(eptNum != iS)
            return false;
    }

    quint8 add;
    add = vecRcv[0].data[0];
    //printf("add:%x,com_add:%x\n",add,com_add);
    //У���ַ�ǲ�����Ҫ���յĵ�ַ
    if(add != com_add)
        return false;
    //У������֡�еĵ�ַ�Ƿ���ͬ
    for(int i = 1;i<iS;i++)
    {
        if(add != (quint8)vecRcv[i].data[0])
        {
            //qDebug("add:%x,data[0]:%x",add,vecRcv[i].data[0]);
            return false;
        }
    }
    //printf("111\n");
    //У��֡������Ƿ���������
    quint8 frm1,frm2;
    for(int i = 0;i<iS-1;i++)
    {
        frm1 = vecRcv[i].data[1];
        frm2 = vecRcv[i+1].data[1];
        if((frm1-1) != frm2)
        {
            //printf("frm1:%d,frm2:%d\n",frm1,frm2);
            return false;
        }
    }

    return true;
}
/*************************************************************************
* ��������: SndFrame
* ��    ��: ����һ��CAN֡
* �������: frame��can֡��ָ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom::SndFrame(CAN_Frame *frame)
{
    //printf("5\n");
    for(int i = 0;i<200;i++)
    {
        if(a5drv.can_send(frame))
            return true;

        for(int j = 0;j<200000;j++)
        {
            for(int k = 0;k<200000;k++);
        }
    }
    //printf("6\n");
    return true;
}




/*************************************************************************
* ��������: TCom01
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCom01::TCom01()
{
    com_add  = COM01;
    eptNum   = 1;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom01::snd()
{
    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j = 0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom01::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[1] != 1)||(pd[2] != 'O')||(pd[3] != 'K'))
    {
        return false;
    }

    return true;
}

/*************************************************************************
* ��������: TCom02
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCom02::TCom02()
{
    com_add  = COM02;
    eptNum   = 1;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom02::snd()
{
    int iS = sizeof(STR_PARA)*5;

    int iF = iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd = (quint8*)(para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j = 0;j<1000;j++);
        printf("data:%x %x %x %x %x %x %x %x\n",canS.data[0],canS.data[1],canS.data[2],canS.data[3],
                                                canS.data[4],canS.data[5],canS.data[6],canS.data[7]);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У��������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom02::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[1] != 1)||(pd[2] != 'O')||(pd[3] != 'K'))
        return false;

    return true;
}

/*************************************************************************
* ��������: TCom03
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCom03::TCom03()
{
    com_add  = COM03;
    eptNum   = 1;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom03::snd()
{
    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j = 0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom03::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[1] != 1)||(pd[2] != 'O')||(pd[3] != 'K'))
        return false;

    return true;
}


/*************************************************************************
* ��������: TCom04
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCom04::TCom04()
{
    com_add  = COM04;
    eptNum   = 1;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom04::snd()
{
    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j = 0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom04::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[1] != 1)||(pd[2] != 'O')||(pd[3] != 'K'))
        return false;

    return true;
}


/*************************************************************************
* ��������: TCom05
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCom05::TCom05()
{
    com_add  = COM05;
    eptNum   = 1;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom05::snd()
{
    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j = 0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom05::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[1] != 1)||(pd[2] != 'O')||(pd[3] != 'K'))
        return false;

    return true;
}






/*************************************************************************
* ��������: TCom06
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCom06::TCom06()
{
    com_add  = COM06;
    eptNum   = 1;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom06::snd()
{
    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j = 0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom06::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[1] != 1)||(pd[2] != 'O')||(pd[3] != 'K'))
        return false;

    return true;
}



/*************************************************************************
* ��������: TCom07
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCom07::TCom07()
{
    com_add  = COM07;
    eptNum   = 1;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom07::snd()
{
    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //printf("%x %x %x %x %x %x %x %x\n",canS.data[0],canS.data[1],canS.data[2],canS.data[3],
        //                                   canS.data[4],canS.data[5],canS.data[6],canS.data[7]);
        //for(int j = 0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom07::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[1] != 1)||(pd[2] != 'O')||(pd[3] != 'K'))
        return false;

    return true;
}



/*************************************************************************
* ��������: TCom08
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCom08::TCom08()
{
    com_add  = COM08;
    eptNum   = 1;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom08::snd()
{
    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j = 0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom08::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[1] != 1)||(pd[2] != 'O')||(pd[3] != 'K'))
        return false;

    return true;
}



/*************************************************************************
* ��������: TCom20
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCom20::TCom20()
{
    com_add  = COM20;
    eptNum   = 1;

    bNewForSnd = true;
    bOpen = false;
    modelPro = new QStandardItemModel(0,3);
}
/*************************************************************************
* ��������: AddCmd
* ��    ��: ���һ��ʾ������
* �������: rIndex��������λ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCom20::AddCmd(int rIndex)
{
    modelPro->insertRow(rIndex);
    bNewForSnd = true;
    bOpen      = true;
}
/*************************************************************************
* ��������: DelCmd
* ��    ��: ɾ��һ��ʾ������
* �������: rIndexɾ�������λ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCom20::DelCmd(int rIndex)
{
    if(rIndex ==  0||(rIndex == modelPro->rowCount()-1))
        return;

    modelPro->removeRow(rIndex);
    bNewForSnd = true;
    bOpen      = true;
}
/*************************************************************************
* ��������: SetItem
* ��    ��: ����ʾ������Item������
* �������: row		���õ���
			column	���õ���
			item	item������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCom20::SetItem(int row,int column,QStandardItem* item)
{
    modelPro->setItem(row,column,item);
    bNewForSnd = true;
    bOpen      = true;
}
/*************************************************************************
* ��������: NewPgm
* ��    ��: �½�ʾ�̳���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCom20::NewPgm()
{
    //��ճ����ļ�
    modelPro->clear();

    AddCmd(0);
    QStandardItem *startI=new QStandardItem(QObject::tr("����ʼ"));
    modelPro->setItem(0,2,startI);
    AddCmd(1);
    QStandardItem *endI=new QStandardItem(QObject::tr("�������"));
    modelPro->setItem(1,2,endI);
}
/*************************************************************************
* ��������: SavePgm
* ��    ��: ����ʾ�̳���
* �������: file	�����ļ���ָ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCom20::SavePgm(QFile *file)
{
    //�����ļ�ͷ
    PGM_HEAD head;
    head.cmdL = modelPro->rowCount()-2;
    file->write((char*)(&head),sizeof(head));

    //��������
    for(int i = 1;i<modelPro->rowCount()-1;i++)
    {
        QStandardItem *item = modelPro->item(i,1);
        ((TCmd*)item)->OnSave(file);
    }

    //����ѵ�
    file->write((char*)(&comStk),sizeof(comStk));

    bOpen = false;
}
/*************************************************************************
* ��������: OpenPgm
* ��    ��: ��ʾ�̳���
* �������: file	���ļ���ָ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCom20::OpenPgm(QFile *file)
{
    //��ճ����ļ�
    modelPro->clear();

    //��ȡ�ļ�ͷ
    PGM_HEAD head;
    file->read((char*)(&head),sizeof(head));

    TCmd::STR_PARA *para=new TCmd::STR_PARA[head.cmdL];
    //��ȡ��������
    file->read((char*)para,sizeof(TCmd::STR_PARA)*head.cmdL);

    //��ȡ�ѵ�����
    file->read((char*)(&comStk),sizeof(comStk));

    AddCmd(0);
    QStandardItem *startI=new QStandardItem(QObject::tr("����ʼ"));
    modelPro->setItem(0,2,startI);
    AddCmd(1);
    QStandardItem *endI=new QStandardItem(QObject::tr("�������"));
    modelPro->setItem(1,2,endI);


    //��������
    for(int i=0;i<head.cmdL;i++)
    {
        TCmd *cmd;
        quint8 act[] = {TCmd::X1MOV, TCmd::Z1MOV,TCmd::UMOV, TCmd::X2MOV,TCmd::Z2MOV,
                        TCmd::INPUT, TCmd::OUTPUT, TCmd::OUTPUTG, TCmd::STACK, TCmd::STACK + 1};
        for(int j = 0; j < sizeof(act)/sizeof(quint8) - 1; j++)
        {
            if((para[i].action == act[j]) ||
               ((para[i].action > act[j])&&(para[i].action < act[j + 1]))){
                cmd = create_cmd[j]();

                if(j == 6){
                    cmd->setIcon(QIcon(":/Res/image/icon_output2_gpio.png"));
                }
                break;
            }
        }

        cmd->para=para[i];

        AddCmd(i+1);
        SetItem(i+1,0,cmd->ConsCombiItem());
        SetItem(i+1,1,(QStandardItem*)cmd);
        SetItem(i+1,2,cmd->ConsTitItem());
    }

    delete []para;

    bOpen = false;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom20::snd()
{
    //plsTran();

    //�������г������ݣ�����pd����
    int iS = modelPro->rowCount()-2;
    int iL = sizeof(TCmd::STR_PARA);
    //printf("iS:%d,iL:%d\n",iS,iL);
    iS *= iL;

    quint8 *pd = new quint8[iS];
    for(int i = 1;i<modelPro->rowCount()-1;i++)
    {
        //if((i == 2)&&modelPro->rowCount()>3)
        //    continue;

        TCmd* itemCmd = (TCmd*)modelPro->item(i,1);
        quint8 *pdS = (quint8*)(&itemCmd->para);
        memcpy(pd+iL*(i-1),pdS,iL);
    }


    int iF = iS/6;
    if(iS%6)
        iF++;

    iSndN = iF;
    //printf("iF:%x\n",iF);
    //����pd��������
    CAN_Frame canS;
    for(int i = iF;i>0;i--)
    {
        //if(i == 3)
        //    continue;



        if((i % 255) == 0){
            canS.data[0] = com_add + i / 255 - 1;
            canS.data[1] = 255;
        }else{
            canS.data[0] = com_add + i / 255;
            canS.data[1] = i % 255;
        }

        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        //a5drv.can_send(&canS);
        SndFrame(&canS);
        //printf("%x %x %x %x %x %x %x %x\n",canS.data[0],canS.data[1],canS.data[2],canS.data[3],
        //                                 canS.data[4],canS.data[5],canS.data[6],canS.data[7]);

        //for(int j = 0;j<10000000;j++);
    }

    //RplsTran();

    return true;
}
/*************************************************************************
* ��������: plsTran
* ��    ��: ת��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCom20::plsTran()
{
    /*int ipls[] = {0,1,2,3,4,3,4};

    for(int i = 1;i<modelPro->rowCount()-1;i++){
        TCmd* itemCmd = (TCmd*)modelPro->item(i,1);

        if(itemCmd->para.action <= TCmd::ZMOV){
            int index = ipls[itemCmd->para.action - TCmd::XMOV];
            itemCmd->para.dist = itemCmd->para.dist * 1000 / com02.para[index].pls_equ;
        }
    }*/
}
/*************************************************************************
* ��������: RplsTran
* ��    ��: ��������ת��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TCom20::RplsTran()
{
    /*int ipls[] = {0,1,2,3,4,3,4};

    for(int i = 1;i<modelPro->rowCount()-1;i++){
        TCmd* itemCmd = (TCmd*)modelPro->item(i,1);

        if(itemCmd->para.action <= TCmd::ZMOV){
            int index = ipls[itemCmd->para.action - TCmd::XMOV];
            itemCmd->para.dist = itemCmd->para.dist * com02.para[index].pls_equ / 1000;
        }
    }*/
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom20::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    printf("pd7:%d,iSndN:%d",pd[7],iSndN);
    if(pd[7] != iSndN)
        return false;
    if((pd[2] != 'A')||(pd[3] != 'C')||(pd[4] != 'K'))
        return false;

    bNewForSnd = false;   //��λ���ͳɹ��ı�־
    return true;
}
/*************************************************************************
* ��������: UpdateUI
* ��    ��: ����UI��ʾ
* �������: bSuc	ͨѶ�ɹ���ʧ�ܵı�־
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom20::UpdateUI(bool bSuc)
{
    if(bSuc)
        warn.ShowW2L(TWarn::W_FILES);
}







/*************************************************************************
* ��������: TCom70
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TCom70::TCom70()
{
    com_add  = COM70;
    eptNum   = 1;

    para.height  = 10;
    para.num     = 10;
    para.stkp    = 1;
    for(int i = 0;i<10;i++)
        para.interval[i] = 100;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom70::snd()
{
    int iS = sizeof(STR_PARA);

    int iF = iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd = (quint8*)(&para);
    for(int i = iF;i>0;i--)
    {
        canS.data[0] = com_add;
        canS.data[1] = i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j = 0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TCom70::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd = (quint8*)vecRcv[0].data;
    if((pd[2] != 'A')||(pd[3] != 'C')||(pd[4] != 'K'))
        return false;

    return true;
}









/*************************************************************************
* ��������: TComE0
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TComE0::TComE0()
{
    com_add =COME0;
    eptNum  =1;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TComE0::snd()
{
    int iS=sizeof(STR_PARA);

    int iF=iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd=(quint8*)(&para);
    for(int i=iF;i>0;i--)
    {
        canS.data[0]=com_add;
        canS.data[1]=i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j=0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: chk
* ��    ��: У����յ����ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TComE0::chk()
{
    if(!TCom::chk())
        return false;

    quint8* pd=(quint8*)vecRcv[0].data;
    if((pd[3]!='A')||(pd[4]!='C')||(pd[5]!='K'))
        return false;

    return true;
}





/*************************************************************************
* ��������: TComF0
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TComF0::TComF0()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gbk"));//���������������

    com_add = COMF0;
    eptNum  = sizeof(STR_PARA_R) / 6 + ((sizeof(STR_PARA_R) % 6) == 0) ? 0 : 1;

    str_sub_sta.push_back(QObject::tr("����"));
    str_sub_sta.push_back(QObject::tr("ֹͣδ��λ"));
    str_sub_sta.push_back(QObject::tr("��ָ��"));
    str_sub_sta.push_back(QObject::tr("��ѭ��"));
    str_sub_sta.push_back(QObject::tr("ȫ�Զ�"));
    str_sub_sta.push_back(QObject::tr("��ͣ"));
    str_sub_sta.push_back(QObject::tr("ֹͣ"));
    str_sub_sta.push_back(QObject::tr("��ͣ"));
    str_sub_sta.push_back(QObject::tr("��λ��"));
    str_sub_sta.push_back(QObject::tr("�㶯"));
    str_sub_sta.push_back(QObject::tr("�ֶ�"));
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TComF0::snd()
{
    int iS=sizeof(STR_PARA_S);

    int iF=iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd=(quint8*)(&spara);
    for(int i=iF;i>0;i--)
    {
        canS.data[0]=com_add;
        canS.data[1]=i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j=0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: UpdateUI
* ��    ��: ����UI��ʾ
* �������: bSuc	ͨѶ�ɹ���ʧ�ܵı�־
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TComF0::UpdateUI(bool bSuc)
{
    if(!bSuc)
        return false;

    quint8* pdD=(quint8*)(&rpara);
    for(int i=0;i<vecRcv.size();i++)
    {
        quint8* pdS=(quint8*)vecRcv[i].data;
        memcpy(pdD+6*i,pdS+2,6);
    }

    //������ת��
    /*rpara.xpos = rpara.xpos * com02.para[0].pls_equ / 1000;
    rpara.y1pos = rpara.y1pos * com02.para[1].pls_equ / 1000;
    rpara.z1pos = rpara.z1pos * com02.para[2].pls_equ / 1000;
    rpara.y2pos = rpara.y2pos * com02.para[3].pls_equ / 1000;
    rpara.z2pos = rpara.z2pos * com02.para[4].pls_equ / 1000;*/
    float fxp = ((float)rpara.xpos) / 100.0;
    float fy1p = ((float)rpara.y1pos) / 100.0;
    float fz1p = ((float)rpara.z1pos) / 100.0;
    float fy2p = ((float)rpara.y2pos) / 100.0;
    float fz2p = ((float)rpara.z2pos) / 100.0;

    widMana->mainW->ui->lblXPos->setText(QString("X1:") + QString::number(fxp,'f',2) + QString("mm"));
    widMana->mainW->ui->lblY1Pos->setText(QString("Z1:") + QString::number(fy1p,'f',2) + QString("mm"));
    widMana->mainW->ui->lblZ1Pos->setText(QString("U:") + QString::number(fz1p,'f',2) + QObject::tr("��"));
    widMana->mainW->ui->lblY2Pos->setText(QString("X2:") + QString::number(fy2p,'f',2) + QString("mm"));
    widMana->mainW->ui->lblZ2Pos->setText(QString("Z2:") + QString::number(fz2p,'f',2) + QString("mm"));

    widMana->mainW->ui->btnStus->setText(datToSta(rpara.sub_sta));

    widMana->frm_run.UpdateUI();
    //widMana->frm_run.ui->tblV_Pro->selectRow(rpara.radd);

    widMana->frm_monit.UpdateIO();

    UpdateLht();

    //printf("I:%x,%x,%x,%x,%x,%x\n",rpara.in[0],rpara.in[1],rpara.in[2],rpara.in[3],rpara.in[4],rpara.in[5]);
    //printf("O:%x,%x,%x,%x\n",rpara.out[0],rpara.out[1],rpara.out[2],rpara.out[3]);

    return true;
}
/*************************************************************************
* ��������: UpdateLht
* ��    ��: ����ָʾ��
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void TComF0::UpdateLht()
{
    /*if(rpara.sub_sta == RESTTING)
        a5drv.led_on(3);
    else
        a5drv.led_off(3);*/
    if(rpara.sub_sta == STP_NO_RST)
        a5drv.led_off(3);

    if(rpara.sub_sta == EMERGENCY)
        a5drv.led_on(0);
    else
        a5drv.led_off(0);
    /*str_sub_sta.push_back(QObject::tr("����"));
    str_sub_sta.push_back(QObject::tr("ֹͣδ��λ"));
    str_sub_sta.push_back(QObject::tr("��ָ��"));
    str_sub_sta.push_back(QObject::tr("��ѭ��"));
    str_sub_sta.push_back(QObject::tr("ȫ�Զ�"));
    str_sub_sta.push_back(QObject::tr("��ͣ"));
    str_sub_sta.push_back(QObject::tr("ֹͣ"));
    str_sub_sta.push_back(QObject::tr("��ͣ"));
    str_sub_sta.push_back(QObject::tr("��λ��"));
    str_sub_sta.push_back(QObject::tr("�㶯"));
    str_sub_sta.push_back(QObject::tr("�ֶ�"));
            IDLE,STP_NO_RST,STEP,SGL_CLE,AUTO,STOP,EMERGENCY,RESTTING,JOG,MANUAL*/
    if(rpara.sub_sta == STEP ||
       rpara.sub_sta == SGL_CLE ||
       rpara.sub_sta == AUTO ||
       rpara.sub_sta == RESTTING ||
       rpara.sub_sta == JOG){
                a5drv.led_on(1);
            }else{
                a5drv.led_off(1);
            }
}

/*************************************************************************
* ��������: datToSta
* ��    ��: ��λ��״̬ת��������
* �������: dat	״ֵ̬
* �������: ��
* �� �� ֵ: ת��������
*************************************************************************/
QString TComF0::datToSta(quint8 dat)
{
    dat+=1;

    if(dat<str_sub_sta.size())
        return str_sub_sta[dat];
    else
        return QString("");

    /*if(dat==0xff)
        return str_sub_sta[0];
    else
    {
        if(dat<str_sub_sta.size()-1)
          return str_sub_sta[dat+1];
    }*/
}






/*************************************************************************
* ��������: TComF1
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TComF1::TComF1()
{
    com_add =COMF1;
    eptNum  =0;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TComF1::snd()
{
    int iS=sizeof(STR_PARA);

    int iF=iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd=(quint8*)(&para);
    for(int i=iF;i>0;i--)
    {
        canS.data[0]=com_add;
        canS.data[1]=i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j=0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: UpdateUI
* ��    ��: ����UI��ʾ
* �������: bSuc	ͨѶ�ɹ���ʧ�ܵı�־
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TComF1::UpdateUI(bool bSuc)
{
    if(!bSuc)
        return false;

    quint8* pdD=(quint8*)(com02.para);
    for(int i=0;i<vecRcv.size();i++)
    {
        quint8* pdS=(quint8*)vecRcv[i].data;
        memcpy(pdD+6*i,pdS+2,6);
    }

    widMana->frm_setup.SetSeroPara();

    return true;
}





/*************************************************************************
* ��������: TComF2
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TComF2::TComF2()
{
    com_add =COMF2;
    eptNum  =0;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TComF2::snd()
{
    int iS=sizeof(STR_PARA);

    int iF=iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd=(quint8*)(&para);
    for(int i=iF;i>0;i--)
    {
        canS.data[0]=com_add;
        canS.data[1]=i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j=0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: UpdateUI
* ��    ��: ����UI��ʾ
* �������: bSuc	ͨѶ�ɹ���ʧ�ܵı�־
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TComF2::UpdateUI(bool bSuc)
{
    if(!bSuc)
        return false;

    quint8* pdD=(quint8*)(&com07.para);
    for(int i=0;i<vecRcv.size();i++)
    {
        quint8* pdS=(quint8*)vecRcv[i].data;
        memcpy(pdD+6*i,pdS+2,6);
    }

    widMana->frm_setup.SetResetPara();

    return true;
}



/*************************************************************************
* ��������: TComF3
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TComF3::TComF3()
{
    com_add =COMF3;
    eptNum  =0;
}
/*************************************************************************
* ��������: snd
* ��    ��: �������ݰ�
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TComF3::snd()
{
    int iS=sizeof(STR_PARA);

    int iF=iS/6;
    if(iS%6)
        iF++;

    CAN_Frame canS;
    quint8 *pd=(quint8*)(&para);
    for(int i=iF;i>0;i--)
    {
        canS.data[0]=com_add;
        canS.data[1]=i;
        memcpy(canS.data+2,pd+(iF-i)*6,6);
        //if(!a5drv.can_send(&canS))
        //    return false;
        SndFrame(&canS);
        //for(int j=0;j<1000;j++);
    }
    return true;
}
/*************************************************************************
* ��������: UpdateUI
* ��    ��: ����UI��ʾ
* �������: bSuc	ͨѶ�ɹ���ʧ�ܵı�־
* �������: ��
* �� �� ֵ: �ɹ�����true��ʧ�ܷ���false
*************************************************************************/
bool TComF3::UpdateUI(bool bSuc)
{
    //printf("bSuc:%d\n",bSuc);
    //if(!bSuc)
    //    return false;

    AnaCmd();
    //widMana->frm_teach.InitTblVPro();

    return true;
}
/*************************************************************************
* ��������: AnaCmd
* ��    ��: ����ʾ�̳���
* �������: file	���ļ���ָ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TComF3::AnaCmd()
{
    //��ճ����ļ�
    com20.modelPro->clear();

    quint8* pdD=new quint8[vecRcv.size() * 6];
    for(int i=0;i<vecRcv.size();i++)
    {
        quint8* pdS=(quint8*)vecRcv[i].data;
        memcpy(pdD+6*i,pdS+2,6);
    }

    //printf("\n\n\n\nvecRcv.size():%d,vecRcv.size()*6:%d\n",vecRcv.size(),vecRcv.size()*6);
    /*printf("%d\n",sizeof(TCom06::STR_PARA));
    for(int i = 0; i < 16; i++){
        if(i%16 == 0){
            printf("\n");
        }

        printf("%x ",*(pdD+44+i));

    }*/

    memcpy((quint8*)(&comStk.para),pdD,sizeof(TCom06::STR_PARA));

    com20.AddCmd(0);
    QStandardItem *startI=new QStandardItem(QObject::tr("����ʼ"));
    com20.SetItem(0,2,startI);
    com20.AddCmd(1);
    QStandardItem *endI=new QStandardItem(QObject::tr("�������"));
    com20.SetItem(1,2,endI);

    int                iCmd  = (vecRcv.size() * 6 - sizeof(TCom06::STR_PARA))/(sizeof(TCmd::STR_PARA));
    TCmd::STR_PARA     *para = (TCmd::STR_PARA*)(pdD + sizeof(TCom06::STR_PARA));
    //��������
    for(int i=0;i<iCmd;i++)
    {
        TCmd *cmd;
        quint8 act[] = {TCmd::INPUT, TCmd::INPUTG, TCmd::OUTPUT, TCmd::OUTPUTG, TCmd::STACK ,TCmd::STACK + 1};
        for(int j = 0; j < sizeof(act)/sizeof(quint8); j++)
        {
            if(para[i].action < act[j]){
                cmd = create_cmd[j]();

                if(j == 1)
                    ((TCmd_In*)cmd)->ioT = TCmd::SPECIAL;
                else if(j ==2)
                    ((TCmd_In*)cmd)->ioT = TCmd::GENERAL;
                else if(j == 3)
                    ((TCmd_Out*)cmd)->ioT = TCmd::SPECIAL;
                else if(j == 4)
                    ((TCmd_Out*)cmd)->ioT = TCmd::GENERAL;

                break;
            }
        }

        cmd->para=para[i];

        com20.AddCmd(i+1);
        com20.SetItem(i+1,0,cmd->ConsCombiItem());
        com20.SetItem(i+1,1,(QStandardItem*)cmd);
        com20.SetItem(i+1,2,cmd->ConsTitItem());
    }

    delete []pdD;
}

//ͨѶȫ�ֱ���
TCom01  com01;       //���ð汾�ŵ�
TCom02  com02;       //�ŷ�����
TCom03  com03;       //���ô�����ʽ��
TCom04  com04;       //���ü������
TCom05  com05;       //���ò�Ʒ
TCom06  com06,comStk;       //���öѵ�
TCom07  com07;       //��λ����
TCom08  com08;       //�����������
TCom20  com20;       //ʾ�̳���
TCom70  com70;       //�ѵ�ָ��
TComF0  comF0;       //��ѯ����
TComF1  comF1;       //��ȡ�ŷ�����
TComF2  comF2;       //��ȡ��λ����
TComF3  comF3;       //��ȡʾ�̳���
TComE0  comE0;       //���з�ʽָ��


QMutex mutex_com;               //�̻߳������
QVector<TCom*> pComBuf1;        //�����Բ�ѯ����
QVector<TCom*> pComBuf2;        //�����Բ�ѯ����

//==========================================================================================
// End of file.
//==========================================================================================

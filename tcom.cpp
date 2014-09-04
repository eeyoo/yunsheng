/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: tcom.cpp

* 功能描述: 通讯类文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
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
* 函数名称: TCom
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCom::TCom()
{
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送通讯包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
*************************************************************************/
bool TCom::snd()
{
}
/*************************************************************************
* 函数名称: rcv
* 功    能: 接收返回数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
        //超时出错
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
        //错误处理，从第二帧开始，如果帧地址和当前地址不同，或者帧序号大于等于当前序号，都作为出错
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
            //数据接收完成
            if(canR.data[1] == 0x01){

                if(com_add == COMF3){   //接收示教程序
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
* 函数名称: DoCom
* 功    能: 执行一次完整通讯
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: chk
* 功    能: 校验接收数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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

    //校验接收的帧数是否为期望值
    if(eptNum != 0)
    {
        if(eptNum != iS)
            return false;
    }

    quint8 add;
    add = vecRcv[0].data[0];
    //printf("add:%x,com_add:%x\n",add,com_add);
    //校验地址是不是需要接收的地址
    if(add != com_add)
        return false;
    //校验所有帧中的地址是否相同
    for(int i = 1;i<iS;i++)
    {
        if(add != (quint8)vecRcv[i].data[0])
        {
            //qDebug("add:%x,data[0]:%x",add,vecRcv[i].data[0]);
            return false;
        }
    }
    //printf("111\n");
    //校验帧的序号是否连续减少
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
* 函数名称: SndFrame
* 功    能: 发送一个CAN帧
* 输入参数: frame，can帧的指针
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TCom01
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCom01::TCom01()
{
    com_add  = COM01;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TCom02
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCom02::TCom02()
{
    com_add  = COM02;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: chk
* 功    能: 校验接收数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TCom03
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCom03::TCom03()
{
    com_add  = COM03;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TCom04
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCom04::TCom04()
{
    com_add  = COM04;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TCom05
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCom05::TCom05()
{
    com_add  = COM05;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TCom06
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCom06::TCom06()
{
    com_add  = COM06;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TCom07
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCom07::TCom07()
{
    com_add  = COM07;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TCom08
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCom08::TCom08()
{
    com_add  = COM08;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TCom20
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: AddCmd
* 功    能: 添加一条示教命令
* 输入参数: rIndex添加命令的位置
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TCom20::AddCmd(int rIndex)
{
    modelPro->insertRow(rIndex);
    bNewForSnd = true;
    bOpen      = true;
}
/*************************************************************************
* 函数名称: DelCmd
* 功    能: 删除一条示教命令
* 输入参数: rIndex删除命令的位置
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: SetItem
* 功    能: 设置示教命令Item的内容
* 输入参数: row		设置的行
			column	设置的列
			item	item的内容
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TCom20::SetItem(int row,int column,QStandardItem* item)
{
    modelPro->setItem(row,column,item);
    bNewForSnd = true;
    bOpen      = true;
}
/*************************************************************************
* 函数名称: NewPgm
* 功    能: 新建示教程序
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TCom20::NewPgm()
{
    //清空程序文件
    modelPro->clear();

    AddCmd(0);
    QStandardItem *startI=new QStandardItem(QObject::tr("程序开始"));
    modelPro->setItem(0,2,startI);
    AddCmd(1);
    QStandardItem *endI=new QStandardItem(QObject::tr("程序结束"));
    modelPro->setItem(1,2,endI);
}
/*************************************************************************
* 函数名称: SavePgm
* 功    能: 保存示教程序
* 输入参数: file	保存文件的指针
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TCom20::SavePgm(QFile *file)
{
    //保存文件头
    PGM_HEAD head;
    head.cmdL = modelPro->rowCount()-2;
    file->write((char*)(&head),sizeof(head));

    //保存命令
    for(int i = 1;i<modelPro->rowCount()-1;i++)
    {
        QStandardItem *item = modelPro->item(i,1);
        ((TCmd*)item)->OnSave(file);
    }

    //保存堆叠
    file->write((char*)(&comStk),sizeof(comStk));

    bOpen = false;
}
/*************************************************************************
* 函数名称: OpenPgm
* 功    能: 打开示教程序
* 输入参数: file	打开文件的指针
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TCom20::OpenPgm(QFile *file)
{
    //清空程序文件
    modelPro->clear();

    //读取文件头
    PGM_HEAD head;
    file->read((char*)(&head),sizeof(head));

    TCmd::STR_PARA *para=new TCmd::STR_PARA[head.cmdL];
    //读取命令数据
    file->read((char*)para,sizeof(TCmd::STR_PARA)*head.cmdL);

    //读取堆叠数据
    file->read((char*)(&comStk),sizeof(comStk));

    AddCmd(0);
    QStandardItem *startI=new QStandardItem(QObject::tr("程序开始"));
    modelPro->setItem(0,2,startI);
    AddCmd(1);
    QStandardItem *endI=new QStandardItem(QObject::tr("程序结束"));
    modelPro->setItem(1,2,endI);


    //解析命令
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
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
*************************************************************************/
bool TCom20::snd()
{
    //plsTran();

    //整合所有程序数据，放入pd缓冲
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
    //发送pd缓冲数据
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
* 函数名称: plsTran
* 功    能: 转换脉冲数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: RplsTran
* 功    能: 脉冲数逆转换
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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

    bNewForSnd = false;   //置位发送成功的标志
    return true;
}
/*************************************************************************
* 函数名称: UpdateUI
* 功    能: 更新UI显示
* 输入参数: bSuc	通讯成功、失败的标志
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
*************************************************************************/
bool TCom20::UpdateUI(bool bSuc)
{
    if(bSuc)
        warn.ShowW2L(TWarn::W_FILES);
}







/*************************************************************************
* 函数名称: TCom70
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TComE0
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TComE0::TComE0()
{
    com_add =COME0;
    eptNum  =1;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TComF0
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TComF0::TComF0()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gbk"));//设置中文字体编码

    com_add = COMF0;
    eptNum  = sizeof(STR_PARA_R) / 6 + ((sizeof(STR_PARA_R) % 6) == 0) ? 0 : 1;

    str_sub_sta.push_back(QObject::tr("空闲"));
    str_sub_sta.push_back(QObject::tr("停止未复位"));
    str_sub_sta.push_back(QObject::tr("单指令"));
    str_sub_sta.push_back(QObject::tr("单循环"));
    str_sub_sta.push_back(QObject::tr("全自动"));
    str_sub_sta.push_back(QObject::tr("暂停"));
    str_sub_sta.push_back(QObject::tr("停止"));
    str_sub_sta.push_back(QObject::tr("急停"));
    str_sub_sta.push_back(QObject::tr("复位中"));
    str_sub_sta.push_back(QObject::tr("点动"));
    str_sub_sta.push_back(QObject::tr("手动"));
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: UpdateUI
* 功    能: 更新UI显示
* 输入参数: bSuc	通讯成功、失败的标志
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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

    //脉冲数转换
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
    widMana->mainW->ui->lblZ1Pos->setText(QString("U:") + QString::number(fz1p,'f',2) + QObject::tr("°"));
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
* 函数名称: UpdateLht
* 功    能: 更新指示灯
* 输入参数: 无
* 输出参数: 无
* 返 回 值:
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
    /*str_sub_sta.push_back(QObject::tr("空闲"));
    str_sub_sta.push_back(QObject::tr("停止未复位"));
    str_sub_sta.push_back(QObject::tr("单指令"));
    str_sub_sta.push_back(QObject::tr("单循环"));
    str_sub_sta.push_back(QObject::tr("全自动"));
    str_sub_sta.push_back(QObject::tr("暂停"));
    str_sub_sta.push_back(QObject::tr("停止"));
    str_sub_sta.push_back(QObject::tr("急停"));
    str_sub_sta.push_back(QObject::tr("复位中"));
    str_sub_sta.push_back(QObject::tr("点动"));
    str_sub_sta.push_back(QObject::tr("手动"));
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
* 函数名称: datToSta
* 功    能: 下位机状态转换成文字
* 输入参数: dat	状态值
* 输出参数: 无
* 返 回 值: 转换的文字
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
* 函数名称: TComF1
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TComF1::TComF1()
{
    com_add =COMF1;
    eptNum  =0;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: UpdateUI
* 功    能: 更新UI显示
* 输入参数: bSuc	通讯成功、失败的标志
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TComF2
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TComF2::TComF2()
{
    com_add =COMF2;
    eptNum  =0;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: UpdateUI
* 功    能: 更新UI显示
* 输入参数: bSuc	通讯成功、失败的标志
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: TComF3
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TComF3::TComF3()
{
    com_add =COMF3;
    eptNum  =0;
}
/*************************************************************************
* 函数名称: snd
* 功    能: 发送数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: UpdateUI
* 功    能: 更新UI显示
* 输入参数: bSuc	通讯成功、失败的标志
* 输出参数: 无
* 返 回 值: 成功返回true，失败返回false
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
* 函数名称: AnaCmd
* 功    能: 解析示教程序
* 输入参数: file	打开文件的指针
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TComF3::AnaCmd()
{
    //清空程序文件
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
    QStandardItem *startI=new QStandardItem(QObject::tr("程序开始"));
    com20.SetItem(0,2,startI);
    com20.AddCmd(1);
    QStandardItem *endI=new QStandardItem(QObject::tr("程序结束"));
    com20.SetItem(1,2,endI);

    int                iCmd  = (vecRcv.size() * 6 - sizeof(TCom06::STR_PARA))/(sizeof(TCmd::STR_PARA));
    TCmd::STR_PARA     *para = (TCmd::STR_PARA*)(pdD + sizeof(TCom06::STR_PARA));
    //解析命令
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

//通讯全局变量
TCom01  com01;       //配置版本号等
TCom02  com02;       //伺服配置
TCom03  com03;       //配置待机方式等
TCom04  com04;       //配置检测允许
TCom05  com05;       //配置产品
TCom06  com06,comStk;       //配置堆叠
TCom07  com07;       //复位配置
TCom08  com08;       //电机方向配置
TCom20  com20;       //示教程序
TCom70  com70;       //堆叠指令
TComF0  comF0;       //查询命令
TComF1  comF1;       //读取伺服参数
TComF2  comF2;       //读取复位数据
TComF3  comF3;       //读取示教程序
TComE0  comE0;       //运行方式指令


QMutex mutex_com;               //线程互斥变量
QVector<TCom*> pComBuf1;        //周期性查询数据
QVector<TCom*> pComBuf2;        //触发性查询数据

//==========================================================================================
// End of file.
//==========================================================================================

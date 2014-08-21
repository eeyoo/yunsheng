/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: tcmd.cpp

* 功能描述: 自定义运行指令文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#include "tcmd.h"
#include "ui_frm_teach.h"
#include "twidmana.h"
#include "tlineedit.h"

/*************************************************************************
* 函数名称: TCmd
* 功    能: 构造函数
* 输入参数: fileName
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCmd::TCmd(const QString &fileName)
        :QStandardItem((QIcon)(fileName),QString(""))
{
    cls_typ = CLS_BSE;
}
/*************************************************************************
* 函数名称: Id2Til
* 功    能: 转换Id到标题
* 输入参数: Id	需要转换的Id
* 输出参数: 无
* 返 回 值: 转换好的标题
*************************************************************************/
QString TCmd::Id2Til(CMDID Id)
{
    return QString("");
}
/*************************************************************************
* 函数名称: ConsCombiItem
* 功    能: 构造组合Item
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 组合Item
*************************************************************************/
QStandardItem* TCmd::ConsCombiItem()
{
    if(para.combin == 0)
        return new QStandardItem(QObject::tr(""));

    return new QStandardItem(QObject::tr("同动%1").arg(para.combin));
}
/*************************************************************************
* 函数名称: OnSave
* 功    能: 保存示教命令
* 输入参数: file	保存文件的指针
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TCmd::OnSave(QFile *file)
{
    file->write((char*)(&para),sizeof(para));
}
/*************************************************************************
* 函数名称: OnOpen
* 功    能: 打开示教命令
* 输入参数: file	打开文件的指针
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TCmd::OnOpen(QFile *file)
{
    file->read((char*)(&para),sizeof(para));
}





/*************************************************************************
* 函数名称: TCmd_Mov
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCmd_Mov::TCmd_Mov()
        :TCmd(":/Icon/Btn/Res/btn/motor.png")
{
    cls_typ = CLS_MOV;
    memset(&para,0,sizeof(STR_PARA));

    //通讯数据
    com_add  = COM7F;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: ConsPara
* 功    能: 构造命令参数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
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
* 函数名称: getCmdTit
* 功    能: 获取命令的标题
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 命令标题
*************************************************************************/
QString TCmd_Mov::getCmdTit()
{
    float dist = ((float)para.dist) / 100.0;
    if(para.action == TCmd::UMOV){
        return QObject::tr("%1:角度%2，速度%3，延时%4")
                        .arg(Id2Til((CMDID)para.action))
                        .arg(QString::number(dist,'f',2))
                        .arg(para.spd)
                        .arg(para.wattim);
    }else{
        return QObject::tr("%1:位置%2，速度%3，延时%4")
                        .arg(Id2Til((CMDID)para.action))
                        .arg(QString::number(dist,'f',2))
                        .arg(para.spd)
                        .arg(para.wattim);
    }

}
/*************************************************************************
* 函数名称: ConsTitItem
* 功    能: 构造命令Item
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 命令Item
*************************************************************************/
QStandardItem* TCmd_Mov::ConsTitItem()
{
    return new QStandardItem(getCmdTit());
}
/*************************************************************************
* 函数名称: OnCmdClk
* 功    能: 响应命令的单击事件
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: snd
* 功    能: 发送命令数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
*************************************************************************/
bool TCmd_Mov::snd()
{
    //脉冲数转换
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
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
* 函数名称: Id2Til
* 功    能: 转换Id到标题
* 输入参数: Id	需要转换的Id
* 输出参数: 无
* 返 回 值: 转换好的标题
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
* 函数名称: TCmd_In
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCmd_In::TCmd_In()
        :TCmd(":/Res/image/inicon.PNG")
{
    cls_typ = CLS_IO;
    memset(&para,0,sizeof(STR_PARA));

    //通讯数据
    com_add  = COM7F;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: ConsPara
* 功    能: 构造命令参数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
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
* 函数名称: getCmdTit
* 功    能: 获取命令标题
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 命令标题
*************************************************************************/
QString TCmd_In::getCmdTit()
{
    return QObject::tr("%1:%2,延时%3")
                    .arg(Id2Til((CMDID)para.action))
                    .arg(para.dist == 1?QObject::tr("开"):QObject::tr("关"))
                    .arg(para.wattim);
}
/*************************************************************************
* 函数名称: ConsTitItem
* 功    能: 构造命令Item
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 命令Item
*************************************************************************/
QStandardItem* TCmd_In::ConsTitItem()
{
    return new QStandardItem(getCmdTit());
}
/*************************************************************************
* 函数名称: OnCmdClk
* 功    能: 响应命令单击事件
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: snd
* 功    能: 发送命令数据
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
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
* 函数名称: Id2Til
* 功    能: 转换Id到标题
* 输入参数: Id	需要转换的Id
* 输出参数: 无
* 返 回 值: 转换好的标题
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
* 函数名称: TCmd_Out
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCmd_Out::TCmd_Out()
        :TCmd(":/Res/image/icon_output1_gpio.png")
{
    cls_typ = CLS_IO;
    memset(&para,0,sizeof(STR_PARA));

    //通讯数据
    com_add  = COM7F;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: ConsPara
* 功    能: 构造命令参数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
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
* 函数名称: getCmdTit
* 功    能: 获取命令标题
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 命令标题
*************************************************************************/
QString TCmd_Out::getCmdTit()
{
    return QObject::tr("%1:%2,延时%3")
                    .arg(Id2Til((CMDID)para.action))
                    .arg(para.dist == 1?QObject::tr("开"):QObject::tr("关"))
                    .arg(para.wattim);
}
/*************************************************************************
* 函数名称: ConsTitItem
* 功    能: 构造命令Item
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 命令Item
*************************************************************************/
QStandardItem* TCmd_Out::ConsTitItem()
{
    return new QStandardItem(getCmdTit());
}
/*************************************************************************
* 函数名称: OnCmdClk
* 功    能: 响应命令单击事件
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: snd
* 功    能: 发送命令数据
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
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
* 函数名称: chk
* 功    能: 校验接收的数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
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
* 函数名称: Id2Til
* 功    能: 转换Id到标题
* 输入参数: Id	需要转换的Id
* 输出参数: 无
* 返 回 值: 转换好的标题
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
* 函数名称: TCmd_Stk
* 功    能: 构造函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TCmd_Stk::TCmd_Stk()
        :TCmd(":/Res/image/icon_stack.png")
{
    cls_typ = CLS_STK;
    memset(&para,0,sizeof(STR_PARA));

    //通讯数据
    com_add  = COM7F;
    eptNum   = 1;
}
/*************************************************************************
* 函数名称: ConsPara
* 功    能: 构造命令的参数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
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
* 函数名称: getCmdTit
* 功    能: 获取命令标题
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 命令标题
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
    return QObject::tr("%1%2,延时%3")
                    .arg(Id2Til((CMDID)para.action))
                    .arg(strT)
                    .arg(para.wattim);
}
/*************************************************************************
* 函数名称: ConsTitItem
* 功    能: 构造命令Item
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 命令Item
*************************************************************************/
QStandardItem* TCmd_Stk::ConsTitItem()
{
    return new QStandardItem(getCmdTit());
}
/*************************************************************************
* 函数名称: OnCmdClk
* 功    能: 响应命令的单击事件
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: snd
* 功    能: 发送命令数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
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
* 函数名称: chk
* 功    能: 校验接收数据包
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 成功true，失败false
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
* 函数名称: Id2Til
* 功    能: 转换Id到标题
* 输入参数: Id	需要转换的Id
* 输出参数: 无
* 返 回 值: 转换好的标题
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
* 函数名称: CreateMX1
* 功    能: 创建X1运行命令
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 运行命令
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
* 函数名称: CreateMZ1
* 功    能: 创建Z1运行命令
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 运行命令
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
* 函数名称: CreateMU
* 功    能: 创建U运行命令
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 运行命令
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
* 函数名称: CreateMX2
* 功    能: 创建X2运行命令
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 运行命令
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
* 函数名称: CreateMZ2
* 功    能: 创建Z2运行命令
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 运行命令
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
* 函数名称: CreateI
* 功    能: 创建输入命令
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 输入命令
*************************************************************************/
TCmd* CreateI()
{
    TCmd *cmd = new TCmd_In;
    cmd->setIcon(QIcon(":/Res/image/icon_input_gpio.png"));
    //((TCmd_In*)cmd)->ioT  = TCmd::SPECIAL;
    return cmd;
}
/*************************************************************************
* 函数名称: CreateO
* 功    能: 创建输出命令
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 输出命令
*************************************************************************/
TCmd* CreateO()
{
    TCmd *cmd = new TCmd_Out;
    //((TCmd_Out*)cmd)->ioT  = TCmd::SPECIAL;
    return cmd;
}
/*************************************************************************
* 函数名称: CreateStk
* 功    能: 创建堆叠命令
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 堆叠命令
*************************************************************************/
TCmd* CreateStk()
{
    return new TCmd_Stk;
}

/*****************命令数组***********************/
Create_Cmd create_cmd[] =
{
    CreateMX1,CreateMZ1,CreateMU,CreateMX2,CreateMZ2,
    CreateI,CreateO,CreateO,CreateStk
};								



TCmd*            pCurCmd;               //当前手动操作命令
int              iCurCmd = 0;		//当前操作命令
TCmd_Mov*        cmd_movX;              //手动 X轴运动命令通讯
TCmd_Mov*        cmd_movY1;		//手动 Y1轴运动命令通讯
TCmd_Mov*        cmd_movZ1;		//手动 Z1轴运动命令通讯
TCmd_Mov*        cmd_movY2;		//手动 Y2轴运动命令通讯
TCmd_Mov*        cmd_movZ2;		//手动 Z2轴运动命令通讯
TCmd_Mov*        cmd_movY;		//手动 Y轴运动命令通讯
TCmd_Mov*        cmd_movZ;		//手动 Z轴运动命令通讯
/*ROT,OVRTRN,BRC1,BRC2,BRC3,SCK1,SCK2,RES1,RES2,
        BLT,ERR,STK,AUX*/
TCmd_In*          cmd_In;		//手动 输入命令通讯
TCmd_Out*         cmd_Out;		//手动 输出命令通讯

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: tcmd.h

* 功能描述: 自定义示教命令头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef TCMD_H
#define TCMD_H
#include <QFile>
#include <QStandardItem>

#include "tcom.h"


//示教命令基类，存储每条命令的数据
class TCmd : public QStandardItem,public TCom
{
public:
    TCmd(const QString &fileName);
public:
    enum CMDID
    {
        /********************************
        动作编号对应
        10H：X轴运动
        11H：Y1轴运动
        12H：Z1轴运动
        13H：Y2轴运动
        14H：Z2轴运动
        15H：Y轴联动
        16H：Z轴联动


        17H~42H: 44路输入
        43H~75h: 50路输入备用

        76H~91H: 28路输出
        92H~C4H: 50路输出备用

        C5H: 堆叠
        *********************************/
        X1MOV = 0x10, Z1MOV,UMOV,X2MOV,Z2MOV,
        INPUT = 0x17, INPUTG = 0x20,
        OUTPUT = 0x76, OUTPUTG = 0x76 + 8, STACK = 0xC5
    };
    enum CLS_TYP
    {
        CLS_BSE,CLS_MOV,CLS_IO,CLS_STK,CLS_AUX
    };
    enum IO_TYP
    {
        SPECIAL,GENERAL
    };
    enum MOV_TYP
    {
        DIR,ROT
    };

#pragma pack(1)
    struct STR_PARA
    {
        quint8  action;     //动作编号
        quint32 dist;       //横行距离
        quint32 resdist;
        quint8  spd;        //横行速度
        quint16 wattim;     //动作延迟时间
        quint16 res1;       //备用
        quint8  combin;     //组合关系
        quint8  res2;       //备用
    };
#pragma pack()

public:
    CLS_TYP cls_typ;        //类的类型

    STR_PARA para;          //协议参数数据
public:
    virtual bool ConsPara(){}                   //获取UI参数
    virtual QString getCmdTit(){}               //获取命令说明文字
    virtual QStandardItem* ConsTitItem(){}      //生成命令说明文字Item
    virtual QStandardItem* ConsCombiItem();     //生成组合关系的Item
    virtual void OnCmdClk(){}                   //响应点击命令事件
    virtual void OnSave(QFile *file);           //保存文件
    virtual void OnOpen(QFile *file);           //计算命令的字节数
private:
    virtual QString Id2Til(CMDID Id);
};
class TCmd_Mov : public TCmd
{
public:
    TCmd_Mov();
public:
    bool ConsPara();                   //获取UI参数
    QString getCmdTit();               //获取命令说明文字
    QStandardItem* ConsTitItem();      //生成命令说明文字Item
    void OnCmdClk();                   //响应点击命令事件
    bool snd();                        //发送数据
    bool chk();                        //校验通讯
    //void OnSave(QString *strS);        //保存文件
    //int  CmdLen();                     //计算命令的字节数
    QString Id2Til(CMDID Id);

public:
    MOV_TYP mt;
};
class TCmd_In : public TCmd
{
public:
    TCmd_In();
public:
    bool ConsPara();                   //获取UI参数
    QString getCmdTit();               //获取命令说明文字
    QStandardItem* ConsTitItem();      //生成命令说明文字Item
    void OnCmdClk();                   //响应点击命令事件
    bool snd();                        //发送数据
    bool chk();                        //校验通讯
    //void OnSave(QString *strS);        //保存文件
    //int  CmdLen();                     //计算命令的字节数
    QString Id2Til(CMDID Id);

public:
    IO_TYP ioT;
};
class TCmd_Out : public TCmd
{
public:
    TCmd_Out();
public:
    bool ConsPara();                   //获取UI参数
    QString getCmdTit();               //获取命令说明文字
    QStandardItem* ConsTitItem();      //生成命令说明文字Item
    void OnCmdClk();                   //响应点击命令事件
    bool snd();                        //发送数据
    bool chk();                        //校验通讯
    //void OnSave(QString *strS);        //保存文件
    //int  CmdLen();                     //计算命令的字节数
    QString Id2Til(CMDID Id);
public:
    IO_TYP ioT;
};
class TCmd_Stk : public TCmd
{
public:
    TCmd_Stk();

#pragma pack(1)
    struct STK_PARA
    {
        quint8  action;     //动作编号
        quint8 name[8];     //堆叠程序名
        quint8  spd;        //横行速度
        quint16 wattim;     //动作延迟时间
        quint16 res1;       //备用
        quint8  combin;     //组合关系
        quint8  res2;       //备用
    };
#pragma pack()
public:
    bool ConsPara();                   //获取UI参数
    QString getCmdTit();               //获取命令说明文字
    QStandardItem* ConsTitItem();      //生成命令说明文字Item
    void OnCmdClk();                   //响应点击命令事件
    bool snd();                        //发送数据
    bool chk();                        //校验通讯
    //void OnSave(QString *strS);        //保存文件
    //int  CmdLen();                     //计算命令的字节数
    QString Id2Til(CMDID Id);
};



typedef TCmd*(*Create_Cmd)();
extern Create_Cmd create_cmd[];


extern      TCmd*            pCurCmd;
extern      int              iCurCmd;
extern      TCmd_Mov*        cmd_movX;        //手动 运动命令通讯
extern      TCmd_Mov*        cmd_movY1;
extern      TCmd_Mov*        cmd_movZ1;
extern      TCmd_Mov*        cmd_movY2;
extern      TCmd_Mov*        cmd_movZ2;
extern      TCmd_Mov*        cmd_movY;
extern      TCmd_Mov*        cmd_movZ;
extern      TCmd_Out*         cmd_Out;
extern      TCmd_In*          cmd_In;
#endif // TCMD_H

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: tcom.h

* 功能描述: 自定义通讯类头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef TCOM_H
#define TCOM_H
#include <QFile>
#include <QVector>
#include <QMutex>
#include <QMutexLocker>
#include <QStandardItemModel>
#include <QStandardItem>

#include "qa5driver.h"

//通讯基类，负责为通讯机制提供统一接口
class TCom
{
public:
    TCom();
    ~TCom(){}

    enum COM_ADD
    {
        COM01 = 0x01,
        COM02,
        COM03,
        COM04,
        COM05,
        COM06,
        COM07,
        COM08,

        COM20 = 0x20,
        COM70 = 0x70,
        COM7F = 0x7f,
        COME0 = 0xe0,

        COMF0 = 0xf0,
        COMF1,
        COMF2,
        COMF3
    };
    enum AXIS
    {
        X = 0x01,
        Y1,
        Z1,
        Y2,
        Z2
    };
public:
    virtual bool DoCom();               //执行通讯
protected:
    virtual bool snd();                 //发送数据
    virtual bool rcv();                 //接受数据
    virtual bool chk();                 //校验

    virtual bool UpdateUI(bool bSuc){}  //更新UI
    virtual bool SndFrame(CAN_Frame *frame);    //发送单条CAN帧

public:
    QVector <CAN_Frame> vecRcv;         //接收帧缓存
    quint8   com_add;                   //帧地址
    quint8   eptNum;                    //期望回复帧数量，0表示不需要校验帧数量
};

class TCom01 : public TCom
{
public:
    TCom01();
public:
#pragma pack(1)
    struct STR_PARA
    {
        quint8 ser[12];     //序列号
        quint8 ver[6];      //版本号
        quint16 year;       //年
        quint8 month;       //月
        quint8 day;         //日
        quint8 res[2];      //备用
        quint8 psw[6];      //密码
    };
#pragma pack()

public:
    STR_PARA para;
public:
    //bool UpdateUI(bool bSuc);
    bool snd();
    bool chk();
};

class TCom02 : public TCom
{
public:
    TCom02();
public:

    enum AXISP
    {
        DISABLE,ENABLE
    };

#pragma pack(1)
    struct STR_PARA
    {
        quint8  axis;       //电机轴
        quint32 absL;       //绝对长度
        quint8  whlvel;     //整体速度
        quint16  maxS;      //最大速度
        quint16  maxA;      //最大加速度
        quint8  manS;       //手动示教速度
        quint8  resS;       //复位速度
        quint8  errA;       //运行误差
        quint16 zro_off;    //零点偏移
        quint16  pls_equ;   //脉冲当量
        quint8  accp;       //加速度允许
        quint8  axisp;      //电机使能
        quint8  rspd;       //运行速度
        quint16 prdw;       //周波数
        quint8  mtrD;       //电机方向
        quint8  gears;      //手动档位
        quint16  jog_d_t;   //点动减速时间
        quint8  axisT;      //轴类型 0x01旋转
        quint8  rev[3];     //保留
    };
#pragma pack()

public:
    STR_PARA para[5];
public:
    //bool UpdateUI(bool bSuc);
    bool snd();
    bool chk();
};
class TCom03 : public TCom
{
public:
    TCom03();
public:

    enum WAITTYP
    {
        WAITH,WAITE
    };

#pragma pack(1)
    struct STR_PARA
    {
        quint8 wattyp;  //待机方式
        quint8 watpos;  //待机位置
        quint8 rstpos;  //复位位置
        quint8 sfedor;  //安全门
        quint8 res[2];  //备用
    };
#pragma pack()

public:
    STR_PARA para;
public:
    //bool UpdateUI(bool bSuc);
    bool snd();
    bool chk();
};
class TCom04 : public TCom
{
public:
    TCom04();
public:

    enum CHKA
    {
        ENABLE,DISABLE
    };

#pragma pack(1)
    struct STR_PARA
    {
        quint8 mainS;   //主臂吸检测
        quint8 mainE;   //主臂抱检测
        quint8 Sic;     //剪刀检测
        quint8 rechk;   //备用检测
        quint8 res[2];  //备用
    };
#pragma pack()

public:
    STR_PARA para;
public:
    //bool UpdateUI(bool bSuc);
    bool snd();
    bool chk();
};
class TCom05 : public TCom
{
public:
    TCom05();
public:
#pragma pack(1)
    struct STR_PARA
    {
        quint32 pln_prd;    //计划产量
        quint32 bad_prd;    //不良产品
        quint32 cir_tim;    //循环超时
        quint32 rst_tim;    //复位超时
        quint8  spr_val;    //喷雾间隔
        quint8  res;        //备用
    };
#pragma pack()

public:
    STR_PARA para;
public:
    //bool UpdateUI(bool bSuc);
    bool snd();
    bool chk();
};
class TCom06 : public TCom
{
public:
    TCom06();
public:
    enum ORDER{
        X = 0x01,Y,Z
    };
    enum DIR{
        FORWARD = 0x01,BACKWARD
    };

#pragma pack(1)
    struct STR_PARA
    {
        quint32 entP[2]; //进入点坐标
        quint32 stkP[2]; //堆叠起点坐标
        quint8  spd[2];  //X、Y、Z轴的速度
        quint8  odr[2];  //第一、二、三顺序
        struct{
            quint8  dir; //方向
            quint16 num; //数量
            quint16 dis; //间距
        }opt[2];         // X、Y、Z的方向、数量、间距
    };
#pragma pack()

public:
    STR_PARA para;
public:
    //bool UpdateUI(bool bSuc);
    bool snd();
    bool chk();
};
class TCom07 : public TCom
{
public:
    TCom07();
public:
#pragma pack(1)
    struct STR_PARA
    {
        quint8 spd[5];      //复位速度
        quint8 axis[5];     //复位轴序号
    };
#pragma pack()

public:
    STR_PARA para;
public:
    //bool UpdateUI(bool bSuc);
    bool snd();
    bool chk();
};
class TCom08 : public TCom
{
public:
    TCom08();
public:
#pragma pack(1)
    struct STR_PARA
    {
        quint8 dir[5];      //电机方向
    };
#pragma pack()

public:
    STR_PARA para;
public:
    //bool UpdateUI(bool bSuc);
    bool snd();
    bool chk();
};


class TCom20 : public TCom
{
public:
    TCom20();
public:
#pragma pack(1)
    struct PGM_HEAD
    {
        quint32 cmdL;                  //程序行
    };
#pragma pack()
public:
    bool    bNewForSnd;                //文件更新了，需要发送给下位机
    bool    bOpen;                     //文件打开
    QStandardItemModel *modelPro;      //程序model
    //TCom06  comStk;                    //堆叠数据
private:
    quint8  iSndN;                     //发送的帧数
public:
    void    AddCmd(int rIndex);        //添加命令行
    void    DelCmd(int rIndex);        //删除命令行
    void    SetItem(int row,int column,QStandardItem* item);    //更新命令item

    void    NewPgm();                  //创建新程序
    void    SavePgm(QFile *file);      //保存程序文件
    void    OpenPgm(QFile *file);      //打开程序文件
    void    plsTran();
    void    RplsTran();
public:
    bool UpdateUI(bool bSuc);
    bool snd();
    bool chk();
};


class TCom70 : public TCom
{
public:
    TCom70();
public:
#pragma pack(1)
    struct STR_PARA
    {
        quint8  stkp;            //堆叠方式
        quint8  interval[10];    //左右间隔
        quint16 height;          //高度
        quint8  num;             //数量
    };
#pragma pack()

public:
    STR_PARA para;
public:
    //bool UpdateUI(bool bSuc);
    bool snd();
    bool chk();
};
class TComE0 : public TCom
{
public:
    TComE0();
public:
#pragma pack(1)
    struct STR_PARA
    {
        quint8  runtype;    //运行模式，
        union {
            quint16 adr;
            struct {
                quint8 jogT;//点动类型
                quint8 jogA;//点动轴
            };
        };                  //运行地址或点动
        quint8  cond1;      //运行条件1
        quint8  cond2;      //运行条件2
        quint8  res;        //保留
    };
#pragma pack()
    enum RUN_TYPE
    {
        SGL_STP = 0x01,SGL_CYCLE,AUTO,PAUSE,STOP,EMERGENCY,REST,JOG
    };
    enum JOGT
    {
        JOG_ADD = 0x01,JOG_SUB,JOG_STP
    };

public:
    STR_PARA para;
public:
    //bool UpdateUI(bool bSuc);
    bool snd();
    bool chk();
};
class TComF0 : public TCom
{
public:
    TComF0();
public:
    enum MODE{
        STP_NO_RST,STEP,SGL_CLE,AUTO,SUSPEND,STOP,EMERGENCY,RESTTING,JOG,MANUAL,IDLE = 0xff
    };

#pragma pack(1)
    struct STR_PARA_S
    {
        quint8  dat[6];
    };
    struct STR_PARA_R
    {
       quint8   out[5];        //输出状态
       quint8   in[6];         //输入状态
       quint32  xpos;          //X轴位置
       quint32  y1pos;         //Y1轴位置
       quint32  z1pos;         //Z1轴位置
       quint32  y2pos;         //Y2轴位置
       quint32  z2pos;         //Z2轴位置
       quint16  radd;          //指令运行地址
       quint8   sta;           //电机状态
       quint8   sub_sta;       //下位控制器状态
       quint8   res;           //保留
       quint8   seroEn;        //伺服使能
       quint8   clrErr;        //错误清除
       quint8   serErr;        //伺服报警信号
       quint8   serRdy;        //伺服就绪信号
       quint8   serZSig;       //伺服编码器Z信号
       quint8   keyStu;        //按键状态
    };
#pragma pack()

public:
    STR_PARA_S spara;
    STR_PARA_R rpara;
public:
    bool UpdateUI(bool bSuc);
    bool snd();
    void UpdateLht();
    QString datToSta(quint8 dat);   //下位机状态转换成文字
private:
    QVector<QString>    str_sub_sta;
};
class TComF1 : public TCom
{
public:
    TComF1();
public:
#pragma pack(1)
    struct STR_PARA
    {
        quint8  dat[6];
    };
#pragma pack()
public:
    STR_PARA para;
public:
    bool UpdateUI(bool bSuc);
    bool snd();
    //bool chk();
};
class TComF2 : public TCom
{
public:
    TComF2();
public:
#pragma pack(1)
    struct STR_PARA
    {
        quint8  dat[6];
    };
#pragma pack()
public:
    STR_PARA para;
public:
    bool UpdateUI(bool bSuc);
    bool snd();
    //bool chk();
};
class TComF3 : public TCom
{
public:
    TComF3();
public:
#pragma pack(1)
    struct STR_PARA
    {
        quint8  dat[6];
    };
#pragma pack()
public:
    STR_PARA para;
public:
    bool UpdateUI(bool bSuc);
    bool snd();
    //bool chk();
private:
    void AnaCmd();
};

extern  TCom01  com01;
extern  TCom02  com02;       //伺服配置
extern  TCom03  com03;       //配置待机方式等
extern  TCom04  com04;       //配置检测允许
extern  TCom05  com05;       //配置产品
extern  TCom06  com06,comStk;//配置堆叠
extern  TCom07  com07;       //复位配置
extern  TCom08  com08;       //电机方向配置
extern  TCom20  com20;       //示教程序
extern  TCom70  com70;       //堆叠指令
extern  TComF0  comF0;       //查询命令
extern  TComF1  comF1;       //读取伺服参数
extern  TComF2  comF2;       //读取复位数据
extern  TComF3  comF3;       //读取示教程序
extern  TComE0  comE0;       //运行方式指令

extern  QMutex mutex_com;
extern  QVector<TCom*> pComBuf1;
extern  QVector<TCom*> pComBuf2;
#endif // TCOM_H

//==========================================================================================
// End of file.
//==========================================================================================

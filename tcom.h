/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: tcom.h

* ��������: �Զ���ͨѶ��ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
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

//ͨѶ���࣬����ΪͨѶ�����ṩͳһ�ӿ�
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
    virtual bool DoCom();               //ִ��ͨѶ
protected:
    virtual bool snd();                 //��������
    virtual bool rcv();                 //��������
    virtual bool chk();                 //У��

    virtual bool UpdateUI(bool bSuc){}  //����UI
    virtual bool SndFrame(CAN_Frame *frame);    //���͵���CAN֡

public:
    QVector <CAN_Frame> vecRcv;         //����֡����
    quint8   com_add;                   //֡��ַ
    quint8   eptNum;                    //�����ظ�֡������0��ʾ����ҪУ��֡����
};

class TCom01 : public TCom
{
public:
    TCom01();
public:
#pragma pack(1)
    struct STR_PARA
    {
        quint8 ser[12];     //���к�
        quint8 ver[6];      //�汾��
        quint16 year;       //��
        quint8 month;       //��
        quint8 day;         //��
        quint8 res[2];      //����
        quint8 psw[6];      //����
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
        quint8  axis;       //�����
        quint32 absL;       //���Գ���
        quint8  whlvel;     //�����ٶ�
        quint16  maxS;      //����ٶ�
        quint16  maxA;      //�����ٶ�
        quint8  manS;       //�ֶ�ʾ���ٶ�
        quint8  resS;       //��λ�ٶ�
        quint8  errA;       //�������
        quint16 zro_off;    //���ƫ��
        quint16  pls_equ;   //���嵱��
        quint8  accp;       //���ٶ�����
        quint8  axisp;      //���ʹ��
        quint8  rspd;       //�����ٶ�
        quint16 prdw;       //�ܲ���
        quint8  mtrD;       //�������
        quint8  gears;      //�ֶ���λ
        quint16  jog_d_t;   //�㶯����ʱ��
        quint8  axisT;      //������ 0x01��ת
        quint8  rev[3];     //����
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
        quint8 wattyp;  //������ʽ
        quint8 watpos;  //����λ��
        quint8 rstpos;  //��λλ��
        quint8 sfedor;  //��ȫ��
        quint8 res[2];  //����
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
        quint8 mainS;   //���������
        quint8 mainE;   //���۱����
        quint8 Sic;     //�������
        quint8 rechk;   //���ü��
        quint8 res[2];  //����
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
        quint32 pln_prd;    //�ƻ�����
        quint32 bad_prd;    //������Ʒ
        quint32 cir_tim;    //ѭ����ʱ
        quint32 rst_tim;    //��λ��ʱ
        quint8  spr_val;    //������
        quint8  res;        //����
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
        quint32 entP[2]; //���������
        quint32 stkP[2]; //�ѵ��������
        quint8  spd[2];  //X��Y��Z����ٶ�
        quint8  odr[2];  //��һ��������˳��
        struct{
            quint8  dir; //����
            quint16 num; //����
            quint16 dis; //���
        }opt[2];         // X��Y��Z�ķ������������
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
        quint8 spd[5];      //��λ�ٶ�
        quint8 axis[5];     //��λ�����
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
        quint8 dir[5];      //�������
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
        quint32 cmdL;                  //������
    };
#pragma pack()
public:
    bool    bNewForSnd;                //�ļ������ˣ���Ҫ���͸���λ��
    bool    bOpen;                     //�ļ���
    QStandardItemModel *modelPro;      //����model
    //TCom06  comStk;                    //�ѵ�����
private:
    quint8  iSndN;                     //���͵�֡��
public:
    void    AddCmd(int rIndex);        //���������
    void    DelCmd(int rIndex);        //ɾ��������
    void    SetItem(int row,int column,QStandardItem* item);    //��������item

    void    NewPgm();                  //�����³���
    void    SavePgm(QFile *file);      //��������ļ�
    void    OpenPgm(QFile *file);      //�򿪳����ļ�
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
        quint8  stkp;            //�ѵ���ʽ
        quint8  interval[10];    //���Ҽ��
        quint16 height;          //�߶�
        quint8  num;             //����
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
        quint8  runtype;    //����ģʽ��
        union {
            quint16 adr;
            struct {
                quint8 jogT;//�㶯����
                quint8 jogA;//�㶯��
            };
        };                  //���е�ַ��㶯
        quint8  cond1;      //��������1
        quint8  cond2;      //��������2
        quint8  res;        //����
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
       quint8   out[5];        //���״̬
       quint8   in[6];         //����״̬
       quint32  xpos;          //X��λ��
       quint32  y1pos;         //Y1��λ��
       quint32  z1pos;         //Z1��λ��
       quint32  y2pos;         //Y2��λ��
       quint32  z2pos;         //Z2��λ��
       quint16  radd;          //ָ�����е�ַ
       quint8   sta;           //���״̬
       quint8   sub_sta;       //��λ������״̬
       quint8   res;           //����
       quint8   seroEn;        //�ŷ�ʹ��
       quint8   clrErr;        //�������
       quint8   serErr;        //�ŷ������ź�
       quint8   serRdy;        //�ŷ������ź�
       quint8   serZSig;       //�ŷ�������Z�ź�
       quint8   keyStu;        //����״̬
    };
#pragma pack()

public:
    STR_PARA_S spara;
    STR_PARA_R rpara;
public:
    bool UpdateUI(bool bSuc);
    bool snd();
    void UpdateLht();
    QString datToSta(quint8 dat);   //��λ��״̬ת��������
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
extern  TCom02  com02;       //�ŷ�����
extern  TCom03  com03;       //���ô�����ʽ��
extern  TCom04  com04;       //���ü������
extern  TCom05  com05;       //���ò�Ʒ
extern  TCom06  com06,comStk;//���öѵ�
extern  TCom07  com07;       //��λ����
extern  TCom08  com08;       //�����������
extern  TCom20  com20;       //ʾ�̳���
extern  TCom70  com70;       //�ѵ�ָ��
extern  TComF0  comF0;       //��ѯ����
extern  TComF1  comF1;       //��ȡ�ŷ�����
extern  TComF2  comF2;       //��ȡ��λ����
extern  TComF3  comF3;       //��ȡʾ�̳���
extern  TComE0  comE0;       //���з�ʽָ��

extern  QMutex mutex_com;
extern  QVector<TCom*> pComBuf1;
extern  QVector<TCom*> pComBuf2;
#endif // TCOM_H

//==========================================================================================
// End of file.
//==========================================================================================

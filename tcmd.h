/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: tcmd.h

* ��������: �Զ���ʾ������ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef TCMD_H
#define TCMD_H
#include <QFile>
#include <QStandardItem>

#include "tcom.h"


//ʾ��������࣬�洢ÿ�����������
class TCmd : public QStandardItem,public TCom
{
public:
    TCmd(const QString &fileName);
public:
    enum CMDID
    {
        /********************************
        ������Ŷ�Ӧ
        10H��X���˶�
        11H��Y1���˶�
        12H��Z1���˶�
        13H��Y2���˶�
        14H��Z2���˶�
        15H��Y������
        16H��Z������


        17H~42H: 44·����
        43H~75h: 50·���뱸��

        76H~91H: 28·���
        92H~C4H: 50·�������

        C5H: �ѵ�
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
        quint8  action;     //�������
        quint32 dist;       //���о���
        quint32 resdist;
        quint8  spd;        //�����ٶ�
        quint16 wattim;     //�����ӳ�ʱ��
        quint16 res1;       //����
        quint8  combin;     //��Ϲ�ϵ
        quint8  res2;       //����
    };
#pragma pack()

public:
    CLS_TYP cls_typ;        //�������

    STR_PARA para;          //Э���������
public:
    virtual bool ConsPara(){}                   //��ȡUI����
    virtual QString getCmdTit(){}               //��ȡ����˵������
    virtual QStandardItem* ConsTitItem(){}      //��������˵������Item
    virtual QStandardItem* ConsCombiItem();     //������Ϲ�ϵ��Item
    virtual void OnCmdClk(){}                   //��Ӧ��������¼�
    virtual void OnSave(QFile *file);           //�����ļ�
    virtual void OnOpen(QFile *file);           //����������ֽ���
private:
    virtual QString Id2Til(CMDID Id);
};
class TCmd_Mov : public TCmd
{
public:
    TCmd_Mov();
public:
    bool ConsPara();                   //��ȡUI����
    QString getCmdTit();               //��ȡ����˵������
    QStandardItem* ConsTitItem();      //��������˵������Item
    void OnCmdClk();                   //��Ӧ��������¼�
    bool snd();                        //��������
    bool chk();                        //У��ͨѶ
    //void OnSave(QString *strS);        //�����ļ�
    //int  CmdLen();                     //����������ֽ���
    QString Id2Til(CMDID Id);

public:
    MOV_TYP mt;
};
class TCmd_In : public TCmd
{
public:
    TCmd_In();
public:
    bool ConsPara();                   //��ȡUI����
    QString getCmdTit();               //��ȡ����˵������
    QStandardItem* ConsTitItem();      //��������˵������Item
    void OnCmdClk();                   //��Ӧ��������¼�
    bool snd();                        //��������
    bool chk();                        //У��ͨѶ
    //void OnSave(QString *strS);        //�����ļ�
    //int  CmdLen();                     //����������ֽ���
    QString Id2Til(CMDID Id);

public:
    IO_TYP ioT;
};
class TCmd_Out : public TCmd
{
public:
    TCmd_Out();
public:
    bool ConsPara();                   //��ȡUI����
    QString getCmdTit();               //��ȡ����˵������
    QStandardItem* ConsTitItem();      //��������˵������Item
    void OnCmdClk();                   //��Ӧ��������¼�
    bool snd();                        //��������
    bool chk();                        //У��ͨѶ
    //void OnSave(QString *strS);        //�����ļ�
    //int  CmdLen();                     //����������ֽ���
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
        quint8  action;     //�������
        quint8 name[8];     //�ѵ�������
        quint8  spd;        //�����ٶ�
        quint16 wattim;     //�����ӳ�ʱ��
        quint16 res1;       //����
        quint8  combin;     //��Ϲ�ϵ
        quint8  res2;       //����
    };
#pragma pack()
public:
    bool ConsPara();                   //��ȡUI����
    QString getCmdTit();               //��ȡ����˵������
    QStandardItem* ConsTitItem();      //��������˵������Item
    void OnCmdClk();                   //��Ӧ��������¼�
    bool snd();                        //��������
    bool chk();                        //У��ͨѶ
    //void OnSave(QString *strS);        //�����ļ�
    //int  CmdLen();                     //����������ֽ���
    QString Id2Til(CMDID Id);
};



typedef TCmd*(*Create_Cmd)();
extern Create_Cmd create_cmd[];


extern      TCmd*            pCurCmd;
extern      int              iCurCmd;
extern      TCmd_Mov*        cmd_movX;        //�ֶ� �˶�����ͨѶ
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

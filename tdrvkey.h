/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: tdrvkey.h

* ��������: ����ɨ���߳�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef TDRVKEY_H
#define TDRVKEY_H

#include <QObject>
#include <QThread>

class TDrvKey : public QThread
{
    Q_OBJECT
public:
    TDrvKey(QObject *parent = 0);
public:
    enum DRVTYP
    {
        KEY0,KEY1,KEY2,KEY3,KEY4,KEY5,KEY6,KEY7,KEY8,KEY9,KEY10,
        KEY11,KEY12,KEY13,KEY14,KEY15,TRI_KEY,QDEC_KEY
    };
    enum DRVLEV
    {
        DOWN,UP
    };

    union MSG{
        quint32 msg;
        struct{
         quint16 msgT;
         quint16 msgL;
        };
    };

public:
    virtual   void  run();
private:
    void emitMsg(DRVTYP dt,DRVLEV dl);

signals:
    void sigKey(int dt);

public slots:

};

extern  TDrvKey drv_key;

#endif // TDRVKEY_H

//==========================================================================================
// End of file.
//==========================================================================================

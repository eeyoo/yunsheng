/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: twarn.h

* ��������: ����������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef TWARN_H
#define TWARN_H

#include <QFile>
#include <QVector>
#include <QDateTime>

class TWarn
{
public:
    TWarn();

public:
    struct WrnMsg
    {
        quint32 wrnN;
        QString strM;
        QDateTime dt;
    };
    enum WRNTYPE
    {
        W_FILES,W_COM,W_SAVE,W_ICHK,W_OCHK,W_STK_SVE,
        W_USR_AUTH,W_PSW_INPUT,W_PSW_ERR,W_PSW_MERR1,
        W_PSW_MERR2,W_MODE_CHANGE,W_NEWPRG,W_NEWPRG_S
    };

public:
    void ShowW2L(WRNTYPE warnN = W_FILES);
    void ClearW();

public:
    QVector<WrnMsg> wrnM;       //�����¼
    QVector<WrnMsg> wrnH;       //��ʷ�����¼
private:
    int iMsgT;
};

extern  TWarn   warn;       //������Ϣ�����

#endif // TWARN_H

//==========================================================================================
// End of file.
//==========================================================================================

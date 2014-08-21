/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: treadcmd.h

* ��������: ��ȡXML�����ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef TREADCMD_H
#define TREADCMD_H

#include <QVector>
#include <QString>

class TReadCmd
{
public:
    TReadCmd();


    struct CmdTil
    {
        quint8  cmdId;
        QString cmdTil;
    };
public:
    bool ReadCmd();

public:
    QVector<CmdTil> CmdM;
    QVector<CmdTil> CmdI;
    QVector<CmdTil> CmdO;
    QVector<CmdTil> CmdS;
};

extern  TReadCmd    readCmd;

#endif // TREADCMD_H

//==========================================================================================
// End of file.
//==========================================================================================

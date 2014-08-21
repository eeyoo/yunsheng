/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: treadcmd.h

* 功能描述: 读取XML配置文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
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

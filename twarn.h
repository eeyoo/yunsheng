/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: twarn.h

* 功能描述: 报警管理类

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
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
    QVector<WrnMsg> wrnM;       //警告记录
    QVector<WrnMsg> wrnH;       //历史警告记录
private:
    int iMsgT;
};

extern  TWarn   warn;       //警告消息类变量

#endif // TWARN_H

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: tdrvkey.h

* 功能描述: 按键扫描线程

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
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

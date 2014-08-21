/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: tdrvqdec.h

* 功能描述: 扫描旋转编码器

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#ifndef TDRVQDEC_H
#define TDRVQDEC_H

#include <QThread>

class TDrvQdec : public QThread
{
    Q_OBJECT
public:
    explicit TDrvQdec(QObject *parent = 0);

    enum DRVLEV
    {
        UP,DOWN
    };

public:
    virtual   void  run();
signals:
    void sigQdec(int value);
public slots:
private:
    bool m_bPD5,m_bPD6;

};

extern  TDrvQdec drv_qdec;

#endif // TDRVQDEC_H

//==========================================================================================
// End of file.
//==========================================================================================

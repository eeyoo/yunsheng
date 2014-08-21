/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: tdrvqdec.h

* ��������: ɨ����ת������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
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

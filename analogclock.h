/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: analogclock.h

* ��������: �Զ����ӱ�ؼ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>

class AnalogClock : public QWidget
{
    Q_OBJECT
public:
    explicit AnalogClock(QWidget *parent = 0);

signals:

public slots:
protected:
    void paintEvent(QPaintEvent *);

};

#endif // ANALOGCLOCK_H

//==========================================================================================
// End of file.
//==========================================================================================

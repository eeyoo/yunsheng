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

#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

class Dashboard : public QWidget
{
    Q_OBJECT
public:
    explicit Dashboard(QWidget *parent = 0);

signals:

public slots:
    void setHand(QString value);

protected:
    void paintEvent(QPaintEvent *);
    double mVal;

};

#endif // DASHBOARD_H

//==========================================================================================
// End of file.
//==========================================================================================

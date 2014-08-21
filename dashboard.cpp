/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: analogclock.cpp

* ��������: �Զ����ӱ�ؼ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/


#include <QtGui>

#include "dashboard.h"

/*************************************************************************
* ��������: Dashboard
* ��   ��: ���캯��
* �������: parent ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dashboard::Dashboard(QWidget *parent) :
    QWidget(parent)
{
    mVal = -120.0;
    resize(200,200);
    /*
    QPixmap pixmap(":/Res/image/tclock.png");
    QPalette palette;
    palette.setBrush(backgroundRole(),QBrush(pixmap.scaled(QSize(200,200),\
                                      Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    setPalette(palette);
    //setMask(pixmap.mask());
    setAutoFillBackground(true);
    */

}
/*************************************************************************
* ��������: paintEvent
* ��   ��: �ػ�
* �������: QPaintEvent *event �ػ��¼�
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dashboard::paintEvent(QPaintEvent */*event*/)
{

    static const QPoint hand[4] = {
        QPoint(8,0),
        QPoint(0,-50),
        QPoint(-8,0),
        QPoint(0,10)
    };

    QColor handColor(255,255,255);

    int side = qMin(width(), height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPoint widgetCenter(width()/2, height()/2);
    painter.translate(widgetCenter);
    painter.scale(side / 200.0, side / 200.0);


    // draw hour hand
    painter.setPen(Qt::NoPen);
    painter.setBrush(handColor);

    painter.save();
    painter.drawPixmap(-100,-100, 200, 200, QPixmap(":/Res/image/dashboard.png"));
    painter.rotate(mVal);
    painter.drawConvexPolygon(hand, 4);
    painter.restore();

}
/*************************************************************************
* ��������: setHand
* ��   ��: ����ָ��
* �������: value ָ��ֵ
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dashboard::setHand(QString value)
{
    //value.chop(1);
    mVal = value.toDouble() * 2.4 - 120;
    update();
}

//==========================================================================================
// End of file.
//==========================================================================================

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
//#include <QDebug>

#include "analogclock.h"

/*************************************************************************
* ��������: AnalogClock
* ��   ��: ���캯��
* �������: QWidget *parent ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
AnalogClock::AnalogClock(QWidget *parent) :
    QWidget(parent)
{
    /*
    QPixmap pixmap(":/images/tclock.png");
    QPalette palette;
    palette.setBrush(backgroundRole(),QBrush(pixmap.scaled(QSize(300,300),\
                                          Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    setPalette(palette);
    //setMask(pixmap.mask());
    setAutoFillBackground(true);
    */
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    timer->start(1000); // Timeout interval is 1s

    //setWindowTitle("Analog Clock");
    resize(200,200);
}
/*************************************************************************
* ��������: paintEvent
* ��   ��: �ػ�
* �������: QPaintEvent *event �ػ��¼�
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void AnalogClock::paintEvent(QPaintEvent */*event*/)
{
    //QPixmap hourPixmap(":/images/hour_needle.png");
    //QPixmap minutePixmap(":/images/minute_needle.png");
    //QPixmap secondPixmap(":/images/second_needle1.png");

    static const QPoint hourHand[4] = {
        QPoint(2,8),
        QPoint(-2,8),
        QPoint(-2,-40),
        QPoint(2,-40)
    };
    static const QPoint minuteHand[4] = {
        QPoint(2,8),
        QPoint(-2,8),
        QPoint(-2,-60),
        QPoint(2,-60)
    };
    static const QPoint secondHand[4] = {
        QPoint(1,10),
        QPoint(-1,10),
        QPoint(-1,-70),
        QPoint(1,-70)
    };

    QColor hourColor(255,255,255);
    QColor minuteColor(255,255,255);
    QColor secondColor(39, 115, 180);
    QColor markColor(255,255,255);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPoint widgetCenter(width()/2, height()/2);
    painter.translate(widgetCenter);
    painter.scale(side / 200.0, side / 200.0);

    // draw hour hand
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 4);
    painter.restore();


    // draw minute hand
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * ((time.minute() + time.second() / 60.0)));
    painter.drawConvexPolygon(minuteHand, 4);
    painter.restore();

    // draw second hand
    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);

    painter.save();
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(secondHand, 4);
    painter.restore();

    // draw hour mark lines
    painter.setPen(markColor);

    for (int i=0; i<12; ++i) {
        //painter.drawLine(88, 0, 96, 0);
        painter.drawLine(75, 0, 84, 0);
        painter.rotate(30.0);
    }

    // draw minute marks
    //painter.setPen(minuteColor);
    for (int j=0; j<60; ++j) {
        if ((j%5) != 0)
            //painter.drawLine(92, 0, 96, 0);
            painter.drawLine(80, 0, 84, 0);
        painter.rotate(6.0);
    }

    /*
    // draw outline
    painter.setPen(QPen(Qt::white, 2));
    painter.setBrush(Qt::NoBrush);
    painter.save();
    painter.drawEllipse(-100,-100,200,200);
    painter.restore();
    */

    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);
    painter.save();
    painter.drawEllipse(-5,-5,10,10);
    painter.restore();
    //qDebug() << QString::number(time.second());
}

//==========================================================================================
// End of file.
//==========================================================================================

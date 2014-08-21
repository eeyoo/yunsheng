/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: analogclock.cpp

* 功能描述: 自定义钟表控件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/


#include <QtGui>

#include "dashboard.h"

/*************************************************************************
* 函数名称: Dashboard
* 功   能: 构造函数
* 输入参数: parent 父类句柄
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: paintEvent
* 功   能: 重绘
* 输入参数: QPaintEvent *event 重绘事件
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: setHand
* 功   能: 设置指针
* 输入参数: value 指针值
* 输出参数: 无
* 返 回 值: 无
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

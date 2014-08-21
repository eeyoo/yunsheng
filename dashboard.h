/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: analogclock.h

* 功能描述: 自定义钟表控件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
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

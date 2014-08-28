/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: ttblviewf.h

* 功能描述: 自定义QTableView类

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.8.23

* 修	改:
**************************************************************************************/

#ifndef TTBLVIEWF_H
#define TTBLVIEWF_H

#include <QTableView>

class TTblViewF : public QTableView
{
    Q_OBJECT
public:
    explicit TTblViewF(QWidget *parent = 0);

signals:

public slots:
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

};

#endif // TTBLVIEWF_H


//==========================================================================================
// End of file.
//==========================================================================================

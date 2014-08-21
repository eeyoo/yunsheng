/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: tlineedit.h

* 功能描述: 自定义QLineEdit类头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef TLineEdit_H
#define TLineEdit_H
 
#include <QLineEdit>
#include <QMouseEvent>
 
class TLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit TLineEdit(QWidget *parent = 0);
protected:
    //重写mousePressEvent事件
    virtual void mousePressEvent(QMouseEvent *event);
public:
    int iMark;
signals:
    //自定义clicked()信号,在mousePressEvent事件发生时触发
    void clicked();
 
public slots:
 
};
 
#endif // TLineEdit_H

//==========================================================================================
// End of file.
//==========================================================================================

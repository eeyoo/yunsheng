/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: tlineedit.cpp

* 功能描述: 自定义QLineEdit控件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#include "tlineedit.h"

/*************************************************************************
* 函数名称: TLineEdit
* 功   能: 构造函数
* 输入参数: parent 根类句柄
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TLineEdit::TLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}
 
//重写mousePressEvent事件,检测事件类型是不是点击了鼠标左键
void TLineEdit::mousePressEvent(QMouseEvent *event) {
    //如果单击了就触发clicked信号
    if (event->button() == Qt::LeftButton) {
        //触发clicked信号
        emit clicked();
    }
    //将该事件传给父类处理
    QLineEdit::mousePressEvent(event);
}

//==========================================================================================
// End of file.
//==========================================================================================

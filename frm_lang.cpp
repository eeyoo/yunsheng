/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_lang.cpp

* 功能描述: 语言选择文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/


#include "frm_lang.h"
#include "ui_frm_lang.h"
/*************************************************************************
* 函数名称: Frm_Lang
* 功    能: 构造函数
* 输入参数: 
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_Lang::Frm_Lang() :
    
    ui(new Ui::Frm_Lang)
{
    ui->setupUi(this);
    //setAutoFillBackground(true);
}
/*************************************************************************
* 函数名称: ~Frm_Lang
* 功    能: 析构函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_Lang::~Frm_Lang()
{
    delete ui;
}

//==========================================================================================
// End of file.
//==========================================================================================

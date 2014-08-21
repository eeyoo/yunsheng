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

#ifndef FRM_PROM_H
#define FRM_PROM_H

#include "twidget.h"

namespace Ui {
    class Frm_ProM;
}

class Frm_ProM : public TWidget
{
    Q_OBJECT

public:
    Frm_ProM();
    ~Frm_ProM();

private:
    Ui::Frm_ProM *ui;

private:
    void SearchFile();
    bool OnOpen();
private slots:
    void on_btnEx_clicked();
    void on_btnIm_clicked();
    void on_btnDel_clicked();
    void on_btnSveA_clicked();
    void on_btnRen_clicked();
    void on_btnEdit_clicked();
    void on_btnOpen_clicked();
    void on_btnNew_clicked();
    void setVisible(bool visible);
};

#endif // FRM_PROM_H

//==========================================================================================
// End of file.
//==========================================================================================

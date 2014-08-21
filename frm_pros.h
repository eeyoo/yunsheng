/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_pros.h

* 功能描述: 产品设置头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef FRM_PROS_H
#define FRM_PROS_H

#include "twidget.h"

namespace Ui {
class Frm_ProS;
}

class Frm_ProS : public TWidget
{
    Q_OBJECT

public:
    Frm_ProS();
    ~Frm_ProS();

public:
    Ui::Frm_ProS *ui;
private slots:
    void on_lePlnPrd_clicked();
    void on_leBadPrd_clicked();
    void on_leCirTim_clicked();
    void on_leRstTim_clicked();
    void on_leSprVal_clicked();
};

#endif // FRM_PROS_H

//==========================================================================================
// End of file.
//==========================================================================================

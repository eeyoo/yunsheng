/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_manufacturer.h

* 功能描述: 厂家设置画面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#ifndef FRM_MANUFACTURER_H
#define FRM_MANUFACTURER_H

#include "twidget.h"

namespace Ui {
class Frm_Manufacturer;
}

class Frm_Manufacturer : public TWidget
{
    Q_OBJECT

public:
    Frm_Manufacturer();
    ~Frm_Manufacturer();


private slots:
    void on_btnUpd_clicked();
    void on_btnRelad_clicked();
    void on_btnReboot_clicked();

    void on_btnRecov_clicked();

private:
    Ui::Frm_Manufacturer *ui;
};

#endif // FRM_MANUFACTURER_H

//==========================================================================================
// End of file.
//==========================================================================================

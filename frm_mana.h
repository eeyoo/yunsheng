/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_mana.h

* 功能描述: 运行模式选择头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef FRM_MANA_H
#define FRM_MANA_H

#include "twidget.h"
#include <QSignalMapper>

namespace Ui {
    class Frm_Mana;
}

class Frm_Mana : public TWidget
{
    Q_OBJECT

public:
    Frm_Mana();
    ~Frm_Mana();

private:
    QSignalMapper  sglMapRb;
    QSignalMapper  sglMapCb;
private:
    void InitRbSig();
    void InitCbSig();
private slots:
    void on_rb_clicked(int irb);
    void on_cb_clicked(int icb);
private:
    Ui::Frm_Mana *ui;
};

#endif // FRM_MANA_H

//==========================================================================================
// End of file.
//==========================================================================================

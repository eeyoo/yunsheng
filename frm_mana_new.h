/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_mana_new.h

* 功能描述: 手动画面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#ifndef FRM_MANA_NEW_H
#define FRM_MANA_NEW_H

#include "twidget.h"

namespace Ui {
class Frm_Mana_New;
}

class Frm_Mana_New : public TWidget
{
    Q_OBJECT

public:
    Frm_Mana_New();
    ~Frm_Mana_New();

private:
    Ui::Frm_Mana_New *ui;
};

#endif // FRM_MANA_NEW_H

//==========================================================================================
// End of file.
//==========================================================================================

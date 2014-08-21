/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_view.h

* 功能描述: 系统查询头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef FRM_VIEW_H
#define FRM_VIEW_H

#include "twidget.h"

namespace Ui {
    class Frm_View;
}

class Frm_View : public TWidget
{
    Q_OBJECT

public:
    Frm_View();
    ~Frm_View();

public slots:
    void setVisible(bool visible);
private:
    Ui::Frm_View *ui;
};

#endif // FRM_VIEW_H

//==========================================================================================
// End of file.
//==========================================================================================

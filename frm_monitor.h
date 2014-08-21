/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: Frm_Monitor.h

* 功能描述: 监视画面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#ifndef FRM_MONITOR_H
#define FRM_MONITOR_H

#include "twidget.h"
#include <QSignalMapper>

namespace Ui {
class Frm_Monitor;
}

class Frm_Monitor : public TWidget
{
    Q_OBJECT

public:
    Frm_Monitor();
    ~Frm_Monitor();

private:
    QSignalMapper  sglMapCb;

private:
    Ui::Frm_Monitor *ui;

public:
    void UpdateIO();

private slots:
    void on_cbO_clicked(int ibtn);
};

#endif // FRM_MONITOR_H

//==========================================================================================
// End of file.
//==========================================================================================

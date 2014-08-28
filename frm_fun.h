/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_fun.h

* 功能描述: 主功能按钮头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef FRM_FUN_H
#define FRM_FUN_H

#include "twidget.h"
//#include <QWidget>

namespace Ui {
    class Frm_Fun;
}

class Frm_Fun : public TWidget
{
    Q_OBJECT

public:
    Frm_Fun();
    ~Frm_Fun();
    void OnQdec(QDECT qt, int spanT);

private:
    Ui::Frm_Fun *ui;

private slots:
    void on_btnHelp_clicked();
    void on_btnManufacturer_clicked();
    void on_btnAuthority_clicked();
    void on_btnMonitor_clicked();
    void on_btnLog_clicked();
    void on_btnStkS_clicked();
    void on_btnPdtS_clicked();
    void on_btnLang_clicked();
    void on_btnTimS_clicked();
    void on_btnRun_clicked();
    void on_btnUsrS_clicked();
    void on_btnSysS_clicked();
    void on_btnTeach_clicked();
};

#endif // FRM_FUN_H

//==========================================================================================
// End of file.
//==========================================================================================

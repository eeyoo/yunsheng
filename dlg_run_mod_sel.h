/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_run_mod_sel.h

* 功能描述: 运行模式选择文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef DLG_RUN_MOD_SEL_H
#define DLG_RUN_MOD_SEL_H

#include <QDialog>
#include "frm_run.h"

namespace Ui {
    class Dlg_Run_Mod_Sel;
}

class Dlg_Run_Mod_Sel : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Run_Mod_Sel(QWidget *parent = 0);
    ~Dlg_Run_Mod_Sel();
public:
    Frm_Run::Run_Model r_model;
private:
    void SndPgm();
private:
    Ui::Dlg_Run_Mod_Sel *ui;
private slots:
    void on_btnSStp_clicked();
    void on_btnSPrd_clicked();
    void on_btnCan_clicked();
    void on_btnAuto_clicked();
    void on_btnMana_clicked();
};

#endif // DLG_RUN_MOD_SEL_H

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_glbspd.h

* 功能描述: 自定义仪表控件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#ifndef DLG_GLBSPD_H
#define DLG_GLBSPD_H

#include <QDialog>

class Dashboard;

namespace Ui {
class Dlg_GlbSpd;
}

class Dlg_GlbSpd : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_GlbSpd(QWidget *parent = 0);
    ~Dlg_GlbSpd();

private slots:
    void on_leGlbSpd_clicked();
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_btnAdd_clicked();

    void on_btnSub_clicked();

private:
    Ui::Dlg_GlbSpd *ui;
    Dashboard *mBoard;
    double mVal; //全局速度百分比

};

#endif // DLG_GLBSPD_H

//==========================================================================================
// End of file.
//==========================================================================================

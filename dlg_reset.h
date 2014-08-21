/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_reset.h

* 功能描述: 复位界面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#ifndef DLG_RESET_H
#define DLG_RESET_H

#include <QDialog>

namespace Ui {
    class Dlg_Reset;
}

class Dlg_Reset : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Reset(QWidget *parent = 0);
    ~Dlg_Reset();

    bool chkRstOK();

private:
    Ui::Dlg_Reset *ui;

private slots:
    void on_btnQuit_clicked();
    void on_btnOK_clicked();
    void UpdateSet();
};

#endif // DLG_RESET_H

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_pgm_sel.h

* 功能描述: A5底层资源定义文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef DLG_PGM_SEL_H
#define DLG_PGM_SEL_H

#include <QDialog>

namespace Ui {
    class Dlg_Pgm_Sel;
}

class Dlg_Pgm_Sel : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Pgm_Sel(QWidget *parent = 0);
    ~Dlg_Pgm_Sel();
public:
    int m_iPgm;
private:
    Ui::Dlg_Pgm_Sel *ui;

private slots:
    void on_btnCan_clicked();
    void on_btnOK_clicked();
};

#endif // DLG_PGM_SEL_H

//==========================================================================================
// End of file.
//==========================================================================================

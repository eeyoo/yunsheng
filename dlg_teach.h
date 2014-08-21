/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_teach.h

* 功能描述: 示教文件保存头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef DLG_TEACH_H
#define DLG_TEACH_H

#include <QDialog>

namespace Ui {
    class Dlg_Teach;
}

class Dlg_Teach : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Teach(QWidget *parent = 0);
    ~Dlg_Teach();

private:
    Ui::Dlg_Teach *ui;

private slots:
    void on_btnCan_clicked();
    void on_btnOK_clicked();
};

#endif // DLG_TEACH_H

//==========================================================================================
// End of file.
//==========================================================================================

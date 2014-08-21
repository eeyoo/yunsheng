/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: Dlg_StackManage.h

* 功能描述: 堆叠程序管理界面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#ifndef DLG_STACKMANAGE_H
#define DLG_STACKMANAGE_H

#include <QDialog>

namespace Ui {
class Dlg_StackManage;
}

class Dlg_StackManage : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_StackManage(QWidget *parent = 0);
    ~Dlg_StackManage();

private:
    Ui::Dlg_StackManage *ui;

public:
    QString m_strN;
private:
    void SearchFile();

private slots:
    void on_btnCancel_clicked();
    void on_btnOK_clicked();
};

#endif // DLG_STACKMANAGE_H

//==========================================================================================
// End of file.
//==========================================================================================

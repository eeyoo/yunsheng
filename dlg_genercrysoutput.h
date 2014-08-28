/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_generrelayoutput.h

* 功能描述: 输出设置

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.8.20

* 修	改:
**************************************************************************************/

#ifndef DLG_GENERCRYSOUTPUT_H
#define DLG_GENERCRYSOUTPUT_H

#include <QDialog>
#include <QSignalMapper>

namespace Ui {
class Dlg_GenerCrysOutput;
}

class Dlg_GenerCrysOutput : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_GenerCrysOutput(QWidget *parent = 0);
    ~Dlg_GenerCrysOutput();

private:
    Ui::Dlg_GenerCrysOutput *ui;

private:
    QSignalMapper  sglMapL;
public:
    int iO;

private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
    void on_btn_clicked(int ibtn);
};

#endif // DLG_GENERCRYSOUTPUT_H


//==========================================================================================
// End of file.
//==========================================================================================

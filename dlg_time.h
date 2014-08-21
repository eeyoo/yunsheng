/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_time.h

* 功能描述: 修改系统时间头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef DLG_TIME_H
#define DLG_TIME_H

#include <QDialog>

//#include "tclock.h"
class AnalogClock;

namespace Ui {
    class Dlg_Time;
}

class Dlg_Time : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Time(QWidget *parent = 0);
    ~Dlg_Time();

private:
    Ui::Dlg_Time *ui;
    AnalogClock *clock;

private slots:
    void on_btnOK_clicked();
    void on_btnQuit_clicked();
};

#endif // DLG_TIME_H

//==========================================================================================
// End of file.
//==========================================================================================

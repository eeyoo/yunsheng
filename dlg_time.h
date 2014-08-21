/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_time.h

* ��������: �޸�ϵͳʱ��ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
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

/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: Frm_Monitor.h

* ��������: ���ӻ���

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef FRM_MONITOR_H
#define FRM_MONITOR_H

#include "twidget.h"
#include <QSignalMapper>

namespace Ui {
class Frm_Monitor;
}

class Frm_Monitor : public TWidget
{
    Q_OBJECT

public:
    Frm_Monitor();
    ~Frm_Monitor();

private:
    QSignalMapper  sglMapCb;

private:
    Ui::Frm_Monitor *ui;

public:
    void UpdateIO();

private slots:
    void on_cbO_clicked(int ibtn);
};

#endif // FRM_MONITOR_H

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: analogclock.h

* ��������: �Զ����ӱ�ؼ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef FRM_PROM_H
#define FRM_PROM_H

#include "twidget.h"

namespace Ui {
    class Frm_ProM;
}

class Frm_ProM : public TWidget
{
    Q_OBJECT

public:
    Frm_ProM();
    ~Frm_ProM();

private:
    Ui::Frm_ProM *ui;

private:
    void SearchFile();
    bool OnOpen();
private slots:
    void on_btnEx_clicked();
    void on_btnIm_clicked();
    void on_btnDel_clicked();
    void on_btnSveA_clicked();
    void on_btnRen_clicked();
    void on_btnEdit_clicked();
    void on_btnOpen_clicked();
    void on_btnNew_clicked();
    void setVisible(bool visible);
};

#endif // FRM_PROM_H

//==========================================================================================
// End of file.
//==========================================================================================

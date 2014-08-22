/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_stack.h

* ��������: �ѵ�����ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef FRM_STACK_H
#define FRM_STACK_H

#include "twidget.h"

namespace Ui {
class Frm_Stack;
}

class Frm_Stack : public TWidget
{
    Q_OBJECT

public:
    Frm_Stack();
    ~Frm_Stack();

public:
    enum STK_T{
        SET,TEACH
    }stk_t;

    QString strN;

private:
    bool bSve;
private:
    void GetData();
    void SetData();
private:
    Ui::Frm_Stack *ui;

private slots:
    void on_btnCancel_clicked();
    void on_btnStkDel_clicked();
    void on_btnStkSave_clicked();
    void on_btnStkOpen_clicked();
    void on_btnOk_clicked();
    void on_leStkInterY_clicked();
    void on_leStkNumY_clicked();
    void on_leStkInterX_clicked();
    void on_leStkNumX_clicked();
    void on_leStackSpd_clicked();
    void on_leStartPoint_clicked();
    void on_leReadypoint_clicked();
};

#endif // FRM_STACK_H

//==========================================================================================
// End of file.
//==========================================================================================

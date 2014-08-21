/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_pros.h

* ��������: ��Ʒ����ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef FRM_PROS_H
#define FRM_PROS_H

#include "twidget.h"

namespace Ui {
class Frm_ProS;
}

class Frm_ProS : public TWidget
{
    Q_OBJECT

public:
    Frm_ProS();
    ~Frm_ProS();

public:
    Ui::Frm_ProS *ui;
private slots:
    void on_lePlnPrd_clicked();
    void on_leBadPrd_clicked();
    void on_leCirTim_clicked();
    void on_leRstTim_clicked();
    void on_leSprVal_clicked();
};

#endif // FRM_PROS_H

//==========================================================================================
// End of file.
//==========================================================================================

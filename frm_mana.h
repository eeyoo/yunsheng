/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_mana.h

* ��������: ����ģʽѡ��ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef FRM_MANA_H
#define FRM_MANA_H

#include "twidget.h"
#include <QSignalMapper>

namespace Ui {
    class Frm_Mana;
}

class Frm_Mana : public TWidget
{
    Q_OBJECT

public:
    Frm_Mana();
    ~Frm_Mana();

private:
    QSignalMapper  sglMapRb;
    QSignalMapper  sglMapCb;
private:
    void InitRbSig();
    void InitCbSig();
private slots:
    void on_rb_clicked(int irb);
    void on_cb_clicked(int icb);
private:
    Ui::Frm_Mana *ui;
};

#endif // FRM_MANA_H

//==========================================================================================
// End of file.
//==========================================================================================

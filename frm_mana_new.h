/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_mana_new.h

* ��������: �ֶ�����

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef FRM_MANA_NEW_H
#define FRM_MANA_NEW_H

#include "twidget.h"

namespace Ui {
class Frm_Mana_New;
}

class Frm_Mana_New : public TWidget
{
    Q_OBJECT

public:
    Frm_Mana_New();
    ~Frm_Mana_New();

private:
    Ui::Frm_Mana_New *ui;
};

#endif // FRM_MANA_NEW_H

//==========================================================================================
// End of file.
//==========================================================================================

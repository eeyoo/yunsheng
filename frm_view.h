/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_view.h

* ��������: ϵͳ��ѯͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef FRM_VIEW_H
#define FRM_VIEW_H

#include "twidget.h"

namespace Ui {
    class Frm_View;
}

class Frm_View : public TWidget
{
    Q_OBJECT

public:
    Frm_View();
    ~Frm_View();

public slots:
    void setVisible(bool visible);
private:
    Ui::Frm_View *ui;
};

#endif // FRM_VIEW_H

//==========================================================================================
// End of file.
//==========================================================================================

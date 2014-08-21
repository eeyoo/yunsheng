/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_manufacturer.h

* ��������: �������û���

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef FRM_MANUFACTURER_H
#define FRM_MANUFACTURER_H

#include "twidget.h"

namespace Ui {
class Frm_Manufacturer;
}

class Frm_Manufacturer : public TWidget
{
    Q_OBJECT

public:
    Frm_Manufacturer();
    ~Frm_Manufacturer();


private slots:
    void on_btnUpd_clicked();
    void on_btnRelad_clicked();
    void on_btnReboot_clicked();

    void on_btnRecov_clicked();

private:
    Ui::Frm_Manufacturer *ui;
};

#endif // FRM_MANUFACTURER_H

//==========================================================================================
// End of file.
//==========================================================================================

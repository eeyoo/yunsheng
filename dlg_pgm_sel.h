/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_pgm_sel.h

* ��������: A5�ײ���Դ�����ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef DLG_PGM_SEL_H
#define DLG_PGM_SEL_H

#include <QDialog>

namespace Ui {
    class Dlg_Pgm_Sel;
}

class Dlg_Pgm_Sel : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Pgm_Sel(QWidget *parent = 0);
    ~Dlg_Pgm_Sel();
public:
    int m_iPgm;
private:
    Ui::Dlg_Pgm_Sel *ui;

private slots:
    void on_btnCan_clicked();
    void on_btnOK_clicked();
};

#endif // DLG_PGM_SEL_H

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_teach.h

* ��������: ʾ���ļ�����ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef DLG_TEACH_H
#define DLG_TEACH_H

#include <QDialog>

namespace Ui {
    class Dlg_Teach;
}

class Dlg_Teach : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Teach(QWidget *parent = 0);
    ~Dlg_Teach();

private:
    Ui::Dlg_Teach *ui;

private slots:
    void on_btnCan_clicked();
    void on_btnOK_clicked();
};

#endif // DLG_TEACH_H

//==========================================================================================
// End of file.
//==========================================================================================

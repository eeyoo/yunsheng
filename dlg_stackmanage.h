/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: Dlg_StackManage.h

* ��������: �ѵ�����������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef DLG_STACKMANAGE_H
#define DLG_STACKMANAGE_H

#include <QDialog>

namespace Ui {
class Dlg_StackManage;
}

class Dlg_StackManage : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_StackManage(QWidget *parent = 0);
    ~Dlg_StackManage();

private:
    Ui::Dlg_StackManage *ui;

public:
    QString m_strN;
private:
    void SearchFile();

private slots:
    void on_btnCancel_clicked();
    void on_btnOK_clicked();
};

#endif // DLG_STACKMANAGE_H

//==========================================================================================
// End of file.
//==========================================================================================

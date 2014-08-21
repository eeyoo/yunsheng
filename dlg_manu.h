/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_manu.h

* ��������: �ֶ�����

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef DLG_MANU_H
#define DLG_MANU_H

#include <QDialog>
#include <QSignalMapper>

namespace Ui {
    class Dlg_Manu;
}

class Dlg_Manu : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Manu(QWidget *parent = 0);
    ~Dlg_Manu();

private:
    Ui::Dlg_Manu *ui;
private:
    int m_iCurCmd;
    QSignalMapper  sglMapCb;
private:
    void SetBtnChk();
    void UpdateOut();
public:
    void InitBtn(int iCmd);
private slots:
    void on_btnReset_clicked();
    void on_btnSpeedLow_clicked();
    void on_btnSpeedHigh_clicked();
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
    void on_btnRun_clicked();
    void on_btnStp_clicked();
    void on_btnServoX_clicked();
    void on_btnServoY1_clicked();
    void on_btnServoY2_clicked();
    void on_btnServoZ1_clicked();
    void on_btnServoZ2_clicked();
    void on_btnServoY1Y2_clicked();
    void on_btnServoZ1Z2_clicked();
    void on_lePos_clicked();
    void on_btnUp_pressed();
    void on_btnUp_released();
    void on_btnDwn_pressed();
    void on_btnDwn_released();
    void on_cbO_clicked(int ibtn);
};

#endif // DLG_MANU_H

//==========================================================================================
// End of file.
//==========================================================================================

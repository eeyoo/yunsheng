/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: mainwindow.h

* ��������: ������ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTime>


#include "tdrvkey.h"
#include "tdrvqdec.h"



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    Ui::MainWindow *ui;
private:
    void InitComP();
private slots:
    void on_btnStp_clicked();
    void on_btnPrg_clicked();
    void on_btnWth_clicked();
    void on_btnbck_clicked();
    void on_btnLft_clicked();
    void on_btnRht_clicked();
    void Can_Com();
    void on_btnHlp_clicked();
    void on_btnMana_clicked();
    void on_btnRst_clicked();
    void on_btnSrt_clicked();

    void on_btnUp_pressed();
    void on_btnUp_released();
    void on_btnDwn_pressed();
    void on_btnDwn_released();
    void UpdateTim();

    void on_sigKey(int dt);
    void on_sigQdec(int dt);

private:
    QTime prsTim;       //��¼��ת����������ʱ��
};

#endif // MAINWINDOW_H

//==========================================================================================
// End of file.
//==========================================================================================

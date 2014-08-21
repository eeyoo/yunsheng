/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: mainwindow.h

* 功能描述: 主窗口头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
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
    QTime prsTim;       //记录旋转编码器按下时间
};

#endif // MAINWINDOW_H

//==========================================================================================
// End of file.
//==========================================================================================

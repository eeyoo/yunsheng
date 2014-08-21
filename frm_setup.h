/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_setup.h

* 功能描述: 设置画面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#ifndef FRM_SETUP_H
#define FRM_SETUP_H

#include "twidget.h"
#include <QSignalMapper>

namespace Ui {
class Frm_Setup;
}

class Frm_Setup : public TWidget
{
    Q_OBJECT

public:
    Frm_Setup();
    ~Frm_Setup();

private:
    Ui::Frm_Setup *ui;

public:
    void SetSeroPara();
    void SetResetPara();
    void SetAxisEn();

    void OnQdec(QDECT qt);

private:
    QSignalMapper  sglMapL;
private slots:
    void on_leRstSpd_clicked();
    void on_btnServoRead_clicked();
    void on_btnSysRead_clicked();
    void on_btnVelG_clicked();
    void on_ckScreenSound_clicked(bool checked);
    void on_ckKeySound_clicked(bool checked);
    void on_btnCalib_clicked();
    void on_btnServoSend_clicked();
    void on_btnSysSend_clicked();
    void on_rdBtnEng_clicked(bool checked);
    void on_rdBtnChi_clicked(bool checked);
    void on_cbEnableZ2_clicked(bool check);
    void on_cbEnableY2_clicked(bool check);
    void on_cbEnableZ1_clicked(bool check);
    void on_cbEnableY1_clicked(bool check);
    void on_cbEnableX_clicked(bool check);
    void on_de_date_editingFinished();
    void on_le_ser_clicked();
    void on_le_ver_clicked();
    void on_le_psw_clicked();
    void on_le_clicked(int ile);
    void on_cbRes_clicked();
    void on_cbMainE_clicked();
    void on_cbSic_clicked();
    void on_cbMainS_clicked();
    void on_rbwatE_clicked(bool checked);
    void on_rbwatH_clicked(bool checked);

    void setVisible(bool visible);

    void on_lePlnPrd_clicked();
    void on_leBadPrd_clicked();
    void on_leCirTim_clicked();
    void on_leRstTim_clicked();
    void on_leSprVal_clicked();
};

#endif // FRM_SETUP_H

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_setup.cpp

* ��������: ���û���

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include <QProcess>

#include "frm_setup.h"
#include "ui_frm_setup.h"
#include "ui_mainwindow.h"
#include "dlg_psw.h"
#include "tcom.h"
#include "tconfig.h"
#include "twidmana.h"
#include "dlg_glbspd.h"

/*************************************************************************
* ��������: Frm_Setup
* ��   ��: ���캯��
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Setup::Frm_Setup() :
    
    ui(new Ui::Frm_Setup)
{
    ui->setupUi(this);

    TLineEdit *tle[] = {ui->leAbsLX,ui->leMaxAX,ui->leMaxSX,ui->lePlsX,ui->lePrdWX,ui->leErrAX,ui->leRSpdX,ui->leMSpdX,ui->leZroOftX,ui->leJog_D_TX,
                      ui->leAbsLY1,ui->leMaxAY1,ui->leMaxSY1,ui->lePlsY1,ui->lePrdWY1,ui->leErrAY1,ui->leRSpdY1,ui->leMSpdY1,ui->leZroOftY1,ui->leJog_D_TY1,
                      ui->leAbsLZ1,ui->leMaxAZ1,ui->leMaxSZ1,ui->lePlsZ1,ui->lePrdWZ1,ui->leErrAZ1,ui->leRSpdZ1,ui->leMSpdZ1,ui->leZroOftZ1,ui->leJog_D_TZ1,
                      ui->leAbsLY2,ui->leMaxAY2,ui->leMaxSY2,ui->lePlsY2,ui->lePrdWY2,ui->leErrAY2,ui->leRSpdY2,ui->leMSpdY2,ui->leZroOftY2,ui->leJog_D_TY2,
                      ui->leAbsLZ2,ui->leMaxAZ2,ui->leMaxSZ2,ui->lePlsZ2,ui->lePrdWZ2,ui->leErrAZ2,ui->leRSpdZ2,ui->leMSpdZ2,ui->leZroOftZ2,ui->leJog_D_TZ2};
    for(int i = 0;i<sizeof(tle)/sizeof(TLineEdit*);i++)
    {
        sglMapL.setMapping(tle[i],i);
        connect(tle[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_le_clicked(int)));

    if(config.cfg.bEn){
        ui->rdBtnChi->setChecked(false);
        ui->rdBtnEng->setChecked(true);
    }else{
        ui->rdBtnChi->setChecked(true);
        ui->rdBtnEng->setChecked(false);
    }
}
/*************************************************************************
* ��������: Frm_Setup
* ��   ��: ��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Setup::~Frm_Setup()
{
    delete ui;
}
/*************************************************************************
* ��������: on_le_clicked
* ��    ��: ��ӦQLineEdit����
* �������: ile	QLineEdit������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_le_clicked(int ile)
{
    TLineEdit *tle[] = {ui->leAbsLX,ui->leMaxAX,ui->leMaxSX,ui->lePlsX,ui->lePrdWX,ui->leErrAX,ui->leRSpdX,ui->leMSpdX,ui->leZroOftX,ui->leJog_D_TX,
                      ui->leAbsLY1,ui->leMaxAY1,ui->leMaxSY1,ui->lePlsY1,ui->lePrdWY1,ui->leErrAY1,ui->leRSpdY1,ui->leMSpdY1,ui->leZroOftY1,ui->leJog_D_TY1,
                      ui->leAbsLZ1,ui->leMaxAZ1,ui->leMaxSZ1,ui->lePlsZ1,ui->lePrdWZ1,ui->leErrAZ1,ui->leRSpdZ1,ui->leMSpdZ1,ui->leZroOftZ1,ui->leJog_D_TZ1,
                      ui->leAbsLY2,ui->leMaxAY2,ui->leMaxSY2,ui->lePlsY2,ui->lePrdWY2,ui->leErrAY2,ui->leRSpdY2,ui->leMSpdY2,ui->leZroOftY2,ui->leJog_D_TY2,
                      ui->leAbsLZ2,ui->leMaxAZ2,ui->leMaxSZ2,ui->lePlsZ2,ui->lePrdWZ2,ui->leErrAZ2,ui->leRSpdZ2,ui->leMSpdZ2,ui->leZroOftZ2,ui->leJog_D_TZ2};


    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        if(ile%10 == 0 || ile%10 == 5 || ile%10 == 8){
            QString strT = dlg.m_str;
            strT = strT.right(strT.length() - strT.indexOf('.') - 1);
            if((strT.length() > 2) && (strT != dlg.m_str))
                return;
        }

        if(tle[ile] == ui->leAbsLZ1){
            if(dlg.m_str.toInt() > 360)
                return;
        }
        tle[ile]->setText(dlg.m_str);
    }
}
/*************************************************************************
* ��������: on_le_ser_clicked
* ��    ��: �������к�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_le_ser_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->le_ser->setText(dlg.m_str);

        for(int i = 0;i<dlg.m_str.length();i++)
        {
            com01.para.ser[i] = dlg.m_str.at(i).toAscii();
            if(i == sizeof(com01.para.ser)-1)
                break;
        }

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com01));
    }
}
/*************************************************************************
* ��������: on_le_ver_clicked
* ��    ��: ����汾��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_le_ver_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->le_ver->setText(dlg.m_str);

        for(int i=0;i<dlg.m_str.length();i++)
        {
            com01.para.ver[i] = dlg.m_str.at(i).toAscii();
            if(i == sizeof(com01.para.ver)-1)
                break;
        }

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com01));
    }
}
/*************************************************************************
* ��������: on_le_psw_clicked
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_le_psw_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec()==QDialog::Accepted)
    {
        //ui->le_psw->setText(dlg.m_str);

        for(int i=0;i<dlg.m_str.length();i++)
        {
            com01.para.psw[i]=dlg.m_str.at(i).toAscii();
            if(i==sizeof(com01.para.psw)-1)
                break;
        }

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com01));
    }
}
/*************************************************************************
* ��������: on_de_date_editingFinished
* ��    ��: ����汾ʱ��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_de_date_editingFinished()
{
    /*QDate date=ui->de_date->date();
    com01.para.year     =date.year();
    com01.para.month    =date.month();
    com01.para.day      =date.day();
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&com01));*/
}
/*************************************************************************
* ��������: on_cbEnableX_clicked
* ��    ��: ʹ��X��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_cbEnableX_clicked(bool check)
{
    com02.para[0].axisp = check?TCom02::ENABLE:TCom02::DISABLE;
    SetAxisEn();
}
/*************************************************************************
* ��������: on_cbEnableY1_clicked
* ��    ��: ʹ��Y1��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_cbEnableY1_clicked(bool check)
{
    com02.para[1].axisp = check?TCom02::ENABLE:TCom02::DISABLE;
    SetAxisEn();
}
/*************************************************************************
* ��������: on_cbEnableZ1_clicked
* ��    ��: ʹ��Z1��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_cbEnableZ1_clicked(bool check)
{
    com02.para[2].axisp = check?TCom02::ENABLE:TCom02::DISABLE;
    SetAxisEn();
}
/*************************************************************************
* ��������: on_cbEnableY2_clicked
* ��    ��: ʹ��Y2��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_cbEnableY2_clicked(bool check)
{
    com02.para[3].axisp = check?TCom02::ENABLE:TCom02::DISABLE;
    SetAxisEn();
}
/*************************************************************************
* ��������: on_cbEnableZ2_clicked
* ��    ��: ʹ��Z2��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_cbEnableZ2_clicked(bool check)
{
    com02.para[4].axisp=check?TCom02::ENABLE:TCom02::DISABLE;
    SetAxisEn();
}
/*************************************************************************
* ��������: on_rbwatH_clicked
* ��    ��: ���ͷ������
* �������: checked	���״̬
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_rbwatH_clicked(bool checked)
{
    com03.para.wattyp=TCom03::WAITH;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&com03));
}
/*************************************************************************
* ��������: on_rbwatE_clicked
* ��    ��: ���β������
* �������: checked	���״̬
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_rbwatE_clicked(bool checked)
{
    com03.para.wattyp=TCom03::WAITE;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&com03));
}
/*************************************************************************
* ��������: on_cbMainS_clicked
* ��    ��: ������������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_cbMainS_clicked()
{
    /*com04.para.mainS=ui->cbMainS->checkState()?
                     TCom04::ENABLE:TCom04::DISABLE;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&com04));*/
}
/*************************************************************************
* ��������: on_cbSic_clicked
* ��    ��: ����������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_cbSic_clicked()
{
    /*com04.para.Sic=ui->cbSic->checkState()?
                     TCom04::ENABLE:TCom04::DISABLE;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&com04));*/
}
/*************************************************************************
* ��������: on_cbMainE_clicked
* ��    ��: ������۱����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_cbMainE_clicked()
{
    /*com04.para.mainE=ui->cbMainE->checkState()?
                     TCom04::ENABLE:TCom04::DISABLE;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&com04));*/
}
/*************************************************************************
* ��������: on_cbRes_clicked
* ��    ��: ���ü��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::on_cbRes_clicked()
{
    /*com04.para.rechk=ui->cbRes->checkState()?
                     TCom04::ENABLE:TCom04::DISABLE;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&com04));*/
}
/*************************************************************************
* ��������: setVisible
* ��    ��: ��ʼ��������ʾ�����ó����еĿ��
* �������: visible	true��ʾ��false����
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Setup::setVisible(bool visible)
{
    QWidget::setVisible(visible);

    if(visible)
    {
        SetSeroPara();
        SetResetPara();
    }
}
/*************************************************************************
* ��������: SetSeroPara
* ��    ��: �����ŷ�����
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::SetSeroPara()
{
    //�������
    QCheckBox* cbD[] = {ui->cbDirX,ui->cbDirY1,ui->cbDirZ1,ui->cbDirY2,ui->cbDirZ2};
    //���ʹ��
    QCheckBox* cbE[] = {ui->cbEnableX,ui->cbEnableY1,ui->cbEnableZ1,ui->cbEnableY2,ui->cbEnableZ2};
    //���ٶ�ʹ��
    QCheckBox* cbAE[] = {ui->cbAccX,ui->cbAccY1,ui->cbAccZ1,ui->cbAccY2,ui->cbAccZ2};

    TLineEdit *tle[] = {ui->leAbsLX,ui->leMaxAX,ui->leMaxSX,ui->lePlsX,ui->lePrdWX,ui->leErrAX,ui->leRSpdX,ui->leMSpdX,ui->leZroOftX,ui->leJog_D_TX,
                      ui->leAbsLY1,ui->leMaxAY1,ui->leMaxSY1,ui->lePlsY1,ui->lePrdWY1,ui->leErrAY1,ui->leRSpdY1,ui->leMSpdY1,ui->leZroOftY1,ui->leJog_D_TY1,
                      ui->leAbsLZ1,ui->leMaxAZ1,ui->leMaxSZ1,ui->lePlsZ1,ui->lePrdWZ1,ui->leErrAZ1,ui->leRSpdZ1,ui->leMSpdZ1,ui->leZroOftZ1,ui->leJog_D_TZ1,
                      ui->leAbsLY2,ui->leMaxAY2,ui->leMaxSY2,ui->lePlsY2,ui->lePrdWY2,ui->leErrAY2,ui->leRSpdY2,ui->leMSpdY2,ui->leZroOftY2,ui->leJog_D_TY2,
                      ui->leAbsLZ2,ui->leMaxAZ2,ui->leMaxSZ2,ui->lePlsZ2,ui->lePrdWZ2,ui->leErrAZ2,ui->leRSpdZ2,ui->leMSpdZ2,ui->leZroOftZ2,ui->leJog_D_TZ2};

    for(int i = 0; i < 5; i++){
        float absL = ((float)(com02.para[i].absL)) / 100.0;
        tle[i * 10 + 0]->setText(QString::number(absL,'f',2));
        tle[i * 10 + 1]->setText(QString("%1").arg(com02.para[i].maxA));
        tle[i * 10 + 2]->setText(QString("%1").arg(com02.para[i].maxS));

        //float pls_equ = ((float)(com02.para[i].pls_equ)) / 100.0;
        //tle[i * 10 + 3]->setText(QString::number(pls_equ,'f',2));
        tle[i * 10 + 3]->setText(QString("%1").arg(com02.para[i].pls_equ));
        tle[i * 10 + 4]->setText(QString("%1").arg(com02.para[i].prdw));

        float errA = ((float)(com02.para[i].errA)) / 100.0;
        tle[i * 10 + 5]->setText(QString::number(errA,'f',2));
        tle[i * 10 + 6]->setText(QString("%1").arg(com02.para[i].rspd));
        tle[i * 10 + 7]->setText(QString("%1").arg(com02.para[i].manS));

        float zro_off = ((float)(com02.para[i].zro_off)) / 100.0;
        tle[i * 10 + 8]->setText(QString::number(zro_off,'f',2));

        tle[i * 10 + 9]->setText(QString("%1").arg(com02.para[i].jog_d_t));

        cbAE[i]->setChecked(com02.para[i].accp);
        cbE[i]->setChecked(com02.para[i].axisp);
        cbD[i]->setChecked(com02.para[i].mtrD);
    }

    SetAxisEn();

    QString strSer;
    for(int i = 0;i<sizeof(com01.para.ser);i++)
        strSer += (char)com01.para.ser[i];
    ui->le_ser->setText(strSer);

    QString strPsw;
    for(int i = 0;i<sizeof(com01.para.psw);i++)
        strPsw += (char)com01.para.psw[i];

    QString strVer;
    for(int i = 0;i<sizeof(com01.para.ver);i++)
        strVer += (char)com01.para.ver[i];
    ui->le_ver->setText(strVer);

    ui->ckKeySound->setChecked(config.cfg.bBuzzK);
    ui->ckScreenSound->setChecked(config.cfg.bBuzzD);
}
/*************************************************************************
* ��������: SetResetPara
* ��    ��: ���ø�λ����
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::SetResetPara()
{
    ui->leRstSpd->setText(QString("%1").arg(com07.para.spd[0]));

    QComboBox*  cbbA[]  = {ui->cbBoxRstFirst,ui->cbBoxRstSec,ui->cbBoxRstTree,
                           ui->cbBoxRstFouth,ui->cbBoxRstFifth};
    for(int i = 0; i < sizeof(cbbA)/sizeof(QComboBox*); i++){
        if(cbbA[i]->count() > com07.para.axis[i] - 1){
            cbbA[i]->setCurrentIndex(com07.para.axis[i] - 1);
        }
    }

}
/*************************************************************************
* ��������: SetAxisEn
* ��    ��: ���������ʾ
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::SetAxisEn()
{
    quint8      axisp[] = {com02.para[0].axisp,com02.para[1].axisp,com02.para[2].axisp,
                           com02.para[3].axisp,com02.para[4].axisp};
    //�������
    QCheckBox* cbD[] = {ui->cbDirX,ui->cbDirY1,ui->cbDirZ1,ui->cbDirY2,ui->cbDirZ2};
    //���ʹ��
    QCheckBox* cbA[] = {ui->cbEnableX,ui->cbEnableY1,ui->cbEnableZ1,ui->cbEnableY2,ui->cbEnableZ2};
    //���ٶ�ʹ��
    QCheckBox* cbAE[] = {ui->cbAccX,ui->cbAccY1,ui->cbAccZ1,ui->cbAccY2,ui->cbAccZ2};

    QLabel*     lblA[]  = {widMana->mainW->ui->lblXPos,widMana->mainW->ui->lblY1Pos,
                           widMana->mainW->ui->lblZ1Pos,widMana->mainW->ui->lblY2Pos,
                           widMana->mainW->ui->lblZ2Pos};
    QComboBox*  cbbA[]  = {ui->cbBoxRstFirst,ui->cbBoxRstSec,ui->cbBoxRstTree,
                           ui->cbBoxRstFouth,ui->cbBoxRstFifth};
    QString     strA[]  = {QString("X"),QString("Y1"),QString("Z1"),QString("Y2"),QString("Z2")};

    TLineEdit *tle[] = {ui->leAbsLX,ui->leMaxAX,ui->leMaxSX,ui->lePlsX,ui->lePrdWX,ui->leErrAX,ui->leRSpdX,ui->leMSpdX,ui->leZroOftX,ui->leJog_D_TX,
                      ui->leAbsLY1,ui->leMaxAY1,ui->leMaxSY1,ui->lePlsY1,ui->lePrdWY1,ui->leErrAY1,ui->leRSpdY1,ui->leMSpdY1,ui->leZroOftY1,ui->leJog_D_TY1,
                      ui->leAbsLZ1,ui->leMaxAZ1,ui->leMaxSZ1,ui->lePlsZ1,ui->lePrdWZ1,ui->leErrAZ1,ui->leRSpdZ1,ui->leMSpdZ1,ui->leZroOftZ1,ui->leJog_D_TZ1,
                      ui->leAbsLY2,ui->leMaxAY2,ui->leMaxSY2,ui->lePlsY2,ui->lePrdWY2,ui->leErrAY2,ui->leRSpdY2,ui->leMSpdY2,ui->leZroOftY2,ui->leJog_D_TY2,
                      ui->leAbsLZ2,ui->leMaxAZ2,ui->leMaxSZ2,ui->lePlsZ2,ui->lePrdWZ2,ui->leErrAZ2,ui->leRSpdZ2,ui->leMSpdZ2,ui->leZroOftZ2,ui->leJog_D_TZ2};

    for(int i = 0; i < sizeof(axisp)/sizeof(quint8); i++){
        cbA[i]->setChecked(axisp[i]?true:false);
        lblA[i]->setEnabled(axisp[i]?true:false);

        cbD[i]->setEnabled(axisp[i]?true:false);
        cbAE[i]->setEnabled(axisp[i]?true:false);

        tle[i * 10 + 0]->setEnabled(axisp[i]?true:false);
        tle[i * 10 + 1]->setEnabled(axisp[i]?true:false);
        tle[i * 10 + 2]->setEnabled(axisp[i]?true:false);
        tle[i * 10 + 3]->setEnabled(axisp[i]?true:false);
        tle[i * 10 + 4]->setEnabled(axisp[i]?true:false);
        tle[i * 10 + 5]->setEnabled(axisp[i]?true:false);
        tle[i * 10 + 6]->setEnabled(axisp[i]?true:false);
        tle[i * 10 + 7]->setEnabled(axisp[i]?true:false);
        tle[i * 10 + 8]->setEnabled(axisp[i]?true:false);
        tle[i * 10 + 9]->setEnabled(axisp[i]?true:false);
    }

    for(int i = 0; i < sizeof(cbbA)/sizeof(QComboBox*); i++){
        cbbA[i]->clear();
        cbbA[i]->setEnabled(true);
        for(int j = 0; j < sizeof(axisp)/sizeof(quint8); j++){
            if(axisp[j]){
                cbbA[i]->addItem(strA[j]);
            }
        }
    }

    for(int i = cbbA[0]->count(); i < sizeof(cbbA)/sizeof(QComboBox*); i++){
        cbbA[i]->clear();
        cbbA[i]->setEnabled(false);
    }
}

/*************************************************************************
* ��������: on_lePlnPrd_clicked
* ��    ��: ����ƻ���������
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_lePlnPrd_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->lePlnPrd->setText(dlg.m_str);
        com05.para.pln_prd = dlg.m_str.toInt();

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com05));
    }
}
/*************************************************************************
* ��������: on_leBadPrd_clicked
* ��    ��: ���벻����������
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_leBadPrd_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->leBadPrd->setText(dlg.m_str);
        com05.para.bad_prd = dlg.m_str.toInt();

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com05));
    }
}
/*************************************************************************
* ��������: on_leCirTim_clicked
* ��    ��: ����ѭ����ʱ
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_leCirTim_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->leCirTim->setText(dlg.m_str);
        com05.para.cir_tim = dlg.m_str.toInt();

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com05));
    }
}
/*************************************************************************
* ��������: on_leRstTim_clicked
* ��    ��: ���븴λʱ��
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_leRstTim_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->leRstTim->setText(dlg.m_str);
        com05.para.rst_tim = dlg.m_str.toInt();

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com05));
    }
}
/*************************************************************************
* ��������: on_leSprVal_clicked
* ��    ��: ����������
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_leSprVal_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->leSprVal->setText(dlg.m_str);
        com05.para.spr_val = dlg.m_str.toInt();

        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)(&com05));
    }
}
/*************************************************************************
* ��������: on_rdBtnChi_clicked
* ��    ��: ������ʾ����
* �������: checked true���� falseӢ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_rdBtnChi_clicked(bool checked)
{
    //if(checked){
         config.cfg.bEn = false;
         config.SaveCfg();
    //}
}
/*************************************************************************
* ��������: on_rdBtnEng_clicked
* ��    ��: ������ʾ����
* �������: checked trueӢ�� false����
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_rdBtnEng_clicked(bool checked)
{
    //if(checked){
        config.cfg.bEn = true;
        config.SaveCfg();
    //}
}
/*************************************************************************
* ��������: on_btnSysSend_clicked
* ��    ��: ���͸�λ����
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_btnSysSend_clicked()
{
    QComboBox*  cbbA[]  = {ui->cbBoxRstFirst,ui->cbBoxRstSec,ui->cbBoxRstTree,
                           ui->cbBoxRstFouth,ui->cbBoxRstFifth};
    QString     strA[]  = {QString("X"),QString("Y1"),QString("Z1"),QString("Y2"),QString("Z2")};

    memset(&com07.para,sizeof(com07.para),0);


    for(int i = 0; i < sizeof(cbbA)/sizeof(QComboBox*); i++){
        com07.para.spd[i] = ui->leRstSpd->text().toInt();

        if(cbbA[i]->isEnabled()){
            QString strT = cbbA[i]->currentText();
            for(int j = 0; j < 5; j++){
                if(strT == strA[j]){
                    com07.para.axis[i] = j + 1;
                    break;
                }
            }
        }else{
            com07.para.axis[i] = 0;
        }
    }

    widMana->SavePara();

    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)&com07);
}
/*************************************************************************
* ��������: on_btnServoSend_clicked
* ��    ��: ���͵����������
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_btnServoSend_clicked()
{
    //�������
    QCheckBox* cbD[] = {ui->cbDirX,ui->cbDirY1,ui->cbDirZ1,ui->cbDirY2,ui->cbDirZ2};
    //���ʹ��
    QCheckBox* cbE[] = {ui->cbEnableX,ui->cbEnableY1,ui->cbEnableZ1,ui->cbEnableY2,ui->cbEnableZ2};
    //���ٶ�ʹ��
    QCheckBox* cbAE[] = {ui->cbAccX,ui->cbAccY1,ui->cbAccZ1,ui->cbAccY2,ui->cbAccZ2};

    TLineEdit *tle[] = {ui->leAbsLX,ui->leMaxAX,ui->leMaxSX,ui->lePlsX,ui->lePrdWX,ui->leErrAX,ui->leRSpdX,ui->leMSpdX,ui->leZroOftX,ui->leJog_D_TX,
                      ui->leAbsLY1,ui->leMaxAY1,ui->leMaxSY1,ui->lePlsY1,ui->lePrdWY1,ui->leErrAY1,ui->leRSpdY1,ui->leMSpdY1,ui->leZroOftY1,ui->leJog_D_TY1,
                      ui->leAbsLZ1,ui->leMaxAZ1,ui->leMaxSZ1,ui->lePlsZ1,ui->lePrdWZ1,ui->leErrAZ1,ui->leRSpdZ1,ui->leMSpdZ1,ui->leZroOftZ1,ui->leJog_D_TZ1,
                      ui->leAbsLY2,ui->leMaxAY2,ui->leMaxSY2,ui->lePlsY2,ui->lePrdWY2,ui->leErrAY2,ui->leRSpdY2,ui->leMSpdY2,ui->leZroOftY2,ui->leJog_D_TY2,
                      ui->leAbsLZ2,ui->leMaxAZ2,ui->leMaxSZ2,ui->lePlsZ2,ui->lePrdWZ2,ui->leErrAZ2,ui->leRSpdZ2,ui->leMSpdZ2,ui->leZroOftZ2,ui->leJog_D_TZ2};

    for(int i = 0; i < 5; i++){
        com02.para[i].pls_equ    = tle[i * 10 + 3]->text().toInt();
        com02.para[i].absL       = tle[i * 10 + 0]->text().toDouble() * 100.0;
        com02.para[i].maxA       = tle[i * 10 + 1]->text().toInt();
        com02.para[i].maxS       = tle[i * 10 + 2]->text().toInt();

        com02.para[i].prdw       = tle[i * 10 + 4]->text().toInt();
        com02.para[i].errA       = tle[i * 10 + 5]->text().toDouble() * 100.0;
        com02.para[i].rspd       = tle[i * 10 + 6]->text().toInt();
        com02.para[i].manS       = tle[i * 10 + 7]->text().toInt();
        com02.para[i].zro_off    = tle[i * 10 + 8]->text().toDouble() * 100.0;

        com02.para[i].jog_d_t    = tle[i * 10 + 9]->text().toInt();

        com02.para[i].accp       = cbAE[i]->isChecked()?1:0;
        com02.para[i].axisp      = cbE[i]->isChecked()?1:0;
        com02.para[i].mtrD       = cbD[i]->isChecked()?1:0;

        com02.para[i].axisT      = 0;
    }

    com02.para[2].axisT      = 1;

    widMana->SavePara();

    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)&com02);
}
/*************************************************************************
* ��������: on_btnCalib_clicked
* ��    ��: ����У׼��Ļ
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_btnCalib_clicked()
{
    int res = QProcess::execute("/root/calibrate");
    if (!((res == -2) && (res == -1)))
        widMana->mainW->update();
}
/*************************************************************************
* ��������: on_ckKeySound_clicked
* ��    ��: ���ư���������
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_ckKeySound_clicked(bool checked)
{
    config.cfg.bBuzzK = checked;
    config.SaveCfg();
}
/*************************************************************************
* ��������: on_ckScreenSound_clicked
* ��    ��: ���ƴ�����������
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_ckScreenSound_clicked(bool checked)
{
    config.cfg.bBuzzD = checked;
    config.SaveCfg();
}
/*************************************************************************
* ��������: on_btnVelG_clicked
* ��    ��: ���������ٶ�
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_btnVelG_clicked()
{
    Dlg_GlbSpd dlg;
    dlg.setModal(true);
    dlg.exec();
}
/*************************************************************************
* ��������: on_btnSysRead_clicked
* ��    ��: ��ȡ��λ����
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_btnSysRead_clicked()
{
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)&comF2);
}
/*************************************************************************
* ��������: on_btnServoRead_clicked
* ��    ��: ��ȡ�ŷ�����
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_btnServoRead_clicked()
{
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)&comF1);

    //ui->tabWidget_2->setCurrentWidget(ui->tab_2);

    //QWidget* pW = (QWidget*)ui->leAbsLX;
    //ui->btnServoRead->setText(pW->metaObject()->className());
}
/*************************************************************************
* ��������: on_leRstSpd_clicked
* ��    ��: ���ø�λ�ٶ�
* �������: ��
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::on_leRstSpd_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->leRstSpd->setText(dlg.m_str);
    }
}
/*************************************************************************
* ��������: OnQdec
* ��    ��: ��Ӧ��ת������
* �������: qt ��ת�������Ķ���
* �������: ��
* �� �� ֵ:
*************************************************************************/
void Frm_Setup::OnQdec(QDECT qt)
{
    QWidget* pW[] = {(QWidget*)ui->cbEnableX,(QWidget*)ui->cbDirX,(QWidget*)ui->cbAccX,
                     (QWidget*)ui->leAbsLX,(QWidget*)ui->leMaxSX,(QWidget*)ui->leMaxAX,
                     (QWidget*)ui->lePlsX,(QWidget*)ui->lePrdWX,(QWidget*)ui->leErrAX,
                     (QWidget*)ui->leRSpdX,(QWidget*)ui->leMSpdX,(QWidget*)ui->leZroOftX,
                     (QWidget*)ui->leJog_D_TX,(QWidget*)ui->btnServoSend,(QWidget*)ui->btnServoRead,

                     (QWidget*)ui->cbEnableY1,(QWidget*)ui->cbDirY1,(QWidget*)ui->cbAccY1,
                     (QWidget*)ui->leAbsLY1,(QWidget*)ui->leMaxSY1,(QWidget*)ui->leMaxAY1,
                     (QWidget*)ui->lePlsY1,(QWidget*)ui->lePrdWY1,(QWidget*)ui->leErrAY1,
                     (QWidget*)ui->leRSpdY1,(QWidget*)ui->leMSpdY1,(QWidget*)ui->leZroOftY1,
                     (QWidget*)ui->leJog_D_TY1,(QWidget*)ui->btnServoSend,(QWidget*)ui->btnServoRead,

                     (QWidget*)ui->cbEnableZ1,(QWidget*)ui->cbDirZ1,(QWidget*)ui->cbAccZ1,
                     (QWidget*)ui->leAbsLZ1,(QWidget*)ui->leMaxSZ1,(QWidget*)ui->leMaxAZ1,
                     (QWidget*)ui->lePlsZ1,(QWidget*)ui->lePrdWZ1,(QWidget*)ui->leErrAZ1,
                     (QWidget*)ui->leRSpdZ1,(QWidget*)ui->leMSpdZ1,(QWidget*)ui->leZroOftZ1,
                     (QWidget*)ui->leJog_D_TZ1,(QWidget*)ui->btnServoSend,(QWidget*)ui->btnServoRead,

                     (QWidget*)ui->cbEnableY2,(QWidget*)ui->cbDirY2,(QWidget*)ui->cbAccY2,
                     (QWidget*)ui->leAbsLY2,(QWidget*)ui->leMaxSY2,(QWidget*)ui->leMaxAY2,
                     (QWidget*)ui->lePlsY2,(QWidget*)ui->lePrdWY2,(QWidget*)ui->leErrAY2,
                     (QWidget*)ui->leRSpdY2,(QWidget*)ui->leMSpdY2,(QWidget*)ui->leZroOftY2,
                     (QWidget*)ui->leJog_D_TY2,(QWidget*)ui->btnServoSend,(QWidget*)ui->btnServoRead,

                     (QWidget*)ui->cbEnableZ2,(QWidget*)ui->cbDirZ2,(QWidget*)ui->cbAccZ2,
                     (QWidget*)ui->leAbsLZ2,(QWidget*)ui->leMaxSZ2,(QWidget*)ui->leMaxAZ2,
                     (QWidget*)ui->lePlsZ2,(QWidget*)ui->lePrdWZ2,(QWidget*)ui->leErrAZ2,
                     (QWidget*)ui->leRSpdZ2,(QWidget*)ui->leMSpdZ2,(QWidget*)ui->leZroOftZ2,
                     (QWidget*)ui->leJog_D_TZ2,(QWidget*)ui->btnServoSend,(QWidget*)ui->btnServoRead,



                     (QWidget*)ui->leRstSpd,(QWidget*)ui->cbBoxRstFirst,(QWidget*)ui->cbBoxRstSec,
                     (QWidget*)ui->cbBoxRstTree,(QWidget*)ui->cbBoxRstFouth,(QWidget*)ui->cbBoxRstFifth,
                     (QWidget*)ui->btnSysSend,(QWidget*)ui->btnSysRead,(QWidget*)ui->leScrProTim,
                     (QWidget*)ui->btnCalib,(QWidget*)ui->rdBtnChi,
                     (QWidget*)ui->rdBtnEng,(QWidget*)ui->le_ser,(QWidget*)ui->le_ser_2,
                     (QWidget*)ui->le_ver,(QWidget*)ui->btnVelG,(QWidget*)ui->ckKeySound,
                     (QWidget*)ui->ckScreenSound,



                     (QWidget*)ui->lePlnPrd,(QWidget*)ui->lineEdit_2,(QWidget*)ui->lineEdit_6,
                     (QWidget*)ui->leCirTim_2,(QWidget*)ui->leCirTim,(QWidget*)ui->leRstTim,
                     (QWidget*)ui->leBadPrd,(QWidget*)ui->lineEdit_8,(QWidget*)ui->leSprVal

                     /*(QWidget*)ui->,(QWidget*)ui->,
                     (QWidget*)ui->,(QWidget*)ui->,(QWidget*)ui->,
                     (QWidget*)ui->,(QWidget*)ui->,(QWidget*)ui->,
                     (QWidget*)ui->,(QWidget*)ui->,(QWidget*)ui->,
                     (QWidget*)ui->,(QWidget*)ui->,(QWidget*)ui->,
                     (QWidget*)ui->,(QWidget*)ui->,(QWidget*)ui->*/};

    static QWidget  *pCW = NULL;
    static int      PrsT = 0;    //�������
    static int      iCur = 0;    //��ǰ��ȡ����ؼ�
    static int      iS   = sizeof(pW)/sizeof(QWidget*);
    //�ж��н���Ŀؼ�
    for(iCur = 0; iCur < iS; iCur++){
        if(pW[iCur]->hasFocus()){
            break;
        }
    }

    if(pW[iCur] == pW[13] ||
            pW[iCur] == pW[14]){
        iCur += ui->tabW_sero->currentIndex() * 15;
    }
    //iCur = 75 + 19 +2;
    iCur %= iS;

    switch(qt){
    case AHD:
        if((PrsT > 0) && (pCW == pW[iCur])){
            DoAhd(pCW,&PrsT);
        }else{
            PrsT = 0;
            iCur++;
            iCur %= iS;

            pW[iCur]->setFocus();
        }
        break;
    case BCK:
        if((PrsT > 0) && (pCW == pW[iCur])){
            DoBck(pCW,&PrsT);
        }else{
            PrsT = 0;
            iCur--;
            if(iCur < 0)
                iCur = iS -1;

            pW[iCur]->setFocus();
        }
        break;
    case PRS:
        if(iCur >= 0 && iCur < iS){
            if(DoPrs(pW[iCur],&PrsT)){
                pCW = pW[iCur];
                PrsT++;
            }else{
                pCW = NULL;
                PrsT = 0;
            }
        }
        break;
    default:
        break;
    }

    //printf("iCur:%d\n",iCur);
    //�л�TAB�ؼ�
    int iTab[] = {15,30,45,60,75,75+19,75+19+9};
    for(int i = 0; i < sizeof(iTab)/sizeof(int); i++){
        if(iCur < iTab[i]){
            if(i < 5){
                if(ui->tabW->currentIndex() != 0)
                    ui->tabW->setCurrentIndex(0);
                ui->tabW_sero->setCurrentIndex(i);
            }else{
                ui->tabW->setCurrentIndex(i - 5 + 1);
            }
            break;
        }
    }
    /*if(iCur < 5 * 15){
        ui->tabW->setCurrentIndex(0);
        ui->tabW_sero->setCurrentIndex(iCur / 15);
    }*/
}

//==========================================================================================
// End of file.
//==========================================================================================

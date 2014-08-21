/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_authority.cpp

* ��������: �û�������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include "dlg_authority.h"
#include "ui_dlg_authority.h"
#include "dlg_keyboard.h"
#include "twarn.h"
#include "tconfig.h"
#include "qa5driver.h"
#include "twidmana.h"
#include "tcmd.h"

/*************************************************************************
* ��������: Dlg_Authority
* ��   ��: ���캯��
* �������: QWidget *parent ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_Authority::Dlg_Authority(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Authority)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);


    TLineEdit *le[] = {ui->leLPsw,ui->leNPsw,ui->leOPsw,ui->leNPswA};
    for(int i = 0;i<sizeof(le)/sizeof(TLineEdit*);i++)
    {
        sglMapL.setMapping(le[i],i);
        connect(le[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_le_clicked(int)));

    QRadioButton* rb[] = {ui->rb1,ui->rb2,ui->rb3,ui->rb4,ui->rb5,ui->rb6};
    rb[usr.curUsr]->setChecked(true);
    rb[usr.curUsr + 3]->setChecked(true);

    ui->tabw->setCurrentIndex(0);

    a5drv.buzzer_off();

    widMana->bDialog = true;
}
/*************************************************************************
* ��������: Dlg_Authority
* ��   ��: ��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_Authority::~Dlg_Authority()
{
    delete ui;
}
/*************************************************************************
* ��������: on_btnOk_clicked
* ��   ��: ���ȷ����ť
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Authority::on_btnOk_clicked()
{
    //TUsr::CheckUsr(TUsr::Operator);
    int index = ui->tabw->currentIndex();
    if(index == 0){
        QString strP = ui->leLPsw->text();
        QRadioButton* rb[] = {ui->rb1,ui->rb2,ui->rb3};
        int iUsr = 0;
        for(iUsr = 0; iUsr < sizeof(rb)/sizeof(QRadioButton*); iUsr++){
            if(rb[iUsr]->isChecked())
                break;
        }

        QString str = QString("%1%2%3%4%5%6%7%8").arg((char)usr.usrP[iUsr].psw[0])
                                                 .arg((char)usr.usrP[iUsr].psw[1])
                                                 .arg((char)usr.usrP[iUsr].psw[2])
                                                 .arg((char)usr.usrP[iUsr].psw[3])
                                                 .arg((char)usr.usrP[iUsr].psw[4])
                                                 .arg((char)usr.usrP[iUsr].psw[5])
                                                 .arg((char)usr.usrP[iUsr].psw[6])
                                                 .arg((char)usr.usrP[iUsr].psw[7]);
        if(str == strP){
            usr.SetCurUsr((TUsr::USR)iUsr);
            config.SaveCfg();
            widMana->bDialog = false;
            QDialog::accept();
        }else{
            warn.ShowW2L(TWarn::W_PSW_ERR);
        }
    }else if(index == 1){
        QString strPO = ui->leOPsw->text();
        QString strPN = ui->leNPsw->text();
        QString strPNA = ui->leNPswA->text();

        QRadioButton* rb[] = {ui->rb4,ui->rb5,ui->rb6};
        int iUsr = 0;
        for(iUsr = 0; iUsr < sizeof(rb)/sizeof(QRadioButton*); iUsr++){
            if(rb[iUsr]->isChecked())
                break;
        }

        QString str = QString("%1%2%3%4%5%6%7%8").arg((char)usr.usrP[iUsr].psw[0])
                                                 .arg((char)usr.usrP[iUsr].psw[1])
                                                 .arg((char)usr.usrP[iUsr].psw[2])
                                                 .arg((char)usr.usrP[iUsr].psw[3])
                                                 .arg((char)usr.usrP[iUsr].psw[4])
                                                 .arg((char)usr.usrP[iUsr].psw[5])
                                                 .arg((char)usr.usrP[iUsr].psw[6])
                                                 .arg((char)usr.usrP[iUsr].psw[7]);

        if(str != strPO){
            warn.ShowW2L(TWarn::W_PSW_MERR1);
            //QDialog::reject();
        }else if(strPN != strPNA){
            warn.ShowW2L(TWarn::W_PSW_MERR2);
            //QDialog::reject();
        }else{
            for(int i = 0; i < 8; i++){
                usr.usrP[iUsr].psw[i] = strPN.at(i).toLatin1();
            }
            usr.SetCurUsr((TUsr::USR)iUsr);
            config.SaveCfg();
            widMana->bDialog = false;
            QDialog::accept();
        }
    }
}
/*************************************************************************
* ��������: on_btnCancel_clicked
* ��   ��: ���ȡ����ť
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Authority::on_btnCancel_clicked()
{
    widMana->bDialog = false;
    QDialog::reject();
}
/*************************************************************************
* ��������: on_le_clicked
* ��   ��: ����ı���
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Authority::on_le_clicked(int ile)
{
    Dlg_Keyboard dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        if(dlg.m_str.length() != 8){
            warn.ShowW2L(TWarn::W_PSW_INPUT);
            return;
        }
        TLineEdit *le[] = {ui->leLPsw,ui->leNPsw,ui->leOPsw,ui->leNPswA};
        le[ile]->setText(dlg.m_str);
    }
}
/*************************************************************************
* ��������: ModeCheck
* ��   ��: �жϲ���ģʽ���л�
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
bool ModeCheck(int modeC, ...)
{
    int *mode = (int*)((&modeC) + 1);
    for(int i = 0; i < modeC; i++){
        if(comF0.rpara.sub_sta == *(mode + i)){
            warn.ShowW2L(TWarn::W_MODE_CHANGE);
            return false;
        }
    }

    return true;
}

TUsr usr;

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_glbspd.cpp

* ��������: �Զ����Ǳ�ؼ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include <QtGui>

#include "dlg_glbspd.h"
#include "ui_dlg_glbspd.h"
#include "dashboard.h"
#include "dlg_psw.h"
#include "tcmd.h"
#include "twidmana.h"

/*************************************************************************
* ��������: Dlg_GlbSpd
* ��   ��: ���캯��
* �������: QWidget *parent ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_GlbSpd::Dlg_GlbSpd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_GlbSpd),
    mVal(0.0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->leGlbSpd->setText(QString("%1").arg(com02.para[0].whlvel));

    //Dashboard board(ui->spdWidget);
    mBoard = new Dashboard(ui->spdWidget);
    connect(ui->leGlbSpd, SIGNAL(textChanged(QString)), mBoard, SLOT(setHand(QString)));
    //connect(ui->btnAdd, SIGNAL(clicked()), mBoard, SLOT(setHand(QString)));
    mBoard->show();
    mBoard->setHand(ui->leGlbSpd->text());

    widMana->bDialog = true;
}
/*************************************************************************
* ��������: Dlg_GlbSpd
* ��   ��: ��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_GlbSpd::~Dlg_GlbSpd()
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
void Dlg_GlbSpd::on_btnOk_clicked()
{
    for(int i = 0; i < 5; i++)
        com02.para[0].whlvel = ui->leGlbSpd->text().toInt();
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)&com02);

    widMana->SavePara();
    widMana->InitParaUI();

    widMana->bDialog = false;
    QDialog::accept();
}
/*************************************************************************
* ��������: on_btnCancel_clicked
* ��   ��: ���ȡ����ť
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_GlbSpd::on_btnCancel_clicked()
{
    widMana->bDialog = false;
    QDialog::reject();
}
/*************************************************************************
* ��������: on_btnAdd_clicked
* ��   ��: ����ָ��
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_GlbSpd::on_btnAdd_clicked()
{
    mVal = ui->leGlbSpd->text().toInt();
    mVal++;
    if (mVal > 100)
        mVal = 100;
    //mVal++;
    ui->leGlbSpd->setText(QString::number(mVal));

    //qDebug() << QString::number(mVal);
}
/*************************************************************************
* ��������: on_btnSub_clicked
* ��   ��: ����ָ��
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_GlbSpd::on_btnSub_clicked()
{
    mVal = ui->leGlbSpd->text().toInt();

    mVal--;
    if (mVal < 0)
        mVal = 0;
    //mVal--;
    ui->leGlbSpd->setText(QString::number(mVal));
    //qDebug() << QString::number(mVal);
}
/*************************************************************************
* ��������: on_leGlbSpd_clicked
* ��   ��: ����ı�������ָ��ֵ
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_GlbSpd::on_leGlbSpd_clicked()
{
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec()==QDialog::Accepted)
    {
        if(dlg.m_str.toInt() > 100)
            return;

        ui->leGlbSpd->setText(dlg.m_str);
    }
}

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_reset.cpp

* ��������: ��λ����

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include "dlg_reset.h"
#include "ui_dlg_reset.h"
#include "twidmana.h"
#include "tcmd.h"

#include <QTimer>


/*************************************************************************
* ��������: Dlg_Reset
* ��   ��: ���캯��
* �������: QWidget *parent ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_Reset::Dlg_Reset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Reset)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    widMana->bDialog = true;
}
/*************************************************************************
* ��������: Dlg_Reset
* ��   ��: ��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_Reset::~Dlg_Reset()
{
    delete ui;
}
/*************************************************************************
* ��������: on_btnOK_clicked
* ��   ��: ��ʼ��λ
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Reset::on_btnOK_clicked()
{
    QMutexLocker locker(&mutex_com);
    memset(&comE0.para,sizeof(comE0.para),0);
    comE0.para.runtype  = TComE0::REST;
    pComBuf2.push_back((TCom*)&comE0);


    QTimer *timer = new QTimer(this);
    timer->start(1000);//һ����
    connect(timer,SIGNAL(timeout()),this,SLOT(UpdateSet()));
}
/*************************************************************************
* ��������: UpdateSet
* ��    ��: ���¸�λ��ʾ
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Reset::UpdateSet()
{
    static int iT = 0;
    QString strT = QObject::tr("��λ�У����Ժ�");
    for(int i = 0; i < iT; i++){
        strT += QString(".");
    }
    ui->lblT->setText(strT);

    iT++;
    iT%=6;

    if(chkRstOK()){
        QDialog::accept();

        widMana->bDialog = false;
    }
}
/*************************************************************************
* ��������: chkRstOK
* ��    ��: �жϸ�λ�Ƿ�ɹ�
* �������: ��
* �������: ��
* �� �� ֵ: true �ɹ��� false ʧ��
*************************************************************************/
bool Dlg_Reset::chkRstOK()
{
    /*quint8 axisp[] = {com02.para[0].axisp,com02.para[1].axisp,com02.para[2].axisp,
                      com02.para[3].axisp,com02.para[4].axisp};
    quint32 pos[] = {comF0.rpara.xpos,comF0.rpara.y1pos,comF0.rpara.z1pos,
                    comF0.rpara.y2pos,comF0.rpara.z2pos};

    for(int i = 0; i < sizeof(axisp)/sizeof(quint8); i++){
        if((axisp[i] == TCom02::ENABLE) && (pos[i] != 0)){
            return false;
        }
    }*/
    if(comF0.rpara.sub_sta == TComF0::IDLE)
        return true;
    else
        return false;
}
/*************************************************************************
* ��������: on_btnQuit_clicked
* ��   ��: ȡ����λ����
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Reset::on_btnQuit_clicked()
{
    QDialog::reject();
    widMana->bDialog = false;

    QMutexLocker locker(&mutex_com);
    memset(&comE0.para,sizeof(comE0.para),0);
    comE0.para.runtype  = TComE0::STOP;
    pComBuf2.push_back((TCom*)&comE0);
}

//==========================================================================================
// End of file.
//==========================================================================================

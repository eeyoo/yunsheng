/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_mana.cpp

* ��������: �ֶ����л���

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/


#include "frm_mana.h"
#include "ui_frm_mana.h"
#include "tcmd.h"
/*************************************************************************
* ��������: Frm_Mana
* ��    ��: ���캯��
* �������: 
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Mana::Frm_Mana() :
    
    ui(new Ui::Frm_Mana)
{
    ui->setupUi(this);
    //setAutoFillBackground(true);

    InitRbSig();
    InitCbSig();
}
/*************************************************************************
* ��������: ~Frm_Mana
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Mana::~Frm_Mana()
{
    delete ui;
}
/*************************************************************************
* ��������: InitRbSig
* ��    ��: ��ʼ��QRadioButton��Ϣ����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Mana::InitRbSig()
{
    QRadioButton *rb[] = {ui->rb1,ui->rb2,ui->rb3,ui->rb4,ui->rb5,ui->rb6,ui->rb7};
    for(int i = 0;i<sizeof(rb)/sizeof(QRadioButton*);i++)
    {
        sglMapRb.setMapping(rb[i],i);
        connect(rb[i], SIGNAL(clicked()), &sglMapRb, SLOT(map()));
    }
    connect(&sglMapRb,SIGNAL(mapped(int)),this,SLOT(on_rb_clicked(int)));
}
/*************************************************************************
* ��������: InitCbSig
* ��    ��: ��ʼ��QCheckBox��Ϣ����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Mana::InitCbSig()
{
    QCheckBox *cb[] = {ui->cb1,ui->cb2,ui->cb3,ui->cb4,ui->cb5,ui->cb6,
                        ui->cb7,ui->cb8,ui->cb9,ui->cb10,ui->cb11};
    for(int i = 0;i<sizeof(cb)/sizeof(QCheckBox*);i++)
    {
        sglMapCb.setMapping(cb[i],i);
        connect(cb[i], SIGNAL(clicked()), &sglMapCb, SLOT(map()));
    }
    connect(&sglMapCb,SIGNAL(mapped(int)),this,SLOT(on_cb_clicked(int)));
}
/*************************************************************************
* ��������: on_rb_clicked
* ��    ��: ��ӦQRadioButton����¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Mana::on_rb_clicked(int irb)
{
    QRadioButton *rb[] = {ui->rb1,ui->rb2,ui->rb3,ui->rb4,ui->rb5,ui->rb6,ui->rb7};
    if(rb[irb]->isChecked())
    {
        iCurCmd = irb;
    }
}
/*************************************************************************
* ��������: on_cb_clicked
* ��    ��: ��ӦQCheckBox����¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Mana::on_cb_clicked(int icb)
{
    QCheckBox *cb[] = {ui->cb1,ui->cb2,ui->cb3,ui->cb4,ui->cb5,ui->cb6,
                        ui->cb7,ui->cb8,ui->cb9,ui->cb10,ui->cb11};
    //cmd_Out->para.action = TCmd::ROT+icb;
    cmd_Out->para.dist    = cb[icb]->checkState()?1:0;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)cmd_Out);
}

//==========================================================================================
// End of file.
//==========================================================================================

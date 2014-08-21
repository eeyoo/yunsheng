/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_psw.cpp

* ��������: ���ּ����ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#include "dlg_psw.h"
#include "ui_dlg_psw.h"
#include "qa5driver.h"
#include "twidmana.h"
/*************************************************************************
* ��������: Dlg_Psw
* ��    ��: ���캯������ʼ��QPushButton��Ϣ����
* �������: QWidget *parent
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_Psw::Dlg_Psw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Psw)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    QPushButton *btn[] = {ui->btn46,ui->btn48,ui->btn49,ui->btn50,ui->btn51,
                        ui->btn52,ui->btn53,ui->btn54,ui->btn55,ui->btn56,ui->btn57};
    for(int i = 0;i<sizeof(btn)/sizeof(QPushButton*);i++)
    {
        sglMapL.setMapping(btn[i],i);
        connect(btn[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_btn_clicked(int)));

    a5drv.buzzer_off();
    widMana->bDialog = true;
}
/*************************************************************************
* ��������: ~Dlg_Psw
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_Psw::~Dlg_Psw()
{
    delete ui;
}
/*************************************************************************
* ��������: on_btn_clicked
* ��    ��: ��ӦQPushButton����¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Psw::on_btn_clicked(int ibtn)
{
    QPushButton *btn[] = {ui->btn46,ui->btn48,ui->btn49,ui->btn50,ui->btn51,
                        ui->btn52,ui->btn53,ui->btn54,ui->btn55,ui->btn56,ui->btn57};
    QString strBtn = btn[ibtn]->objectName();
    strBtn = strBtn.right(strBtn.length()-3);

    quint8 asc = (quint8)strBtn.toInt();
    m_str = ui->le_input->text();
    m_str += asc;

    ui->le_input->setText(m_str);
}
/*************************************************************************
* ��������: on_btnOK_K_clicked
* ��    ��: ���ȷ����ť���˳�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Psw::on_btnOK_K_clicked()
{
    widMana->bDialog = false;
    QDialog::accept();
}
/*************************************************************************
* ��������: on_btnQuit_K_clicked
* ��    ��: ����˳���ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Psw::on_btnQuit_K_clicked()
{
    widMana->bDialog = false;
    QDialog::reject();
}
/*************************************************************************
* ��������: on_btnBack_clicked
* ��    ��: ����˸�ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Psw::on_btnBack_clicked()
{
    m_str = ui->le_input->text();
    m_str = m_str.left(m_str.length()-1);
    ui->le_input->setText(m_str);
}

//==========================================================================================
// End of file.
//==========================================================================================

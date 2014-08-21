/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_keyboard.cpp

* ��������: �Զ�������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include "dlg_keyboard.h"
#include "ui_dlg_keyboard.h"
#include "qa5driver.h"
#include "twidmana.h"

/*************************************************************************
* ��������: Dlg_Keyboard
* ��   ��: ���캯��
* �������: QWidget *parent ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_Keyboard::Dlg_Keyboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Keyboard)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    QPushButton *btn[] = {ui->btn48,ui->btn49,ui->btn50,ui->btn51,ui->btn52,ui->btn53,ui->btn54,
                          ui->btn55,ui->btn56,ui->btn57,ui->btn97,ui->btn98,ui->btn99,ui->btn100,
                          ui->btn101,ui->btn102,ui->btn103,ui->btn104,ui->btn105,ui->btn106,ui->btn107,
                          ui->btn108,ui->btn109,ui->btn110,ui->btn111,ui->btn112,ui->btn113,ui->btn114,
                          ui->btn115,ui->btn116,ui->btn117,ui->btn118,ui->btn119,ui->btn120,ui->btn121,
                          ui->btn122,ui->btn43,ui->btn45,ui->btn42,ui->btn47,ui->btn32,ui->btn40,
                          ui->btn59,ui->btn41,ui->btn46,ui->btn33,ui->btn63};
    for(int i = 0;i<sizeof(btn)/sizeof(QPushButton*);i++)
    {
        sglMapL.setMapping(btn[i],i);
        connect(btn[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_btn_clicked(int)));

    setFocusPolicy(Qt::NoFocus);

    a5drv.buzzer_off();

    widMana->bDialog = true;

    ui->btnShift->setText(ui->btnShift->isChecked() ? QString("ABC") : QString("abc"));
}
/*************************************************************************
* ��������: Dlg_Keyboard
* ��   ��: ��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_Keyboard::~Dlg_Keyboard()
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
void Dlg_Keyboard::on_btn_clicked(int ibtn)
{
    QPushButton *btn[] = {ui->btn48,ui->btn49,ui->btn50,ui->btn51,ui->btn52,ui->btn53,ui->btn54,
                          ui->btn55,ui->btn56,ui->btn57,ui->btn97,ui->btn98,ui->btn99,ui->btn100,
                          ui->btn101,ui->btn102,ui->btn103,ui->btn104,ui->btn105,ui->btn106,ui->btn107,
                          ui->btn108,ui->btn109,ui->btn110,ui->btn111,ui->btn112,ui->btn113,ui->btn114,
                          ui->btn115,ui->btn116,ui->btn117,ui->btn118,ui->btn119,ui->btn120,ui->btn121,
                          ui->btn122,ui->btn43,ui->btn45,ui->btn42,ui->btn47,ui->btn32,ui->btn40,
                          ui->btn59,ui->btn41,ui->btn46,ui->btn33,ui->btn63};

    QString strBtn = btn[ibtn]->objectName();
    strBtn = strBtn.right(strBtn.length()-3);

    quint8 asc = (quint8)strBtn.toInt();
    if(ui->btnShift->isChecked())
    {
        if(asc >= 'a'&&asc <= 'z')
            asc -= 32;
    }

    m_str = ui->le_input->text();
    m_str += asc;

    ui->le_input->setText(m_str);
}
/*************************************************************************
* ��������: on_btnBack_clicked
* ��   ��: ����˸��
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Keyboard::on_btnBack_clicked()
{
    m_str = ui->le_input->text();
    m_str = m_str.left(m_str.length()-1);
    ui->le_input->setText(m_str);
}
/*************************************************************************
* ��������: on_btnQuit_clicked
* ��   ��: ����˳�
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Keyboard::on_btnQuit_clicked()
{
    widMana->bDialog = false;
    QDialog::reject();
}
/*************************************************************************
* ��������: on_btnEnter_clicked
* ��   ��: ���ȷ����ť
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Keyboard::on_btnEnter_clicked()
{
    widMana->bDialog = false;
    QDialog::accept();
}
/*************************************************************************
* ��������: on_btnShift_clicked
* ��   ��: �л���Сд
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Keyboard::on_btnShift_clicked()
{
    QPushButton *btn[] = {ui->btn97,ui->btn98,ui->btn99,ui->btn100,
                          ui->btn101,ui->btn102,ui->btn103,ui->btn104,ui->btn105,ui->btn106,ui->btn107,
                          ui->btn108,ui->btn109,ui->btn110,ui->btn111,ui->btn112,ui->btn113,ui->btn114,
                          ui->btn115,ui->btn116,ui->btn117,ui->btn118,ui->btn119,ui->btn120,ui->btn121,
                          ui->btn122};

    for(int i = 0;i<sizeof(btn)/sizeof(QPushButton*);i++)
    {
        QString strT(ui->btnShift->isChecked()?('A'+(char)i):('a'+(char)i));
        btn[i]->setText(strT);
    }

    ui->btnShift->setText(ui->btnShift->isChecked() ? QString("ABC") : QString("abc"));
}

//==========================================================================================
// End of file.
//==========================================================================================

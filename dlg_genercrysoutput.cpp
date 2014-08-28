/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_genercrysoutput.cpp

* ��������: �������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.8.20

* ��	��:
**************************************************************************************/

#include "dlg_genercrysoutput.h"
#include "ui_dlg_genercrysoutput.h"
#include "twidmana.h"
#include "qa5driver.h"

/*************************************************************************
* ��������: Dlg_GenerCrysOutput
* ��   ��: ���캯��
* �������: QWidget *parent ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_GenerCrysOutput::Dlg_GenerCrysOutput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_GenerCrysOutput)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    a5drv.buzzer_off();

    QPushButton *btn[] = {ui->O9,ui->O10,ui->O11,ui->O12,ui->O13,ui->O14,ui->O15,ui->O16,
                          ui->O17,ui->O18,ui->O19,ui->O20,ui->O21,ui->O22,ui->O23,ui->O24,
                          ui->O25,ui->O26};
    for(int i = 0;i<sizeof(btn)/sizeof(QPushButton*);i++)
    {
        sglMapL.setMapping(btn[i],i);
        connect(btn[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));

        if((i + 8) < readCmd.CmdO.size()){
            btn[i]->setText(readCmd.CmdO[i + 8].cmdTil);
        }
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_btn_clicked(int)));

    widMana->bDialog = true;
}
/*************************************************************************
* ��������: Dlg_GenerCrysOutput
* ��   ��: ��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_GenerCrysOutput::~Dlg_GenerCrysOutput()
{
    widMana->bDialog = false;
    delete ui;
}
/*************************************************************************
* ��������: on_btn_clicked
* ��    ��: ��ӦQPushButton����¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_GenerCrysOutput::on_btn_clicked(int ibtn)
{
    QPushButton *btn[] = {ui->O9,ui->O10,ui->O11,ui->O12,ui->O13,ui->O14,ui->O15,ui->O16,
                          ui->O17,ui->O18,ui->O19,ui->O20,ui->O21,ui->O22,ui->O23,ui->O24,
                          ui->O25,ui->O26};

    QString strBtn = btn[ibtn]->objectName();
    strBtn = strBtn.right(strBtn.length()-1);
    iO = strBtn.toInt() - 1;

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
void Dlg_GenerCrysOutput::on_btnCancel_clicked()
{
    QDialog::reject();
}
/*************************************************************************
* ��������: on_btnOk_clicked
* ��   ��: ���ȷ����ť
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_GenerCrysOutput::on_btnOk_clicked()
{
    QDialog::reject();
}

//==========================================================================================
// End of file.
//==========================================================================================

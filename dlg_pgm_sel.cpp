/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_pgm_sel.cpp

* ��������: ����ѡ���ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#include "dlg_pgm_sel.h"
#include "ui_dlg_pgm_sel.h"

/*************************************************************************
* ��������: Dlg_Pgm_Sel
* ��   ��: ���캯������ʼ��tableWidget�ؼ�
* �������: QWidget *parent
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_Pgm_Sel::Dlg_Pgm_Sel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Pgm_Sel)
{
    ui->setupUi(this);

    QString strP[] = {
        QObject::tr("YS001"),QObject::tr("YS002"),QObject::tr("YS003"),QObject::tr("YS004"),
        QObject::tr("YS005"),QObject::tr("YS006"),QObject::tr("YS007"),QObject::tr("YS008"),
        QObject::tr("YS009"),QObject::tr("YS010"),QObject::tr("YS011"),QObject::tr("YS012"),
        QObject::tr("YS013"),QObject::tr("YS014"),QObject::tr("YS015"),QObject::tr("YS016"),
        QObject::tr("YS017"),QObject::tr("YS018"),QObject::tr("YS019"),QObject::tr("YS020"),
        QObject::tr("YS021"),QObject::tr("YS022"),QObject::tr("YS023"),QObject::tr("YS024"),
        QObject::tr("YS025"),QObject::tr("YS026"),QObject::tr("YS027"),QObject::tr("YS028"),
        QObject::tr("YS029"),QObject::tr("YS030"),QObject::tr("YS031"),QObject::tr("YS032"),
        QObject::tr("YS033"),QObject::tr("YS034"),QObject::tr("YS035"),QObject::tr("YS036"),
        QObject::tr("YS037"),QObject::tr("YS038"),QObject::tr("YS039"),QObject::tr("YS040"),
        QObject::tr("YS041"),QObject::tr("YS042"),QObject::tr("YS043"),QObject::tr("YS044"),
        QObject::tr("YS045"),QObject::tr("YS046"),QObject::tr("YS047"),QObject::tr("YS048"),
        QObject::tr("YS049"),QObject::tr("YS050"),
    };
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(50);
    ui->tableWidget->setColumnWidth(0,140);
    ui->tableWidget->horizontalHeader()->hide();
    for(int i = 0;i<50;i++)
    {
        QTableWidgetItem *itemPN = new QTableWidgetItem(strP[i]);
        ui->tableWidget->setItem(i,0,itemPN);
        ui->tableWidget->setRowHeight(i,50);
    }
}
/*************************************************************************
* ��������: ~Dlg_Pgm_Sel
* ��   ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_Pgm_Sel::~Dlg_Pgm_Sel()
{
    delete ui;
}
/*************************************************************************
* ��������: on_btnOK_clicked
* ��    ��: ���ȷ����ť
* �������: QWidget *parent
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Pgm_Sel::on_btnOK_clicked()
{
    m_iPgm = ui->tableWidget->currentRow();

    QDialog::accept();
}
/*************************************************************************
* ��������: on_btnCan_clicked
* ��    ��: ����˳���ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_Pgm_Sel::on_btnCan_clicked()
{
    QDialog::reject();
}

//==========================================================================================
// End of file.
//==========================================================================================

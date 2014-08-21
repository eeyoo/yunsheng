/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: Dlg_StackManage.cpp

* ��������: �ѵ�����������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include "dlg_stackmanage.h"
#include "ui_dlg_stackmanage.h"
#include "twidmana.h"

#include <QFile>
#include <QDir>
#include <QDateTime>

/*************************************************************************
* ��������: Dlg_StackManage
* ��   ��: ���캯��
* �������: QWidget *parent ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_StackManage::Dlg_StackManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_StackManage)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->tblWStkM->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblWStkM->setColumnCount(3);
    //ui->tblWStkM->setRowCount(4);
    ui->tblWStkM->setColumnWidth(0,100);
    ui->tblWStkM->setColumnWidth(1,80);
    ui->tblWStkM->setColumnWidth(2,200);
    QStringList header;
    header.append(QObject::tr("������"));
    header.append(QObject::tr("��С"));
    header.append(QObject::tr("����ʱ��"));
    ui->tblWStkM->setHorizontalHeaderLabels(header);

    SearchFile();
}
/*************************************************************************
* ��������: Dlg_StackManage
* ��   ��: ��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Dlg_StackManage::~Dlg_StackManage()
{
    delete ui;
}
/*************************************************************************
* ��������: SearchFile
* ��    ��: �����ļ����е��ļ�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_StackManage::SearchFile()
{
    QDir dir(widMana->strStkP);
    if(!dir.exists())
    {
        return;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();

    int file_count = list.count();
    if(file_count <= 0)
    {
        return;
    }

    QStringList string_list;
    for(int i=0; i<file_count;i++)
    {
        QFileInfo file_info = list.at(i);
        QString suffix = file_info.suffix();
        if(QString::compare(suffix, QString("stk"), Qt::CaseInsensitive) == 0)
        {
            //QString absolute_file_path = file_info.absoluteFilePath();
            //string_list.append(absolute_file_path);
            QString strN = file_info.fileName();


            QString strS = QString("%1bytes").arg(file_info.size());
            QDateTime dt = file_info.created();
            QString strD = QString("%1-%2-%3 %4:%5:%6")
                           .arg(dt.date().year()).arg(dt.date().month()).arg(dt.date().day())
                           .arg(dt.time().hour()).arg(dt.time().minute()).arg(dt.time().second());

            QTableWidgetItem *proN=new QTableWidgetItem(strN);
            QTableWidgetItem *proS=new QTableWidgetItem(strS);
            QTableWidgetItem *proD=new QTableWidgetItem(strD);

            ui->tblWStkM->insertRow(i);
            ui->tblWStkM->setItem(i,0,proN);
            ui->tblWStkM->setItem(i,1,proS);
            ui->tblWStkM->setItem(i,2,proD);
        }
    }
}
/*************************************************************************
* ��������: on_btnOK_clicked
* ��    ��: ���ȷ����ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_StackManage::on_btnOK_clicked()
{
    //��ȡ������
    QModelIndex       index = ui->tblWStkM->currentIndex();
    if(!index.isValid())
        QDialog::reject();

    QTableWidgetItem *item  = ui->tblWStkM->item(index.row(),0);
    m_strN  = item->text();

    QDialog::accept();
}
/*************************************************************************
* ��������: on_btnCancel_clicked
* ��    ��: ���ȡ����ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Dlg_StackManage::on_btnCancel_clicked()
{
    QDialog::reject();
}

//==========================================================================================
// End of file.
//==========================================================================================

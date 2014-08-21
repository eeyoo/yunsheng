/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_manufacturer.cpp

* ��������: �������û���

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include <QProcess>
#include <QDir>
#include <QFileInfoList>
#include <QDateTime>

#include "frm_manufacturer.h"
#include "ui_frm_manufacturer.h"
#include "qa5driver.h"

/*************************************************************************
* ��������: Frm_Manufacturer
* ��   ��: ���캯��
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Manufacturer::Frm_Manufacturer() :
    
    ui(new Ui::Frm_Manufacturer)
{
    ui->setupUi(this);

    ui->tblUpdate->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblUpdate->setColumnCount(3);
    //ui->tblPgm->setRowCount(4);
    ui->tblUpdate->setColumnWidth(0,200);
    ui->tblUpdate->setColumnWidth(1,100);
    ui->tblUpdate->setColumnWidth(2,300);
    QStringList header;
    header.append(QObject::tr("������"));
    header.append(QObject::tr("��С"));
    header.append(QObject::tr("����ʱ��"));
    ui->tblUpdate->setHorizontalHeaderLabels(header);




}
/*************************************************************************
* ��������: Frm_Manufacturer
* ��   ��: ��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Manufacturer::~Frm_Manufacturer()
{
    delete ui;
}
/*************************************************************************
* ��������: on_btnReboot_clicked
* ��   ��: ����ϵͳ
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Manufacturer::on_btnReboot_clicked()
{
#ifdef EMBEDED_ARM
    QProcess::execute("/root/reboot");
#endif
}
/*************************************************************************
* ��������: on_btnRelad_clicked
* ��   ��: ����U�̳���
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Manufacturer::on_btnRelad_clicked()
{
#ifdef EMBEDED_ARM
    QDir dir("/media/sda1/YsRobot");
#else
    QDir dir("F://YsRobot//YsRobot");
#endif

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
        //QString suffix = file_info.suffix();
        //if(QString::compare(suffix, QString("pgm"), Qt::CaseInsensitive) == 0)
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

            ui->tblUpdate->insertRow(i);
            ui->tblUpdate->setItem(i,0,proN);
            ui->tblUpdate->setItem(i,1,proS);
            ui->tblUpdate->setItem(i,2,proD);
        }
    }
}
/*************************************************************************
* ��������: on_btnUpd_clicked
* ��   ��: ����ϵͳ
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Manufacturer::on_btnUpd_clicked()
{
#ifdef EMBEDED_ARM
    //��ȡ������
    QModelIndex       index = ui->tblUpdate->currentIndex();
    if(!index.isValid())
        return;
    QTableWidgetItem *item  = ui->tblUpdate->item(index.row(),0);
    QString           strN  = item->text();

    if(QFile::copy(QString("/media/sda1/YsRobot/%1").arg(strN),
                   QString("/root/YsRobotND-1")))
    {
        system("sync");
        system("reboot");
    }
#endif
}
/*************************************************************************
* ��������: on_btnRecov_clicked
* ��   ��: �ָ�ϵͳ
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Manufacturer::on_btnRecov_clicked()
{
#ifdef EMBEDED_ARM
    if(QFile::copy(QString("/root/YsRobotND-2"),
                   QString("/root/YsRobotND-1")))
    {
        system("sync");
        system("reboot");
    }
#endif
}

//==========================================================================================
// End of file.
//==========================================================================================

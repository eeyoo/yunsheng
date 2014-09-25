/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: analogclock.cpp

* ��������: �Զ����ӱ�ؼ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include "frm_prom.h"
#include "ui_frm_prom.h"
#include "twidmana.h"
#include "dlg_keyboard.h"
#include "tcom.h"
#include "dlg_authority.h"


#include <QDir>
#include <QDateTime>
#include <QModelIndex>

/*************************************************************************
* ��������: Frm_ProM
* ��   ��: ���캯��
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_ProM::Frm_ProM() :
    
    ui(new Ui::Frm_ProM)
{
    ui->setupUi(this);

    ui->tblPgm->setSelectionBehavior(QAbstractItemView::SelectRows); // ��������ѡ��
    ui->tblPgm->horizontalHeader()->setStretchLastSection(true); // ���ó������
    ui->tblPgm->setEditTriggers(QAbstractItemView::NoEditTriggers); // ���ֻ��
    ui->tblPgm->setShowGrid(false); // ���ر����
    ui->tblPgm->setAlternatingRowColors(true); // ʹ�ܽ��汳��ɫ

    ui->tblPgm->setColumnCount(3);
    //ui->tblPgm->setRowCount(4);
    ui->tblPgm->setColumnWidth(0,200);
    ui->tblPgm->setColumnWidth(1,100);
    ui->tblPgm->setColumnWidth(2,300);
    //ui->tableWidget->horizontalHeader()->hide();
    QStringList header;
    header.append(QObject::tr("������"));
    header.append(QObject::tr("��С"));
    header.append(QObject::tr("����ʱ��"));
    ui->tblPgm->setHorizontalHeaderLabels(header);
    /*for(int i=0;i<4;i++)
    {
        QString strN=QString("program%1").arg(i);
        QString strS=QString("%1bytes").arg(i*200+30);
        QString strD("2014-2-26");
        QTableWidgetItem *proN=new QTableWidgetItem(strN);
        QTableWidgetItem *proS=new QTableWidgetItem(strS);
        QTableWidgetItem *proD=new QTableWidgetItem(strD);
        ui->tableWidget->setItem(i,0,proN);
        ui->tableWidget->setItem(i,1,proS);
        ui->tableWidget->setItem(i,2,proD);
    }*/
}
/*************************************************************************
* ��������: Frm_ProM
* ��   ��: ��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_ProM::~Frm_ProM()
{
    delete ui;
}
/*************************************************************************
* ��������: on_btnNew_clicked
* ��   ��: �½�����
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_ProM::on_btnNew_clicked()
{
    if(!usr.CheckUsr(TUsr::Administrator))
        return;

    Dlg_Keyboard dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        com20.NewPgm();
        widMana->ShowPgmN(dlg.m_str);
        widMana->SwitchWM(&widMana->frm_teach);
    }
}
/*************************************************************************
* ��������: on_btnOpen_clicked
* ��   ��: �򿪳���
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_ProM::on_btnOpen_clicked()
{
    if(!usr.CheckUsr(TUsr::Operator))
        return;

    if(OnOpen())
        widMana->SwitchWM(&widMana->frm_run);
}
/*************************************************************************
* ��������: on_btnEdit_clicked
* ��   ��: �༭����
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_ProM::on_btnEdit_clicked()
{
    if(!usr.CheckUsr(TUsr::Administrator))
        return;

    if(OnOpen()||!widMana->strFileN.isEmpty()){
        widMana->SwitchWM(&widMana->frm_teach);
    }
}
/*************************************************************************
* ��������: OnOpen
* ��    ��: ��ʾ�̳���
* �������: ��
* �������: ��
* �� �� ֵ: true�򿪳ɹ� false��ʧ��
*************************************************************************/
bool Frm_ProM::OnOpen()
{
    //��ȡ������
    QModelIndex       index = ui->tblPgm->currentIndex();
    if(!index.isValid())
        return false;
    QTableWidgetItem *item  = ui->tblPgm->item(index.row(),0);
    QString           strN  = item->text();

    strN = strN.left(strN.length()-4);


    //�򿪳����ļ�
    QFile *file  =  new QFile();
    file->setFileName(QString("%1/%2.pgm")
                      .arg(widMana->strPgm).arg(strN));
    if(!file->open(QIODevice::ReadOnly))
        return false;
    file->reset();

    com20.OpenPgm(file);

    file->close();
    file->deleteLater();

    widMana->ShowPgmN(strN);

    return true;
}
/*************************************************************************
* ��������: setVisible
* ��    ��: ��ʼ��������ʾ�����ó����еĿ��
* �������: visible	true��ʾ��false����
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_ProM::setVisible(bool visible)
{
    QWidget::setVisible(visible);

    if(visible)
    {

        ui->tblPgm->setRowCount(0);
        SearchFile();
    }
}
/*************************************************************************
* ��������: SearchFile
* ��    ��: �����ļ����е��ļ�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_ProM::SearchFile()
{
    QDir dir(widMana->strPgm);
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
        if(QString::compare(suffix, QString("pgm"), Qt::CaseInsensitive) == 0)
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

            ui->tblPgm->insertRow(i);
            ui->tblPgm->setItem(i,0,proN);
            ui->tblPgm->setItem(i,1,proS);
            ui->tblPgm->setItem(i,2,proD);
        }
    }
}
/*************************************************************************
* ��������: on_btnRen_clicked
* ��   ��: ����������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_ProM::on_btnRen_clicked()
{
    if(!usr.CheckUsr(TUsr::Administrator))
        return;

    Dlg_Keyboard dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        //��ȡ������
        QModelIndex       index = ui->tblPgm->currentIndex();
        if(!index.isValid())
            return;
        QTableWidgetItem *item  = ui->tblPgm->item(index.row(),0);
        QString           strN  = item->text();

        if(QFile::rename(QString("%1/%2").arg(widMana->strPgm).arg(strN),
                      QString("%1/%2.pgm").arg(widMana->strPgm).arg(dlg.m_str)))
        {
            item->setText(QString("%1.pgm").arg(dlg.m_str));

            #ifdef EMBEDED_ARM
                system("sync");
            #endif
        }
    }
}
/*************************************************************************
* ��������: on_btnSveA_clicked
* ��   ��: ���Ϊ����
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_ProM::on_btnSveA_clicked()
{
    if(!usr.CheckUsr(TUsr::Administrator))
        return;

    Dlg_Keyboard dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        //��ȡ������
        QModelIndex       index = ui->tblPgm->currentIndex();
        if(!index.isValid())
            return;
        QTableWidgetItem *item  = ui->tblPgm->item(index.row(),0);
        QString           strN  = item->text();

        if(QFile::copy(QString("%1/%2").arg(widMana->strPgm).arg(strN),
                      QString("%1/%2.pgm").arg(widMana->strPgm).arg(dlg.m_str)))
        {
            QFileInfo file_info(QDir(QString("%1/%2.pgm").arg(widMana->strPgm).arg(dlg.m_str)),QString(""));
            QString strNC = file_info.fileName();


            QString strSC = QString("%1bytes").arg(file_info.size());
            QDateTime dt  = file_info.created();
            QString strDC = QString("%1-%2-%3 %4:%5:%6")
                           .arg(dt.date().year()).arg(dt.date().month()).arg(dt.date().day())
                           .arg(dt.time().hour()).arg(dt.time().minute()).arg(dt.time().second());

            QTableWidgetItem *proN=new QTableWidgetItem(strNC);
            QTableWidgetItem *proS=new QTableWidgetItem(strSC);
            QTableWidgetItem *proD=new QTableWidgetItem(strDC);

            ui->tblPgm->insertRow(index.row()+1);
            ui->tblPgm->setItem(index.row()+1,0,proN);
            ui->tblPgm->setItem(index.row()+1,1,proS);
            ui->tblPgm->setItem(index.row()+1,2,proD);
            ui->tblPgm->selectRow(index.row()+1);

            #ifdef EMBEDED_ARM
                system("sync");
            #endif
        }
    }
}
/*************************************************************************
* ��������: on_btnDel_clicked
* ��   ��: ɾ������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_ProM::on_btnDel_clicked()
{
    if(!usr.CheckUsr(TUsr::Administrator))
        return;

    //��ȡ������
    QModelIndex       index = ui->tblPgm->currentIndex();
    if(!index.isValid())
        return;
    QTableWidgetItem *item  = ui->tblPgm->item(index.row(),0);
    QString           strN  = item->text();

    if(QFile::remove(QString("%1/%2").arg(widMana->strPgm).arg(strN)))
    {
        ui->tblPgm->removeRow(index.row());
        ui->tblPgm->selectRow(index.row());

        #ifdef EMBEDED_ARM
            system("sync");
        #endif
    }
}
/*************************************************************************
* ��������: on_btnIm_clicked
* ��   ��: �������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_ProM::on_btnIm_clicked()
{
    if(!usr.CheckUsr(TUsr::Administrator))
        return;

#ifdef EMBEDED_ARM
    Dlg_Keyboard dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        if(QFile::copy(QString("/media/sda1/%1.pgm").arg(dlg.m_str),
                       QString("%1/%2.pgm").arg(widMana->strPgm).arg(dlg.m_str)))
        {
            QFileInfo file_info(QDir(QString("%1/%2.pgm").arg(widMana->strPgm).arg(dlg.m_str)),QString(""));
            QString strNC = file_info.fileName();


            QString strSC = QString("%1bytes").arg(file_info.size());
            QDateTime dt  = file_info.created();
            QString strDC = QString("%1-%2-%3 %4:%5:%6")
                           .arg(dt.date().year()).arg(dt.date().month()).arg(dt.date().day())
                           .arg(dt.time().hour()).arg(dt.time().minute()).arg(dt.time().second());

            QTableWidgetItem *proN=new QTableWidgetItem(strNC);
            QTableWidgetItem *proS=new QTableWidgetItem(strSC);
            QTableWidgetItem *proD=new QTableWidgetItem(strDC);

            int rc = ui->tblPgm->rowCount();
            ui->tblPgm->insertRow(rc+1);
            ui->tblPgm->setItem(rc+1,0,proN);
            ui->tblPgm->setItem(rc+1,1,proS);
            ui->tblPgm->setItem(rc+1,2,proD);
            ui->tblPgm->selectRow(rc+1);


            system("sync");
        }
    }
#endif
}
/*************************************************************************
* ��������: on_btnEx_clicked
* ��   ��: ��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_ProM::on_btnEx_clicked()
{
    if(!usr.CheckUsr(TUsr::Administrator))
        return;

#ifdef EMBEDED_ARM
    Dlg_Keyboard dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        if(QFile::copy(QString("%1/%2.pgm").arg(widMana->strPgm).arg(dlg.m_str),
                       QString("/media/sda1/%1.pgm").arg(dlg.m_str)))
        {
            system("sync");
        }
    }
#endif
}

//==========================================================================================
// End of file.
//==========================================================================================

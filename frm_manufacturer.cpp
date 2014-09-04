/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_manufacturer.cpp

* 功能描述: 厂家设置画面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include <QProcess>
#include <QDir>
#include <QFileInfoList>
#include <QDateTime>

#include "frm_manufacturer.h"
#include "ui_frm_manufacturer.h"
#include "qa5driver.h"

/*************************************************************************
* 函数名称: Frm_Manufacturer
* 功   能: 构造函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
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
    header.append(QObject::tr("程序名"));
    header.append(QObject::tr("大小"));
    header.append(QObject::tr("创建时间"));
    ui->tblUpdate->setHorizontalHeaderLabels(header);


    ui->tblXML->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblXML->setColumnCount(3);
    //ui->tblPgm->setRowCount(4);
    ui->tblXML->setColumnWidth(0,200);
    ui->tblXML->setColumnWidth(1,100);
    ui->tblXML->setColumnWidth(2,300);
    QStringList headerXML;
    headerXML.append(QObject::tr("文件名"));
    headerXML.append(QObject::tr("大小"));
    headerXML.append(QObject::tr("创建时间"));
    ui->tblXML->setHorizontalHeaderLabels(headerXML);

}
/*************************************************************************
* 函数名称: Frm_Manufacturer
* 功   能: 析构函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_Manufacturer::~Frm_Manufacturer()
{
    delete ui;
}
/*************************************************************************
* 函数名称: on_btnReboot_clicked
* 功   能: 重启系统
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Manufacturer::on_btnReboot_clicked()
{
#ifdef EMBEDED_ARM
    QProcess::execute("/root/reboot");
#endif
}
/*************************************************************************
* 函数名称: on_btnRelad_clicked
* 功   能: 加载U盘程序
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Manufacturer::on_btnRelad_clicked()
{
    ui->tblUpdate->clearContents();
#ifdef EMBEDED_ARM
    QDir dir("/media/sda1/YsRobot");
#else
    QDir dir("E://BIN//qy");
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
        QString suffix = file_info.suffix();
        if(QString::compare(suffix, QString(""), Qt::CaseInsensitive) == 0)
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

            static int iR = 0;
            ui->tblUpdate->insertRow(iR);
            ui->tblUpdate->setItem(iR,0,proN);
            ui->tblUpdate->setItem(iR,1,proS);
            ui->tblUpdate->setItem(iR,2,proD);
            iR++;
        }
    }
}
/*************************************************************************
* 函数名称: on_btnUpd_clicked
* 功   能: 更新系统
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Manufacturer::on_btnUpd_clicked()
{
#ifdef EMBEDED_ARM
    //获取程序名
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
* 函数名称: on_btnRecov_clicked
* 功   能: 恢复系统
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
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
/*************************************************************************
* 函数名称: on_btnImXml_clicked
* 功   能: 导入XML文档
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Manufacturer::on_btnImXml_clicked()
{
#ifdef EMBEDED_ARM
    //获取程序名
    QModelIndex       index = ui->tblXML->currentIndex();
    if(!index.isValid())
        return;
    QTableWidgetItem *item  = ui->tblXML->item(index.row(),0);
    QString           strN  = item->text();

    QFile::remove(QString("/root/Config.xml"));
    if(QFile::copy(QString("/media/sda1/YsRobot/%1").arg(strN),
                   QString("/root/Config.xml")))
    {
        system("sync");
        system("reboot");
    }
#endif
}
/*************************************************************************
* 函数名称: on_btnReladXml_clicked
* 功   能: 加载XML文档
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_Manufacturer::on_btnReladXml_clicked()
{
    ui->tblXML->clearContents();

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
        QString suffix = file_info.suffix();
        if(QString::compare(suffix, QString("xml"), Qt::CaseInsensitive) == 0)
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

            static int iR = 0;
            ui->tblXML->insertRow(iR);
            ui->tblXML->setItem(iR,0,proN);
            ui->tblXML->setItem(iR,1,proS);
            ui->tblXML->setItem(iR,2,proD);
            iR++;
        }
    }
}
//==========================================================================================
// End of file.
//==========================================================================================



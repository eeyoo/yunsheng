/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: Dlg_StackManage.cpp

* 功能描述: 堆叠程序管理界面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include "dlg_stackmanage.h"
#include "ui_dlg_stackmanage.h"
#include "twidmana.h"

#include <QFile>
#include <QDir>
#include <QDateTime>

/*************************************************************************
* 函数名称: Dlg_StackManage
* 功   能: 构造函数
* 输入参数: QWidget *parent 父类句柄
* 输出参数: 无
* 返 回 值: 无
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
    header.append(QObject::tr("程序名"));
    header.append(QObject::tr("大小"));
    header.append(QObject::tr("创建时间"));
    ui->tblWStkM->setHorizontalHeaderLabels(header);

    SearchFile();
}
/*************************************************************************
* 函数名称: Dlg_StackManage
* 功   能: 析构函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_StackManage::~Dlg_StackManage()
{
    delete ui;
}
/*************************************************************************
* 函数名称: SearchFile
* 功    能: 查找文件夹中的文件
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: on_btnOK_clicked
* 功    能: 点击确定按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_StackManage::on_btnOK_clicked()
{
    //获取程序名
    QModelIndex       index = ui->tblWStkM->currentIndex();
    if(!index.isValid())
        QDialog::reject();

    QTableWidgetItem *item  = ui->tblWStkM->item(index.row(),0);
    m_strN  = item->text();

    QDialog::accept();
}
/*************************************************************************
* 函数名称: on_btnCancel_clicked
* 功    能: 点击取消按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_StackManage::on_btnCancel_clicked()
{
    QDialog::reject();
}

//==========================================================================================
// End of file.
//==========================================================================================

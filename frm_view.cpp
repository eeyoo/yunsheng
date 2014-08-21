/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: frm_view.cpp

* 功能描述: 系统信息查看画面

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#include "frm_view.h"
#include "ui_frm_view.h"
#include "twarn.h"

struct SWarn
{
    bool chcek;
    QString warn;
};
/*************************************************************************
* 函数名称: Frm_View
* 功    能: 构造函数
* 输入参数: parent
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_View::Frm_View() :
    
    ui(new Ui::Frm_View)
{
    ui->setupUi(this);
    //setAutoFillBackground(true);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnCount(3);
    //ui->tblPgm->setRowCount(4);
    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(1,500);
    ui->tableWidget->setColumnWidth(2,200);
    //ui->tableWidget->horizontalHeader()->hide();
    QStringList header;
    header.append(QObject::tr("编号"));
    header.append(QObject::tr("提示"));
    header.append(QObject::tr("时间"));
    ui->tableWidget->setHorizontalHeaderLabels(header);
}
/*************************************************************************
* 函数名称: ~Frm_View
* 功    能: 析构函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Frm_View::~Frm_View()
{
    delete ui;
}
/*************************************************************************
* 函数名称: setVisible
* 功    能: 初始化窗口显示，设置程序行的宽度
* 输入参数: visible	true显示，false隐藏
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Frm_View::setVisible(bool visible)
{
    QWidget::setVisible(visible);

    if(visible){
        for(int i = 0; i < warn.wrnH.size(); i++){
            QString strWN = QString("%1").arg(warn.wrnH[i].wrnN);
            QString strN = warn.wrnH[i].strM;
            QDateTime dt = warn.wrnH[i].dt;
            QString strD = QString("%1-%2-%3 %4:%5:%6")
                           .arg(dt.date().year()).arg(dt.date().month()).arg(dt.date().day())
                           .arg(dt.time().hour()).arg(dt.time().minute()).arg(dt.time().second());

            QTableWidgetItem *wrnN=new QTableWidgetItem(strWN);
            QTableWidgetItem *Name=new QTableWidgetItem(strN);
            QTableWidgetItem *wrnD=new QTableWidgetItem(strD);

            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i,0,wrnN);
            ui->tableWidget->setItem(i,1,Name);
            ui->tableWidget->setItem(i,2,wrnD);
        }
    }
}

//==========================================================================================
// End of file.
//==========================================================================================

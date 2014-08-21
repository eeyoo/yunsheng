/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_view.cpp

* ��������: ϵͳ��Ϣ�鿴����

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
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
* ��������: Frm_View
* ��    ��: ���캯��
* �������: parent
* �������: ��
* �� �� ֵ: ��
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
    header.append(QObject::tr("���"));
    header.append(QObject::tr("��ʾ"));
    header.append(QObject::tr("ʱ��"));
    ui->tableWidget->setHorizontalHeaderLabels(header);
}
/*************************************************************************
* ��������: ~Frm_View
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_View::~Frm_View()
{
    delete ui;
}
/*************************************************************************
* ��������: setVisible
* ��    ��: ��ʼ��������ʾ�����ó����еĿ��
* �������: visible	true��ʾ��false����
* �������: ��
* �� �� ֵ: ��
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

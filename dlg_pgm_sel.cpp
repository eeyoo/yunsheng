/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_pgm_sel.cpp

* 功能描述: 程序选择文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#include "dlg_pgm_sel.h"
#include "ui_dlg_pgm_sel.h"

/*************************************************************************
* 函数名称: Dlg_Pgm_Sel
* 功   能: 构造函数，初始化tableWidget控件
* 输入参数: QWidget *parent
* 输出参数: 无
* 返 回 值: 无
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
* 函数名称: ~Dlg_Pgm_Sel
* 功   能: 析构函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Pgm_Sel::~Dlg_Pgm_Sel()
{
    delete ui;
}
/*************************************************************************
* 函数名称: on_btnOK_clicked
* 功    能: 点击确定按钮
* 输入参数: QWidget *parent
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Pgm_Sel::on_btnOK_clicked()
{
    m_iPgm = ui->tableWidget->currentRow();

    QDialog::accept();
}
/*************************************************************************
* 函数名称: on_btnCan_clicked
* 功    能: 点击退出按钮
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Pgm_Sel::on_btnCan_clicked()
{
    QDialog::reject();
}

//==========================================================================================
// End of file.
//==========================================================================================

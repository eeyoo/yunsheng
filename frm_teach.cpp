/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: frm_teach.cpp

* ��������: ʾ�̻���

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#include "frm_teach.h"
#include "ui_frm_teach.h"
#include "twidmana.h"
#include "tcmd.h"
#include "dlg_psw.h"
#include "dlg_manu.h"
#include "twarn.h"
#include "dlg_generinput.h"
#include "dlg_genercrysoutput.h"
#include "dlg_generrelayoutput.h"

#include <QScrollBar>

/*************************************************************************
* ��������: Frm_Teach
* ��    ��: ���캯��
* �������: parent
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Teach::Frm_Teach() :
    
    ui(new Ui::Frm_Teach)
{
    ui->setupUi(this);
    //setAutoFillBackground(true);
    InitBtn();
    InitTim();

    ui->tblV_Pro->setModel(com20.modelPro);
    ui->tblV_Pro->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tblV_Pro->setStyleSheet("selection-background-color: rgb(255,0,0)");
    //ui->tblV_Pro->setAlternatingRowColors(true);
    //ui->tblV_Pro->setStyleSheet("QTableView{background-color: rgb(250, 250, 115);"
    //                            "alternate-background-color: rgb(141, 163, 215);}");
    //ui->tblV_Pro->setItemDelegateForColumn(0, new TTchPgm(this));
    ui->tblV_Pro->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblV_Pro->setIconSize(QSize(42,42));

    ui->tblV_Pro->setColumnWidth(0,70);
    ui->tblV_Pro->setColumnWidth(1,50);
    ui->tblV_Pro->setColumnWidth(2,280);
    ui->tblV_Pro->horizontalHeader()->hide();
    ui->tblV_Pro->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QStandardItem *startI=new QStandardItem(QObject::tr("����ʼ"));
    com20.modelPro->setItem(0,2,startI);
    QStandardItem *endI=new QStandardItem(QObject::tr("�������"));
    com20.modelPro->setItem(1,2,endI);

    ui->tblV_Pro->setRowHeight(0,50);
    ui->tblV_Pro->setRowHeight(1,50);
    ui->tblV_Pro->selectRow(0);
    ui->tblV_Pro->setFocus(Qt::MouseFocusReason);
    ui->tblV_Pro->verticalHeader()->setResizeMode(0,QHeaderView::Fixed);
    ui->tblV_Pro->verticalHeader()->setResizeMode(1,QHeaderView::Fixed);


    ui->tabCmd->setCurrentIndex(0);

    TLineEdit *pLeI = (TLineEdit*)(ui->leNoI);
    pLeI->iMark = 0;
    if(!readCmd.CmdI.isEmpty()){
        pLeI->setText(readCmd.CmdI[0].cmdTil);
    }else{
        pLeI->setText(QString("0"));
    }

    TLineEdit *pLeO = (TLineEdit*)(ui->leNoO);
    pLeO->iMark = 0;
    if(!readCmd.CmdO.isEmpty()){
        pLeO->setText(readCmd.CmdO[0].cmdTil);
    }else{
        pLeO->setText(QString("0"));
    }

    m_bModify = false;
    m_bStk    = false;
}
/*************************************************************************
* ��������: ~Frm_Teach
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
Frm_Teach::~Frm_Teach()
{
    delete ui;
}
/*************************************************************************
* ��������: InitBtn
* ��    ��: ��ʼ�����ť��Ϣ����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::InitBtn()
{
    QPushButton *btn[] = {ui->btnR1,ui->btnR2,ui->btnR3,ui->btnR4,ui->btnR5,
                        ui->btnIG,ui->btnO1,ui->btnO2,ui->btnS};

    for(int i=0; i<sizeof(btn)/sizeof(QPushButton*); i++)
    {
        sglMapL.setMapping(btn[i],i);
        connect(btn[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));

        btn[i]->setCheckable(true);
        btn[i]->setAutoExclusive(true);
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_btn_clicked(int)));

    m_iCmd = 0;
}
/*************************************************************************
* ��������: InitTim
* ��    ��: ��ʼ����ʱ������Ϣ����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::InitTim()
{
    TLineEdit *leT[] = {ui->leTimD,ui->leTimR,ui->leTimI,ui->leTimO,ui->leTimS,ui->leSpdD,ui->leSpdR};
    for(int i=0;i<sizeof(leT)/sizeof(TLineEdit*);i++)
    {
        sglMapT.setMapping(leT[i],i);
        connect(leT[i], SIGNAL(clicked()), &sglMapT, SLOT(map()));
    }
    connect(&sglMapT,SIGNAL(mapped(int)),this,SLOT(on_leT_clicked(int)));
}
/*************************************************************************
* ��������: on_tabCmd_currentChanged
* ��    ��: ʾ�������ǩ�л�
* �������: index	�л��ı�ǩ
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_tabCmd_currentChanged(int index)
{
    quint8 btnI[] = {0,5,8};
    on_btn_clicked(btnI[index]);
}
/*************************************************************************
* ��������: on_btn_clicked
* ��    ��: ��Ӧ���ť����¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_btn_clicked(int ibtn)
{
    QPushButton *btn[]={ui->btnR1,ui->btnR2,ui->btnR3,ui->btnR4,ui->btnR5,
                        ui->btnIG,ui->btnO1,ui->btnO2,ui->btnS};
    btn[ibtn]->setChecked(true);
    m_iCmd = ibtn;
    QWidget* wid[] = {ui->page_D,ui->page_D,ui->page_R,ui->page_D,ui->page_D,
                      ui->page_I,ui->page_O,ui->page_O,ui->page_S};
    ui->stkW_Para->setCurrentWidget(wid[ibtn]);

    m_bModify = false;
}
/*************************************************************************
* ��������: on_leT_clicked
* ��    ��: ��Ӧʱ�������ı������¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_leT_clicked(int ile)
{
    TLineEdit *leT[] = {ui->leTimD,ui->leTimR,ui->leTimI,ui->leTimO,ui->leTimS,ui->leSpdD,ui->leSpdR};
    Dlg_Psw dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        leT[ile]->setText(dlg.m_str);
    }
}
/*************************************************************************
* ��������: on_lePosD_clicked
* ��    ��: ����ֱ���˶�����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_lePosD_clicked()
{
    Dlg_Manu dlg;
    dlg.setModal(true);
    dlg.InitBtn(m_iCmd);
    if(dlg.exec()==QDialog::Accepted)
    {
        quint32 pos[]={comF0.rpara.xpos,comF0.rpara.y1pos,comF0.rpara.z1pos,comF0.rpara.y2pos,comF0.rpara.z2pos};

        double posC = ((double)pos[m_iCmd]) / 100.0;
        ui->lePosD->setText(QString::number(posC,'f',2));
    }
}
/*************************************************************************
* ��������: on_lePosR_clicked
* ��    ��: ������ת�Ƕ�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_lePosR_clicked()
{
    Dlg_Manu dlg;
    dlg.setModal(true);
    dlg.InitBtn(2);
    if(dlg.exec()==QDialog::Accepted)
    {
        quint32 pos[]={comF0.rpara.xpos,comF0.rpara.y1pos,comF0.rpara.z1pos,comF0.rpara.y2pos,comF0.rpara.z2pos};

        double posC = ((double)pos[2]) / 100.0;
        ui->lePosR->setText(QString::number(posC,'f',2));
    }
}
/*************************************************************************
* ��������: on_leNoI_clicked
* ��    ��: �����������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_leNoI_clicked()
{
    Dlg_GenerInput dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted){
        if(dlg.iI < readCmd.CmdI.size()){
            ui->leNoI->setText(readCmd.CmdI[dlg.iI].cmdTil);
        }else{
            ui->leNoI->setText(QString("%1").arg(dlg.iI));
        }

        ((TLineEdit*)ui->leNoI)->iMark = dlg.iI;
    }
}
/*************************************************************************
* ��������: on_leNoO_clicked
* ��    ��: ����������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_leNoO_clicked()
{
    if(ui->btnO1->isChecked()){
        Dlg_GenerRelayOutput dlg;
        dlg.setModal(true);
        if(dlg.exec() == QDialog::Accepted){
            if(dlg.iO < readCmd.CmdO.size()){
                ui->leNoO->setText(readCmd.CmdO[dlg.iO].cmdTil);
            }else{
                ui->leNoO->setText(QString("%1").arg(dlg.iO));
            }
        }
        ((TLineEdit*)ui->leNoO)->iMark = dlg.iO;
    }else{
        Dlg_GenerCrysOutput dlg;
        dlg.setModal(true);
        if(dlg.exec() == QDialog::Accepted){
            if(dlg.iO < readCmd.CmdO.size()){
                ui->leNoO->setText(readCmd.CmdO[dlg.iO].cmdTil);
            }else{
                ui->leNoO->setText(QString("%1").arg(dlg.iO));
            }
        }
        ((TLineEdit*)ui->leNoO)->iMark = dlg.iO;
    }
}
/*************************************************************************
* ��������: on_btnOK_clicked
* ��    ��: ���ȷ����ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_btnOK_clicked()
{
    m_bStk = false;
    int iRow = 0;
    QModelIndex index = ui->tblV_Pro->currentIndex();
    if((index.row() != com20.modelPro->rowCount()-1) && index.isValid())
        iRow = index.row();
    //�޸��������
    if(m_bModify){
        TCmd *cmd=(TCmd*)com20.modelPro->item(index.row(),1);
        cmd->ConsPara();
        QStandardItem *item=com20.modelPro->item(ui->tblV_Pro->currentIndex().row(),2);
        item->setText(cmd->getCmdTit());

        com20.bOpen = true;
        m_bModify=false;
        return;

    }

    //�������
    com20.AddCmd(iRow + 1);

    TCmd *cmd = create_cmd[m_iCmd]();
    cmd->ConsPara();

    com20.SetItem(iRow + 1,1,(QStandardItem*)cmd);
    com20.SetItem(iRow + 1,2,cmd->ConsTitItem());

    ui->tblV_Pro->selectRow(iRow + 1);
    ui->tblV_Pro->setRowHeight(iRow + 1,50);
    ui->tblV_Pro->verticalHeader()->setResizeMode(iRow + 1,QHeaderView::Fixed);
}
/*************************************************************************
* ��������: on_tblV_Pro_clicked
* ��    ��: ���ʾ������
* �������: index	��ǰ�����ʾ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_tblV_Pro_clicked(QModelIndex index)
{
    //ui->leRPos->setText(QString("%1").arg(com20.modelPro->rowCount()));
    //�жϵ�һ�к����һ�У����ܲ�����Ϲ�ϵ
    if(index.row() == 0||index.row() == com20.modelPro->rowCount()-1){
        m_bModify=false;
        return;
    }

    if(index.column()==0)
    {
        Dlg_Psw dlg;
        dlg.setModal(true);
        if(dlg.exec()==QDialog::Accepted)
        {
            TCmd *itemCmd=(TCmd*)com20.modelPro->item(index.row(),1);
            itemCmd->para.combin=dlg.m_str.toInt();
            com20.SetItem(index.row(),0,itemCmd->ConsCombiItem());
            ui->tblV_Pro->selectRow(index.row());
            ui->tblV_Pro->setRowHeight(index.row(),50);
        }
    }
    else
    {
        TCmd *cmd=(TCmd*)com20.modelPro->item(index.row(),1);
        cmd->OnCmdClk();
        m_bModify=true;
    }
}
/*************************************************************************
* ��������: on_btnAhd_clicked
* ��    ��: ���ǰ����ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_btnAhd_clicked()
{
    if(!widMana->bTri)
        return;

    QModelIndex index = ui->tblV_Pro->currentIndex();
    if(index.row() != 0 && index.row() != com20.modelPro->rowCount() - 1){

        TCmd *itemCmd=(TCmd*)com20.modelPro->item(index.row(),1);

        if(itemCmd->para.action >= TCmd::X1MOV &&
           itemCmd->para.action <  TCmd::INPUT){

           TCmd_Mov* cmd[] ={cmd_movX,cmd_movY1,cmd_movZ1,cmd_movY2,cmd_movZ2};

           cmd[itemCmd->para.action - TCmd::X1MOV]->para.dist = itemCmd->para.dist;

           QMutexLocker locker(&mutex_com);
           pComBuf2.push_back((TCom*)cmd[itemCmd->para.action - TCmd::X1MOV]);
        }else if(itemCmd->para.action >= TCmd::INPUT &&
                 itemCmd->para.action <  TCmd::OUTPUT){
            QMutexLocker locker(&mutex_com);
            pComBuf2.push_back((TCom*)itemCmd);
        }

        if(index.row() < com20.modelPro->rowCount() - 2)
        {
            ui->tblV_Pro->selectRow(index.row() + 1);
        }
    }
}
/*************************************************************************
* ��������: on_btnBck_clicked
* ��    ��: ������˰�ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_btnBck_clicked()
{
    if(!widMana->bTri)
        return;

    QModelIndex index = ui->tblV_Pro->currentIndex();
    if(index.row() != 0 && index.row() != com20.modelPro->rowCount() - 1){

        TCmd *itemCmd=(TCmd*)com20.modelPro->item(index.row(),1);

        if(itemCmd->para.action >= TCmd::X1MOV &&
           itemCmd->para.action <  TCmd::INPUT){

           TCmd_Mov* cmd[] ={cmd_movX,cmd_movY1,cmd_movZ1,cmd_movY2,cmd_movZ2};

           cmd[itemCmd->para.action - TCmd::X1MOV]->para.dist = itemCmd->para.dist;

           QMutexLocker locker(&mutex_com);
           pComBuf2.push_back((TCom*)cmd[itemCmd->para.action - TCmd::X1MOV]);
       }else if(itemCmd->para.action >= TCmd::INPUT &&
                itemCmd->para.action < TCmd::OUTPUT){
            QMutexLocker locker(&mutex_com);
            pComBuf2.push_back((TCom*)itemCmd);
        }

        if(index.row() > 1)
        {
            ui->tblV_Pro->selectRow(index.row() - 1);
        }
    }
}
/*************************************************************************
* ��������: on_btnSve_clicked
* ��    ��: ������水ť�����浱ǰ����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_btnSve_clicked()
{
    QFile *file = new QFile();
    file->setFileName(QString("%1/%2.pgm")
                      .arg(widMana->strPgm).arg(widMana->strFileN));
    file->open(QIODevice::WriteOnly);
    file->reset();

    com20.SavePgm(file);

    file->close();
    file->deleteLater();

#ifdef EMBEDED_ARM
    system("sync");
#endif

    warn.ShowW2L(TWarn::W_SAVE);
}
/*************************************************************************
* ��������: on_btnDel_clicked
* ��    ��: ���ɾ����ť��ɾ������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_btnDel_clicked()
{
    QModelIndex index = ui->tblV_Pro->currentIndex();
    if(index.row() > 0 && index.row()!= com20.modelPro->rowCount() - 1)
    {
        com20.DelCmd(index.row());
        m_bModify = false;
        ui->tblV_Pro->selectRow(index.row() - 1);
    }
}
/*************************************************************************
* ��������: setVisible
* ��    ��: ��ʼ��������ʾ�����ó����еĿ��
* �������: visible	true��ʾ��false����
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::setVisible(bool visible)
{
    QWidget::setVisible(visible);

    if(visible)
    {
        ui->tblV_Pro->setColumnWidth(0,70);
        ui->tblV_Pro->setColumnWidth(1,50);
        ui->tblV_Pro->setColumnWidth(2,280);
        ui->tblV_Pro->horizontalHeader()->hide();

        for(int i = 0;i<com20.modelPro->rowCount();i++)
        {
            ui->tblV_Pro->setRowHeight(i,50);
        }

        if(m_bStk){
            ui->leStkN->setText(widMana->frm_stack.strN);
        }
    }
}
/*************************************************************************
* ��������: on_leStkN_clicked
* ��    ��: ������öѵ�ָ��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void Frm_Teach::on_leStkN_clicked()
{
    m_bStk = true;

    widMana->frm_stack.stk_t = Frm_Stack::TEACH;
    widMana->SwitchWM(&widMana->frm_stack);
}

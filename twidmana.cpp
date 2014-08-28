/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: twidmama.cpp

* ��������: ���ڹ�����

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#include <QDir>
#include <QTextStream>

#include "twidmana.h"
#include "ui_mainwindow.h"
#include "ui_frm_pros.h"
#include "tcmd.h"
#include "qa5driver.h"
#include "dlg_authority.h"

TWidMana        *widMana;
//QStandardItemModel *modelPro;
QStandardItem   *itemP;

/*************************************************************************
* ��������: TWidMana
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TWidMana::TWidMana()
{
    bDialog = false;
    bTri    = false;

    pCurW = NULL;
}
/*************************************************************************
* ��������: InitWid
* ��    ��: ��ʼ���Ӵ��ڵ�λ�á����⡢��ʾ
* �������: pPar�������ھ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TWidMana::InitWid(QWidget *pPar)
{
    if(pPar == NULL)
        return;

    mainW = (MainWindow*)pPar;

    int x = ((MainWindow*)pPar)->ui->midlleFrame->x();
    int y = ((MainWindow*)pPar)->ui->midlleFrame->y();
    int wm = ((MainWindow*)pPar)->ui->midlleFrame->width();
    int hm = ((MainWindow*)pPar)->ui->midlleFrame->height();
    int wb = ((MainWindow*)pPar)->ui->bottomFrame->width();
    int hb = ((MainWindow*)pPar)->ui->bottomFrame->height();
    int hg = ((MainWindow*)pPar)->ui->bottomFrame->height() +
             ((MainWindow*)pPar)->ui->midlleFrame->height() +
             ((MainWindow*)pPar)->ui->positionFrame->height() +
             ((MainWindow*)pPar)->ui->titleFrame->height();

    int ht = ((MainWindow*)pPar)->ui->btnbFrame->height();

    /*QPoint pt1 = pPar->mapToGlobal(QPoint(x,y));
    QPoint pt2 = pPar->mapToGlobal(QPoint(x+wm,y+hm));
    QPoint pt2 = pPar->mapToGlobal(QPoint(x+wm,y+hm+hb));*/
    QPoint pt1 = QPoint(x,y);
    QPoint pt2 = QPoint(x+wm,y+hm);
    QPoint pt3 = QPoint(x+wm,y+hm+hb);

    Wid_Mana wid;
    frm_fun.setParent(pPar);
    frm_fun.setWindowFlags(Qt::FramelessWindowHint);
    frm_fun.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_fun.hide();
    wid.pWid = &frm_fun;
    wid.strT = QObject::tr("������");
    widM.push_back(wid);


    frm_mana.setParent(pPar);
    frm_mana.setWindowFlags(Qt::FramelessWindowHint);
    frm_mana.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_mana.hide();
    wid.pWid = &frm_mana;
    wid.strT = QObject::tr("�ֶ�");
    widM.push_back(wid);

    frm_run.setParent(pPar);
    frm_run.setWindowFlags(Qt::FramelessWindowHint);
    frm_run.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_run.hide();
    wid.pWid = &frm_run;
    wid.strT = QObject::tr("����");
    widM.push_back(wid);

    frm_lang.setParent(pPar);
    frm_lang.setWindowFlags(Qt::FramelessWindowHint);
    frm_lang.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_lang.hide();
    wid.pWid = &frm_lang;
    wid.strT = QObject::tr("����");
    widM.push_back(wid);

    frm_pros.setParent(pPar);
    frm_pros.setWindowFlags(Qt::FramelessWindowHint);
    frm_pros.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_pros.hide();
    wid.pWid = &frm_pros;
    wid.strT = QObject::tr("��Ʒ����");
    widM.push_back(wid);

    frm_stack.setParent(pPar);
    frm_stack.setWindowFlags(Qt::FramelessWindowHint);
    frm_stack.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_stack.hide();
    wid.pWid = &frm_stack;
    wid.strT = QObject::tr("�ѵ�����");
    widM.push_back(wid);

    frm_view.setParent(pPar);
    frm_view.setWindowFlags(Qt::FramelessWindowHint);
    frm_view.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_view.hide();
    wid.pWid = &frm_view;
    wid.strT = QObject::tr("ϵͳ��Ϣ");
    widM.push_back(wid);

    frm_teach.setParent(pPar);
    frm_teach.setWindowFlags(Qt::FramelessWindowHint);
    frm_teach.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_teach.hide();
    wid.pWid = &frm_teach;
    wid.strT = QObject::tr("ʾ��");
    widM.push_back(wid);

    frm_prom.setParent(pPar);
    frm_prom.setWindowFlags(Qt::FramelessWindowHint);
    frm_prom.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_prom.hide();
    wid.pWid = &frm_prom;
    wid.strT = QObject::tr("����");
    widM.push_back(wid);

    frm_m_n.setParent(pPar);
    frm_m_n.setWindowFlags(Qt::FramelessWindowHint);
    frm_m_n.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_m_n.hide();
    wid.pWid = &frm_m_n;
    wid.strT = QObject::tr("�ֶ�");
    widM.push_back(wid);

    frm_setup.setParent(pPar);
    frm_setup.setWindowFlags(Qt::FramelessWindowHint);
    frm_setup.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_setup.hide();
    wid.pWid = &frm_setup;
    wid.strT = QObject::tr("����");
    widM.push_back(wid);

    frm_monit.setParent(pPar);
    frm_monit.setWindowFlags(Qt::FramelessWindowHint);
    frm_monit.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_monit.hide();
    wid.pWid = &frm_monit;
    wid.strT = QObject::tr("����");
    widM.push_back(wid);

    frm_mftr.setParent(pPar);
    frm_mftr.setWindowFlags(Qt::FramelessWindowHint);
    frm_mftr.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_mftr.hide();
    wid.pWid = &frm_mftr;
    wid.strT = QObject::tr("����ά��");
    widM.push_back(wid);

    frm_hlp.setParent(pPar);
    frm_hlp.setWindowFlags(Qt::FramelessWindowHint);
    frm_hlp.setGeometry(pt1.x(),pt1.y(),pt2.x()-pt1.x(),pt2.y()-pt1.y());
    frm_hlp.hide();
    wid.pWid = &frm_hlp;
    wid.strT = QObject::tr("����");
    widM.push_back(wid);

    SwitchWM(&frm_fun,ST_SHOW);


    //����ϵͳ�ļ�
    CreateSysF();
    //��ϵͳ�����ļ�
    OpenPara();
}
/*************************************************************************
* ��������: SwitchWM
* ��    ��: �л����ڵ���ʾ
* �������: pWidget��ǰ��Ҫ�л��Ĵ���
			st�����л���ʽ
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TWidMana::SwitchWM(QWidget *pWidget,SHOWTYPE st)
{
    static QWidget *pCurWidgetH = NULL;//��ǰ���ش��ھ��
    static QWidget *pCurWidgetS = NULL;//��ǰ��ʾ���ھ��

    if(pWidget == NULL)
        return;

    if(pCurWidgetS == &frm_teach){
        if(com20.bOpen){
            warn.ShowW2L(TWarn::W_NEWPRG_S);
            return;
        }
    }
    //printf("SavePara111\n");
    switch(st)
    {
    case ST_SHOW:
        if(pCurWidgetS != NULL)
        {
            pCurWidgetS->hide();
            pCurWidgetH = pCurWidgetS;
        }

        pWidget->show();
        pCurWidgetS = pWidget;

        break;
    case ST_HIDE:
        pWidget->hide();
        pCurWidgetH->show();

        pCurWidgetS = pCurWidgetH;
        pCurWidgetH = pWidget;
        break;
    default:
        break;
    }

    pCurW = (TWidget*)pCurWidgetS;

    for(int i = 0; i < widM.size(); i++){
        if(pCurWidgetS == widM[i].pWid){
            mainW->ui->btnWName->setText(widM[i].strT);
            break;
        }
    }
}
/*************************************************************************
* ��������: OpenPara
* ��    ��: ��ϵͳ����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TWidMana::OpenPara()
{
    QString strP = QString("%1/para").arg(strSysPara);

#ifdef EMBEDED_ARM
    //strP = QString("./root/data/para");
#endif
    //printf("%s\n",strP.toLatin1().data());

    QFile *file  =  new QFile();
    file->setFileName(strP);
    file->open(QIODevice::ReadOnly);
    file->reset();

    file->read((char*)(&com01.para),sizeof(com01.para));
    file->read((char*)(com02.para),sizeof(TCom02::STR_PARA)*5);
    file->read((char*)(&com03.para),sizeof(com03.para));
    file->read((char*)(&com04.para),sizeof(com04.para));
    file->read((char*)(&com05.para),sizeof(com05.para));
    file->read((char*)(&com07.para),sizeof(com07.para));

    file->close();
    file->deleteLater();

    InitParaUI();


    //frm_usrs.ui->leMSpdZ1->setText(strSysPara);
    //frm_usrs.ui->leRstSpd->setText(strP);
}
/*************************************************************************
* ��������: SavePara
* ��    ��: ����ϵͳ����
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TWidMana::SavePara()
{
    QString strP = QString("%1/para").arg(strSysPara);
#ifdef EMBEDED_ARM
    //strP = QString("./root/data/para");
#endif
    //frm_usrs.ui->leZroOftZ1->setText(strP);

    QFile *file = new QFile();
    file->setFileName(strP);
    file->open(QIODevice::WriteOnly|QIODevice::Truncate);
    file->reset();

    file->write((char*)(&com01.para),sizeof(com01.para));
    file->write((char*)(com02.para),sizeof(TCom02::STR_PARA)*5);
    file->write((char*)(&com03.para),sizeof(com03.para));
    file->write((char*)(&com04.para),sizeof(com04.para));
    file->write((char*)(&com05.para),sizeof(com05.para));
    file->write((char*)(&com07.para),sizeof(com07.para));

    file->close();
    file->deleteLater();

#ifdef EMBEDED_ARM
    system("sync");
#endif
}
/*************************************************************************
* ��������: InitParaUI
* ��    ��: ���ݴ򿪵�ϵͳ��������ʼ��UI
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TWidMana::InitParaUI()
{
    for(int i = 0; i < 5; i++){
        com02.para[i].axis = TCom::X + i;
    }

    frm_setup.SetAxisEn();

    mainW->ui->btnWhlSpd->setText(QString("%1%").arg(com02.para[0].whlvel));
    usr.SetCurUsr(usr.curUsr);
}
/*************************************************************************
* ��������: CreateSysF
* ��    ��: ����ϵͳ�����ļ��С�ʾ���ļ��ļ���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TWidMana::CreateSysF()
{
    QDir *temp = new QDir();
#ifdef EMBEDED_ARM
    temp->setCurrent("/root");
#endif

    strPgm = QString("%1/pgm").arg(temp->currentPath());
    bool exist = temp->exists(strPgm);
    if(!exist)
    {
        temp->mkdir(strPgm);
    }
    strStkP = QString("%1/stk").arg(temp->currentPath());
    exist = temp->exists(strStkP);
    if(!exist)
    {
        temp->mkdir(strStkP);
    }
    strSysPara = QString("%1/dat").arg(temp->currentPath());
    exist = temp->exists(strSysPara);
    if(!exist)
    {
        temp->mkdir(strSysPara);
        SavePara();
    }
}
/*************************************************************************
* ��������: ShowPgmN
* ��    ��: ��ʾʾ�̳��������
* �������: strN    ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TWidMana::ShowPgmN(QString strN)
{
    strFileN = strN;
    mainW->ui->btnPgmN->setText(strN);
}

//==========================================================================================
// End of file.
//==========================================================================================

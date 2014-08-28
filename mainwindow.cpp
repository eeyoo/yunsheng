/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: mainwindow.cpp

* ��������: ����ܴ���

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#include <QTimer>
#include <QDate>
#include <QTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dlg_teach.h"
#include "dlg_psw.h"
#include "twidmana.h"
#include "dlg_pgm_sel.h"
#include "tcmd.h"
#include "dlg_manu.h"
#include "dlg_authority.h"
#include "dlg_reset.h"
#include "tconfig.h"
#include "qa5driver.h"

/*************************************************************************
* ��������: MainWindow
* ��    ��: ���캯��
* �������: parent
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->mainStk->setCurrentIndex(0);
    //InitWid(this);
    QTimer *timer = new QTimer(this);
    timer->start(1000);//һ����
    connect(timer,SIGNAL(timeout()),this,SLOT(UpdateTim()));

    InitComP();
    //ͨѶʱ��
    QTimer *timerC = new QTimer(this);
    timerC->start(50);//50ms
    connect(timerC,SIGNAL(timeout()),this,SLOT(Can_Com()));

    //�ײ�����ɨ���ź�
#ifdef EMBEDED_ARM
    connect(&drv_key,SIGNAL(sigKey(int)),this,SLOT(on_sigKey(int)));
    drv_key.start();

    connect(&drv_qdec,SIGNAL(sigQdec(int)),this,SLOT(on_sigQdec(int)));
    drv_qdec.start();
#endif
}
/*************************************************************************
* ��������: UpdateTim
* ��    ��: ��ʾʱ��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::UpdateTim()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();


    QString str;
    QString strDate = QString("%1-").arg(date.year());
    if(date.month() < 10)
        str = QString("0%1-").arg(date.month());
    else
        str = QString("%1-").arg(date.month());
    strDate += str;

    if(date.day() < 10)
        str = QString("0%1").arg(date.day());
    else
        str = QString("%1").arg(date.day());
    strDate += str;

    QString strTim;
    if(time.hour() < 10)
        str = QString("0%1:").arg(time.hour());
    else
        str = QString("%1:").arg(time.hour());
    strTim += str;

    if(time.minute() < 10)
        str = QString("0%1:").arg(time.minute());
    else
        str = QString("%1:").arg(time.minute());
    strTim += str;

    if(time.second() < 10)
        str = QString("0%1").arg(time.second());
    else
        str = QString("%1").arg(time.second());
    strTim += str;

    ui->btnDate->setText(strDate);
    ui->btnTim->setText(strTim);

    warn.ClearW();


    config.DoScrPT();
}
/*************************************************************************
* ��������: ~MainWindow
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}
/*************************************************************************
* ��������: InitComP
* ��    ��: ��ʼ��ȫ�ֱ���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::InitComP()
{
    cmd_movX = new TCmd_Mov;
    cmd_movX->para.action = TCmd::X1MOV;
    cmd_movY1 = new TCmd_Mov;
    cmd_movY1->para.action = TCmd::Z1MOV;
    cmd_movZ1 = new TCmd_Mov;
    cmd_movZ1->para.action = TCmd::UMOV;
    cmd_movY2 = new TCmd_Mov;
    cmd_movY2->para.action = TCmd::X2MOV;
    cmd_movZ2 = new TCmd_Mov;
    cmd_movZ2->para.action = TCmd::Z2MOV;
    //cmd_movY = new TCmd_Mov;
    //cmd_movY->para.action = TCmd::YMOV;
    //cmd_movZ = new TCmd_Mov;
    //cmd_movZ->para.action = TCmd::ZMOV;


    cmd_In  = new TCmd_In;
    cmd_Out = new TCmd_Out;

    pComBuf1.push_back((TCom*)(&comF0));

    on_btnHlp_clicked();
}
/*************************************************************************
* ��������: Can_Com
* ��    ��: ִ��CANͨѶ
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::Can_Com()
{
    a5drv.buzzer_off();

    //printf("1\n");
    QMutexLocker locker(&mutex_com);
    if(pComBuf2.isEmpty())
    {
        static int index = 0;
        if(index<pComBuf1.size())
        {
            pComBuf1[index]->DoCom();
            //index++;
        }
        else
            index = -1;

        index++;
    }
    else
    {
        //int iS = pComBuf2.size()-1;
        pComBuf2[0]->DoCom();
        //delete pComBuf2[iS];
        pComBuf2.remove(0,1);
    }
    //printf("2\n");
}
/*************************************************************************
* ��������: on_btnbck_clicked
* ��    ��: ������ذ�ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnbck_clicked()
{
    if(!usr.CheckUsr(TUsr::Operator))
        return;

    widMana->SwitchWM(&widMana->frm_fun);
    //widMana->SavePara();
}
/*************************************************************************
* ��������: on_btnMana_clicked
* ��    ��: ����ֶ���ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnMana_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;
    //widMana->SwitchWM(&widMana->frm_mana);
    Dlg_Manu dlg;
    dlg.setModal(true);
    dlg.exec();
}
/*************************************************************************
* ��������: on_btnPrg_clicked
* ��    ��: �������ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnPrg_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!usr.CheckUsr(TUsr::Operator))
        return;

    widMana->SwitchWM(&widMana->frm_prom);
    /*QString strP[] = {
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

    Dlg_Pgm_Sel dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->btnPgmN->setText(strP[dlg.m_iPgm]);
    }*/
}
/*************************************************************************
* ��������: on_btnWth_clicked
* ��    ��: ���������ӻ���
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnWth_clicked()
{
    if(!usr.CheckUsr(TUsr::Operator))
        return;

    widMana->SwitchWM(&widMana->frm_monit);
}
/*************************************************************************
* ��������: on_btnStp_clicked
* ��    ��: ���ֹͣ��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnStp_clicked()
{
    //exit(0);

    if(!usr.CheckUsr(TUsr::Operator))
        return;

    QMutexLocker locker(&mutex_com);
    memset(&comE0.para,sizeof(comE0.para),0);
    comE0.para.runtype  = TComE0::STOP;
    pComBuf2.push_back((TCom*)&comE0);
}
/*************************************************************************
* ��������: on_btnRst_clicked
* ��    ��: �����λ��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnRst_clicked()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!usr.CheckUsr(TUsr::Operator))
        return;

    /*QMutexLocker locker(&mutex_com);
    memset(&comE0.para,sizeof(comE0.para),0);
    comE0.para.runtype  = TComE0::REST;
    pComBuf2.push_back((TCom*)&comE0);*/
    Dlg_Reset dlg;
    dlg.setModal(true);
    dlg.exec();
}
/*************************************************************************
* ��������: on_btnSrt_clicked
* ��    ��: ���������ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnSrt_clicked()
{
    if(com20.bNewForSnd){
        warn.ShowW2L(TWarn::W_NEWPRG);
        return;
    }
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!usr.CheckUsr(TUsr::Operator))
        return;

    QMutexLocker locker(&mutex_com);
    memset(&comE0.para,sizeof(comE0.para),0);
    comE0.para.runtype  = TComE0::AUTO;
    pComBuf2.push_back((TCom*)&comE0);
}
/*************************************************************************
* ��������: on_btnUp_pressed
* ��    ��: ����UP��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnUp_pressed()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!widMana->bDialog)
        return;

    if(!widMana->bTri)
        return;

    quint8 axis[] = {TCom::X,TCom::Y1,TCom::Z1,TCom::Y2,TCom::Z2,TCom::Y1,TCom::Z1};
    comE0.para.runtype = TComE0::JOG;
    comE0.para.jogT    = TComE0::JOG_ADD;
    comE0.para.jogA    = axis[iCurCmd]+0xF;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&comE0));
}
/*************************************************************************
* ��������: on_btnUp_released
* ��    ��: �ͷ�UP��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnUp_released()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!widMana->bDialog)
        return;

    quint8 axis[] = {TCom::X,TCom::Y1,TCom::Z1,TCom::Y2,TCom::Z2,TCom::Y1,TCom::Z1};
    comE0.para.runtype = TComE0::JOG;
    comE0.para.jogT    = TComE0::JOG_STP;
    comE0.para.jogA    = axis[iCurCmd]+0xF;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&comE0));
}
/*************************************************************************
* ��������: on_btnDwn_pressed
* ��    ��: ����DOWN��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnDwn_pressed()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!widMana->bDialog)
        return;

    if(!widMana->bTri)
        return;

    quint8 axis[] = {TCom::X,TCom::Y1,TCom::Z1,TCom::Y2,TCom::Z2,TCom::Y1,TCom::Z1};
    comE0.para.runtype = TComE0::JOG;
    comE0.para.jogT    = TComE0::JOG_SUB;
    comE0.para.jogA    = axis[iCurCmd]+0xF;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&comE0));
}
/*************************************************************************
* ��������: on_btnDwn_released
* ��    ��: �ͷ�DOWN��ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnDwn_released()
{
    if(!ModeCheck(4,TComF0::AUTO,TComF0::SGL_CLE,TComF0::STEP,TComF0::RESTTING))
        return;

    if(!widMana->bDialog)
        return;

    quint8 axis[] = {TCom::X,TCom::Y1,TCom::Z1,TCom::Y2,TCom::Z2,TCom::Y1,TCom::Z1};
    comE0.para.runtype = TComE0::JOG;
    comE0.para.jogT    = TComE0::JOG_STP;
    comE0.para.jogA    = axis[iCurCmd]+0xF;
    QMutexLocker locker(&mutex_com);
    pComBuf2.push_back((TCom*)(&comE0));
}
/*************************************************************************
* ��������: on_btnHlp_clicked
* ��    ��: ���������ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnHlp_clicked()
{
    /*if(!usr.CheckUsr(TUsr::Operator))
        return;*/

    static bool bStp = true;
    if(bStp)
    {
        pComBuf1.clear();
        bStp = false;
    }
    else
    {
        pComBuf1.push_back((TCom*)(&comF0));
        bStp = true;
    }

    //widMana->pCurW->OnQdec(TWidget::PRS);


    //widMana->SwitchWM(&widMana->frm_hlp);
}
/*************************************************************************
* ��������: on_btnLft_clicked
* ��    ��: ������ϰ�ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnLft_clicked()
{
    widMana->pCurW->OnQdec(TWidget::AHD,prsTim.restart());
}
/*************************************************************************
* ��������: on_btnRht_clicked
* ��    ��: ������°�ť
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_btnRht_clicked()
{
    widMana->pCurW->OnQdec(TWidget::BCK, prsTim.restart());
}
/*************************************************************************
* ��������: on_sigKey
* ��    ��: ��Ӧ�ײ㰴���¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_sigKey(int dt)
{
    TDrvKey::MSG msg;
    msg.msg = dt;

    //printf("key:%x\n",msg.msgT);
    //ui->btnStus->setText(QString("%1").arg(msg.msgT,0,16));


    if(config.cfg.bBuzzK){
        if(msg.msgL == TDrvKey::UP)
            a5drv.buzzer_on();
        else if(msg.msgL == TDrvKey::DOWN)
            a5drv.buzzer_off();
    }

    /*if(msg.msgT == 0x10 ||
       msg.msgT == 0x11){
        return;
    }*/
    //��̬����
    if(msg.msgT == TDrvKey::TRI_KEY){
        if(msg.msgL == TDrvKey::UP){
            widMana->bTri = true;
        }else{
            widMana->bTri = false;

            if(comF0.rpara.sub_sta != TComF0::AUTO){
                QMutexLocker locker(&mutex_com);
                memset(&comE0.para,sizeof(comE0.para),0);
                comE0.para.runtype  = TComE0::STOP;
                pComBuf2.push_back((TCom*)&comE0);
            }
        }
        return;
    }
    //������
    if(msg.msgT == TDrvKey::QDEC_KEY){
        if(msg.msgL == TDrvKey::UP){
            if(config.bScrP){
                config.InitScrPT();
                return;
            }
            prsTim.start();
        }else if(msg.msgL == TDrvKey::DOWN){
            if(prsTim.restart() < 1000){
                //printf("pt1:%d\n",prsTim.restart());
                widMana->pCurW->OnQdec(TWidget::PRS, prsTim.restart());
            }else{
                //printf("pt2:%d\n",prsTim.restart());
                widMana->SwitchWM(&widMana->frm_fun);
            }
        }
        return;
    }

    if(widMana->bDialog)
        return;

    typedef void (MainWindow::*btnFun)();
    btnFun bf[] = {
        &MainWindow::on_btnLft_clicked,&MainWindow::on_btnRht_clicked,
        &MainWindow::on_btnbck_clicked,


        &MainWindow::on_btnDwn_pressed,&MainWindow::on_btnDwn_released,
        &MainWindow::on_btnUp_pressed,&MainWindow::on_btnUp_released,


        &MainWindow::on_btnWth_clicked,&MainWindow::on_btnRst_clicked,
        &MainWindow::on_btnPrg_clicked,&MainWindow::on_btnMana_clicked,
        &MainWindow::on_btnHlp_clicked,
        &MainWindow::on_btnStp_clicked,&MainWindow::on_btnSrt_clicked
    };

    int ibf=0;
    if((msg.msgT < TDrvKey::KEY3) && (msg.msgL == TDrvKey::UP)){
        ibf = msg.msgT;
    }else if(msg.msgT == TDrvKey::KEY3){
        if(msg.msgL == TDrvKey::UP){
            ibf = TDrvKey::KEY3;
        }else{
            ibf = TDrvKey::KEY3 + 1;
        }
    }else if(msg.msgT == TDrvKey::KEY4){
        if(msg.msgL == TDrvKey::UP){
            ibf = TDrvKey::KEY3 + 2;
        }else{
            ibf = TDrvKey::KEY3 + 3;
        }
    }else if((msg.msgT > TDrvKey::KEY4) && (msg.msgT < TDrvKey::TRI_KEY) && (msg.msgL == TDrvKey::UP)){
        ibf = msg.msgT + 2;
    }else{
        return;
    }

    (this->*bf[ibf])();

    config.InitScrPT();
}
/*************************************************************************
* ��������: on_sigQdec
* ��    ��: ��Ӧ�ײ�����¼�
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void MainWindow::on_sigQdec(int dt)
{
    //if(!widMana->bDialog)
    //    return;
    if(!config.bScrP)
        widMana->pCurW->OnQdec((TWidget::QDECT)dt,prsTim.restart());

    /*quint8 spd[]    ={com02.para[0].manS,com02.para[1].manS,com02.para[2].manS,com02.para[3].manS,
                      com02.para[4].manS,com02.para[0].manS,com02.para[1].manS};
    quint32 pos[]   ={comF0.rpara.xpos,comF0.rpara.y1pos,comF0.rpara.z1pos,comF0.rpara.y2pos,
                      comF0.rpara.z2pos,comF0.rpara.y1pos,comF0.rpara.z1pos};
    TCmd_Mov* cmd[] ={cmd_movX,cmd_movY1,cmd_movZ1,cmd_movY2,cmd_movZ2,cmd_movY,cmd_movZ};

    if(dt == TDrvQdec::UP){
        //ui->btnStus->setText("1");
        cmd[iCurCmd]->para.dist   =  pos[iCurCmd] + 10;
        cmd[iCurCmd]->para.spd    =  spd[iCurCmd];
        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)cmd[iCurCmd]);
    }else if(dt == TDrvQdec::DOWN){
        //ui->btnStus->setText("0");
        if(pos[iCurCmd] < 10)
            return;
        cmd[iCurCmd]->para.dist   =  pos[iCurCmd] - 10;
        cmd[iCurCmd]->para.spd    =  spd[iCurCmd];
        QMutexLocker locker(&mutex_com);
        pComBuf2.push_back((TCom*)cmd[iCurCmd]);
    }*/

    //printf("dist:%d\n",cmd[iCurCmd]->para.dist);
}

//==========================================================================================
// End of file.
//==========================================================================================

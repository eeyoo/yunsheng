/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: twidmana.h

* ��������: ���ڹ�����ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef TWIDMANA_H
#define TWIDMANA_H

#include <QWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFile>

#include "frm_fun.h"
#include "frm_teach.h"
#include "frm_mana.h"
#include "frm_run.h"
#include "frm_lang.h"
#include "frm_pros.h"
#include "frm_stack.h"
#include "frm_view.h"
#include "frm_prom.h"
#include "frm_setup.h"
#include "frm_mana_new.h"
#include "treadcmd.h"
#include "frm_monitor.h"
#include "frm_manufacturer.h"
#include "frm_hlp.h"

#include "mainwindow.h"

class TWidMana
{
public:
    TWidMana();

public:
    enum SHOWTYPE
    {
        ST_SHOW,
        ST_HIDE
    };
    struct Wid_Mana
    {
        QWidget *pWid;
        QString strT;
    };

    MainWindow  *mainW;

    QVector<Wid_Mana> widM;
    Frm_Fun     frm_fun;
    Frm_Teach   frm_teach;
    Frm_Mana    frm_mana;
    Frm_Run     frm_run;
    Frm_Lang    frm_lang;
    Frm_ProS    frm_pros;
    Frm_Stack   frm_stack;
    Frm_View    frm_view;
    Frm_ProM    frm_prom;
    Frm_Setup   frm_setup;
  Frm_Monitor   frm_monit;
Frm_Mana_New    frm_m_n;
Frm_Manufacturer frm_mftr;
    Frm_Hlp     frm_hlp;
public:
    void    InitWid(QWidget *pPar);
    void    SwitchWM(QWidget *pWidget,SHOWTYPE st = ST_SHOW);

    void    ShowPgmN(QString strN);

    void    SavePara();
    void    OpenPara();
    void    InitParaUI();
    void    CreateSysF();
public:
    QString strPgm;         //�����ļ����ļ���·��
    QString strSysPara;     //ϵͳ�����ļ���·��
    QString strFileN;       //��ǰ�����ļ���
    QString strStkP;        //�ѵ�����·��

    bool    bDialog;        //�д��ڵ��������α�Ĥ����
    bool    bTri;           //��̬����

public:
    TWidget *pCurW;
};

extern  TWidMana        *widMana;
//extern  QStandardItemModel *modelPro;
extern  QStandardItem   *itemP;

#endif // TWIDMANA_H

//==========================================================================================
// End of file.
//==========================================================================================

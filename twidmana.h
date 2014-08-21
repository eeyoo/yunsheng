/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: twidmana.h

* 功能描述: 窗口管理类头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
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
    QString strPgm;         //程序文件的文件夹路径
    QString strSysPara;     //系统参数文件的路径
    QString strFileN;       //当前程序文件名
    QString strStkP;        //堆叠程序路径

    bool    bDialog;        //有窗口弹出，屏蔽薄膜按键
    bool    bTri;           //三态开关

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

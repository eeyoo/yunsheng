/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: twarn.cpp

* 功能描述: 报警管理类

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include "twarn.h"
#include "ui_mainwindow.h"
#include "ui_frm_run.h"
#include "twidmana.h"

#include <QTextCodec>

/*************************************************************************
* 函数名称: TWarn
* 功   能: 构造函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TWarn::TWarn()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gbk"));//设置中文字体编码

    iMsgT = 0;

    WrnMsg wrnm;
    wrnm.wrnN   = W_FILES;
    wrnm.strM   = QObject::tr("程序下载成功！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_COM;
    wrnm.strM   = QObject::tr("通讯失败，请检查通讯线！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_SAVE;
    wrnm.strM   = QObject::tr("保存成功！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_ICHK;
    wrnm.strM   = QObject::tr("通用输出号为10~44，请重新输入！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_OCHK;
    wrnm.strM   = QObject::tr("通用输出号为11~28，请重新输入！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_STK_SVE;
    wrnm.strM   = QObject::tr("堆叠程序没有保存，请先保存！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_USR_AUTH;
    wrnm.strM   = QObject::tr("你的操作权限不够，请更换操作权限！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_PSW_INPUT;
    wrnm.strM   = QObject::tr("密码长度为8位，请重新输入！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_PSW_ERR;
    wrnm.strM   = QObject::tr("密码错误，请重新输入！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_PSW_MERR1;
    wrnm.strM   = QObject::tr("旧密码错误，请重新输入！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_PSW_MERR2;
    wrnm.strM   = QObject::tr("两次新密码输入不同，请重新输入！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_MODE_CHANGE;
    wrnm.strM   = QObject::tr("请先停止，再继续操作！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_NEWPRG;
    wrnm.strM   = QObject::tr("示教程序有更新，请重新下载！");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_NEWPRG_S;
    wrnm.strM   = QObject::tr("示教程序有更新，请先保存！");
    wrnM.push_back(wrnm);
}
/*************************************************************************
* 函数名称: ShowW2L
* 功   能: 显示报警信息
* 输入参数: warnN 报警号
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TWarn::ShowW2L(WRNTYPE warnN)
{
    for(int i=0;i<wrnM.size();i++)
    {
        if(warnN==wrnM[i].wrnN)
        {
            iMsgT = 0;
            wrnM[i].dt = QDateTime::currentDateTime();
            widMana->mainW->ui->lblWarn->setText(wrnM[i].strM);
            wrnH.push_back(wrnM[i]);
        }
    }
}
/*************************************************************************
* 函数名称: ClearW
* 功   能: 清除报警信息
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TWarn::ClearW()
{
    iMsgT++;
    if(iMsgT > 30){
        widMana->mainW->ui->lblWarn->setText(QString(""));
    }
}

TWarn   warn;       //警告消息类变量

//==========================================================================================
// End of file.
//==========================================================================================

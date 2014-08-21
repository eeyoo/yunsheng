/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: main.cpp

* 功能描述: 程序入口文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QTextStream>
#include <QTranslator>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "twidmana.h"
#include "treadcmd.h"
#include "tconfig.h"
#include "tapplication.h"


//#define QSS_USED

/*************************************************************************
* 函数名称: main
* 功    能: 程序入口函数，打开主窗口
* 输入参数: argc
			argv
* 输出参数: 无
* 返 回 值: 
*************************************************************************/
int main(int argc, char *argv[])
{
    TApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gbk"));//设置中文字体编码


    //设置界面风格
#ifdef QSS_USED
    QFile file(":/QSS/Res/QSS/ys.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    a.setStyleSheet(stylesheet);
#else
    QApplication::setStyle("plastique");
    //QApplication::setStyle("macintosh");
    //QApplication::setStyle("motif");
#endif

    QTranslator translator;
    config.OpenCfg();
    if(config.cfg.bEn){
        translator.load(":/Ys_En");
        a.installTranslator(&translator);
    }

    //打开主窗口
    MainWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.move((QApplication::desktop()->width()-w.width())/2,0);
    w.show();

    //读取命令配置文件
    readCmd.ReadCmd();

    //初始化全局变量

    //初始化窗口控制类
    widMana = new TWidMana;
    widMana -> InitWid(&w);

    return a.exec();
}

//==========================================================================================
// End of file.
//==========================================================================================

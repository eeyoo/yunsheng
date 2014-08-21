/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: main.cpp

* ��������: ��������ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
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
* ��������: main
* ��    ��: ������ں�������������
* �������: argc
			argv
* �������: ��
* �� �� ֵ: 
*************************************************************************/
int main(int argc, char *argv[])
{
    TApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gbk"));//���������������


    //���ý�����
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

    //��������
    MainWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.move((QApplication::desktop()->width()-w.width())/2,0);
    w.show();

    //��ȡ���������ļ�
    readCmd.ReadCmd();

    //��ʼ��ȫ�ֱ���

    //��ʼ�����ڿ�����
    widMana = new TWidMana;
    widMana -> InitWid(&w);

    return a.exec();
}

//==========================================================================================
// End of file.
//==========================================================================================

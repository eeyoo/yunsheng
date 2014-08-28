/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: tapplication.cpp

* 功能描述: 程序接口基类

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include "tapplication.h"
#include "twidmana.h"
#include "ui_mainwindow.h"
#include "qa5driver.h"
#include "tconfig.h"

/*************************************************************************
* 函数名称: TApplication
* 功   能: 构造函数
* 输入参数:argc 系统命令参数数 argv 系统命令 _internal 系统参数
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TApplication::TApplication(int &argc, char **argv, int _internal) :
        QApplication(argc,argv,QT_VERSION)
{

}
/*************************************************************************
* 函数名称: notify
* 功   能: 通知函数
* 输入参数:object 根类句柄 event 通知消息类型
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
bool TApplication::notify(QObject *object, QEvent *event)
{
    if(config.cfg.bBuzzD){
        if(event->type() == QEvent::MouseButtonPress){
            a5drv.buzzer_on();
        }else if(event->type() == QEvent::MouseButtonRelease){
            a5drv.buzzer_off();
        }
    }

    if(config.bScrP){
        if(event->type() == QEvent::MouseButtonRelease){
            config.InitScrPT();
            return true;
        }

        if(event->type() == QEvent::MouseButtonPress ||
               event->type() == QEvent::MouseButtonDblClick ||
               event->type() == QEvent::MouseMove){
            return true;
        }
    }else{
        if(event->type() == QEvent::MouseButtonRelease){
            config.InitScrPT();
        }
    }


    QApplication::notify(object,event);
}

//==========================================================================================
// End of file.
//==========================================================================================

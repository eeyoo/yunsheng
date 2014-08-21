/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: TConfig.cpp

* 功能描述: 系统配置类

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include "tconfig.h"
#include "qa5driver.h"
#include "dlg_authority.h"

#include <QFile>

/*************************************************************************
* 函数名称: TConfig
* 功   能: 构造函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TConfig::TConfig()
{
    memset(&cfg,0,sizeof(cfg));
}
/*************************************************************************
* 函数名称: OpenCfg
* 功   能: 读取系统配置
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TConfig::OpenCfg()
{
    QFile *file = new QFile();

#ifdef EMBEDED_ARM
    file->setFileName("/root/cfg");
#else
    file->setFileName("cfg");
#endif

    file->open(QIODevice::ReadOnly);
    file->reset();

    file->read((char*)(&cfg),sizeof(cfg));
    file->read((char*)(&usr.curUsr),sizeof(usr.curUsr));
    file->read((char*)(usr.usrP),sizeof(usr.usrP));

    file->close();
    file->deleteLater();

}
/*************************************************************************
* 函数名称: SaveCfg
* 功   能: 保存系统配置
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void TConfig::SaveCfg()
{
    QFile *file = new QFile();

#ifdef EMBEDED_ARM
    file->setFileName("/root/cfg");
#else
    file->setFileName("cfg");
#endif

    file->open(QIODevice::WriteOnly);
    file->reset();

    file->write((char*)(&cfg),sizeof(cfg));
    file->write((char*)(&usr.curUsr),sizeof(usr.curUsr));
    file->write((char*)(usr.usrP),sizeof(usr.usrP));

    file->close();
    file->deleteLater();

#ifdef EMBEDED_ARM
    system("sync");
#endif
}


TConfig     config;     //程序配置文件

//==========================================================================================
// End of file.
//==========================================================================================

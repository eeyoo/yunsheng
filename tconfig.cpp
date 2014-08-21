/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: TConfig.cpp

* ��������: ϵͳ������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include "tconfig.h"
#include "qa5driver.h"
#include "dlg_authority.h"

#include <QFile>

/*************************************************************************
* ��������: TConfig
* ��   ��: ���캯��
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TConfig::TConfig()
{
    memset(&cfg,0,sizeof(cfg));
}
/*************************************************************************
* ��������: OpenCfg
* ��   ��: ��ȡϵͳ����
* �������:
* �������: ��
* �� �� ֵ: ��
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
* ��������: SaveCfg
* ��   ��: ����ϵͳ����
* �������:
* �������: ��
* �� �� ֵ: ��
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


TConfig     config;     //���������ļ�

//==========================================================================================
// End of file.
//==========================================================================================
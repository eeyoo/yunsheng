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
    InitScrPT();
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

    eepromR();

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
/*************************************************************************
* ��������: DoScrPT
* ��   ��: ������Ļ����
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TConfig::DoScrPT()
{
    if(curPT > cfg.scrPT){
        bScrP = true;
    }
    curPT++;

    if(bScrP){
        a5drv.led_off(4);
    }else{
        a5drv.led_on(4);
    }
}
/*************************************************************************
* ��������: InitScrPT
* ��   ��: ��ʼ����Ļ����
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TConfig::InitScrPT()
{
    curPT = 0;
    bScrP = false;
}
/*************************************************************************
* ��������: eepromW
* ��   ��: ����д��eeprom
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TConfig::eepromW()
{
    a5drv.eepromW((char*)(&cfg.curPrd), 4);
}
/*************************************************************************
* ��������: eepromR
* ��   ��: ��eeprom��������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TConfig::eepromR()
{
    a5drv.eepromR((char*)(&cfg.curPrd), 4);
}




TConfig     config;     //���������ļ�

//==========================================================================================
// End of file.
//==========================================================================================

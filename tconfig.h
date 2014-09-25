/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: TConfig.h

* ��������: ϵͳ������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/


#ifndef TCONFIG_H
#define TCONFIG_H

class TConfig
{
public:
    TConfig();

    struct CONFIG{
        bool bEn;
        int  bckL;
        int  scrPT;
        int  curPrd;    //��ǰ��Ʒ��
        bool bBuzzD;
        bool bBuzzK;
    };

public:
    CONFIG cfg;
    int    curPT;
    bool   bScrP;
public:
    void OpenCfg();
    void SaveCfg();

    void DoScrPT();
    void InitScrPT();

    void eepromW();
    void eepromR();
};

extern  TConfig     config;     //���������ļ�

#endif // TCONFIG_H

//==========================================================================================
// End of file.
//==========================================================================================

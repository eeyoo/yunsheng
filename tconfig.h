/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: TConfig.h

* 功能描述: 系统配置类

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
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
        int  curPrd;    //当前产品数
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

extern  TConfig     config;     //程序配置文件

#endif // TCONFIG_H

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: qa5driver.h

* 功能描述: A5驱动程序头文件头文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.4.15

* 修	改:
**************************************************************************************/

#ifndef QA5DRIVER_H
#define QA5DRIVER_H

#define EMBEDED_ARM
//#ifdef EMBEDED_ARM

#include <QFile>
#include "at91_gpio.h"
#include "common.h"

//CAN通讯数据帧
struct CAN_Frame
{
    quint32 canId;  //CAN ID
    quint8 data[8]; //CAN数据
};

class QA5Driver
{
public:
    QA5Driver();
    ~QA5Driver();
private:
    void init_All_drv();
    bool Open_All_drv();

    bool Open_buzzer();
    bool Open_can();
    bool Open_led();
    bool Open_key();
    bool Open_qdec();
private:
    int fd_buzzer;
    int socket_can;
    int fd_led;
    int fd_key;
    int fd_qdec;

public:
    bool can_send(CAN_Frame *pframe);
    bool can_rcv(CAN_Frame *pframe);

    bool buzzer_on();
    bool buzzer_off();

    bool led_on(int iNo = 0);
    bool led_off(int iNo = 0);

    bool read_key(int *key_no,bool *key_lev);
    bool read_qdec(int *key_no,bool *key_lev);
};


extern QA5Driver a5drv;
//#endif

#endif // QA5DRIVER_H

//==========================================================================================
// End of file.
//==========================================================================================

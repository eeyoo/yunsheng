/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: qa5driver.cpp

* ��������: A5��������ӿ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#include "qa5driver.h"

#ifdef EMBEDED_ARM

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/socket.h>
#include <linux/input.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#endif

QA5Driver a5drv;

static GPIO_ATTR_ST gpios[] = {
    {"YS_LED0",YS_LED0},{"YS_LED1",YS_LED1},
    {"YS_LED2", YS_LED2},{"YS_LED3",YS_LED3},
    {"YS_LED4",YS_LED4}
};
#define DEV_QDEC         "/dev/input/event2"
#define QDEC_PD5         0x10d
#define QDEC_PD6         0x10e
#define QDEC_PD7         0x10f
#define QDEC_PD13        0x110

static KEY_ATTR g_keys[] = {
    {QDEC_PD5, "KEY_X0"}, {QDEC_PD6, "KEY_X1"},
    {QDEC_PD7, "KEY_X2"}, {QDEC_PD13, "KEY_X3"},
};

int KeyBuf[2]={0,0};

/*************************************************************************
* ��������: QA5Driver
* ��    ��: ���캯��
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
QA5Driver::QA5Driver()
{
    init_All_drv();

    Open_All_drv();
}
/*************************************************************************
* ��������: ~QA5Driver
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
QA5Driver::~QA5Driver()
{
#ifdef EMBEDED_ARM
    close(fd_buzzer);
    close(socket_can);
    close(fd_led);
    close(fd_key);
    close(fd_qdec);
#endif
}
/*************************************************************************
* ��������: init_All_drv
* ��    ��: ��ʼ�����е��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void QA5Driver::init_All_drv()
{
    fd_buzzer       = -1;
    socket_can      = -1;
    fd_led          = -1;
    fd_key          = -1;
    fd_qdec         = -1;
}
/*************************************************************************
* ��������: Open_All_drv
* ��    ��: �����е�����
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::Open_All_drv()
{
    Open_can();
    Open_led();
    Open_buzzer();
    Open_key();
    Open_qdec();
}
/*************************************************************************
* ��������: Open_qdec
* ��    ��: ����������
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::Open_qdec()
{
#ifdef EMBEDED_ARM
    fd_qdec = open(DEV_QDEC, O_RDONLY, 0);
    if(fd_qdec<0)
        return false;
    else
#endif
        return true;

}
/*************************************************************************
* ��������: read_qdec
* ��    ��: ��ȡ��������
* �������: ��
* �������: key_no	��ǰ��ֵ
			key_lev	��ǰ����״̬
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::read_qdec(int *key_no,bool *key_lev)
{
#ifdef EMBEDED_ARM
    EVENT_KEY_ST event;
    memset(&event, 0, sizeof(event));
    if (sizeof(event) != read(fd_qdec, &event, sizeof(event)))
    {
        //DEBUG_ERROR("event get error! errno = %d\n", errno);
        return false;
    }
    else if (EVENT_KEY == event.type)
    {
        *key_no=event.code;*key_lev=event.value;
        return true;
    }
#endif
    return false;

}
/*************************************************************************
* ��������: Open_key
* ��    ��: �򿪰�������
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::Open_key()
{
#ifdef EMBEDED_ARM
    fd_key = open(DEV_KEY, O_RDONLY, 0);
    if(fd_key<0)
        return false;
    else
#endif
        return true;
}
/*************************************************************************
* ��������: read_key
* ��    ��: ��ȡ����
* �������: ��
* �������: key_no	��ǰ��ֵ
			key_lev	��ǰ����״̬
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::read_key(int *key_no,bool *key_lev)
{
#ifdef EMBEDED_ARM
    static KEY_ATTR g_keys[] = {
        {KEY_X0_PC0, "KEY_X0"}, {KEY_X1_PC1, "KEY_X1"},
        {KEY_X2_PC2, "KEY_X2"}, {KEY_X3_PC3, "KEY_X3"},
        {KEY_X4_PC4, "KEY_X4"}, {KEY_X5_PC5, "KEY_X5"},
        {KEY_X6_PC6, "KEY_X6"}, {KEY_X7_PC7, "KEY_X7"},
        {KEY_Y0_PC8, "KEY_Y0"}, {KEY_Y1_PC9, "KEY_Y1"},
        {KEY_Y2_PC10, "KEY_Y2"}, {KEY_Y3_PC11, "KEY_Y3"},
        {KEY_Y4_PC12, "KEY_Y4"}, {KEY_Y5_PD5, "KEY_Y5"},
        {KEY_Y6_PD6, "KEY_Y6"}, {KEY_Y7_PD7, "KEY_Y7"},
        {KEY_Y8_PD25, "KEY_Y8"}, {KEY_Y9_PC13, "KEY_Y9"}
    };
    EVENT_KEY_ST event;
    memset(&event, 0, sizeof(event));
    //printf("1\n");
    if (sizeof(event) != read(fd_key, &event, sizeof(event)))
    {
        //DEBUG_ERROR("event get error! errno = %d\n", errno);
        return false;
    }
    else if (EVENT_KEY == event.type)
    {
        //printf("2code:%x\n",event.code);
        /* get key event */
        for (int i = 0; i < ARRAY_SIZE(g_keys); i++)
        {
            if (g_keys[i].code == event.code)
            {
                //DEBUG_INFO("%s %s\n", g_keys[i].key_name,
                //           (event.value ? EVENT_ACTION_PULLDOWN :EVENT_ACTION_RELEASEUP));
                *key_no=i;*key_lev=event.value;
                return true;
            }
        }
    }
#endif
    return false;
}
/*************************************************************************
* ��������: Open_led
* ��    ��: ��LED
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::Open_led()
{
#ifdef EMBEDED_ARM
    fd_led = open(DEV_GPIO, O_RDWR);
    if (fd_led < 0)
        return false;
    else
#endif
        return true;
}
/*************************************************************************
* ��������: led_on
* ��    ��: ����LED
* �������: LED���
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::led_on(int iNo/*=0*/)
{
#ifdef EMBEDED_ARM
    IOCTL_GPIO_ARG_ST leda;
    leda.gpio_index = gpios[iNo].gpio_index;
    leda.gpio_level = 1;

    return ioctl(fd_led,IOCTL_GPIO_LEVEL_SET,&leda);
#endif
    return false;
}
/*************************************************************************
* ��������: led_off
* ��    ��: �ر�LED
* �������: LED���
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::led_off(int iNo/* = 0*/)
{
#ifdef EMBEDED_ARM
    IOCTL_GPIO_ARG_ST leda;
    leda.gpio_index = gpios[iNo].gpio_index;
    leda.gpio_level = 0;

    return ioctl(fd_led,IOCTL_GPIO_LEVEL_SET,&leda);
#endif
    return false;
}
/*************************************************************************
* ��������: Open_can
* ��    ��: ��CAN
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::Open_can()
{
#ifdef EMBEDED_ARM
    /*struct sockaddr_can can_addr;
    struct ifreq ifr;
    unsigned long ul;

    if((socket_can  =  socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        //DEBUG_ERROR("open can socket error.");
        return false;
    }

    ul = 1;
    memset(&ifr, 1, sizeof(ifr));
    strcpy(ifr.ifr_name, DEV_CAN);
    if (RET_SUCCESS !=  ioctl(socket_can, SIOCGIFINDEX, &ifr))
    {
        //DEBUG_ERROR("ioctl SIOCGIFINDEX failed.");
        close(socket_can);
        return false;
    }

    memset(&can_addr, 0, sizeof(can_addr));
    can_addr.can_family  = AF_CAN;
    can_addr.can_ifindex = ifr.ifr_ifindex;



    if(bind(socket_can, (struct sockaddr *)&can_addr, sizeof(can_addr)) < 0)
    {
        //DEBUG_ERROR("bind can socket failed.");
        close(socket_can);
        return false;
    }*/

    struct sockaddr_can can_addr;
    struct ifreq ifr;

    if((socket_can = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        //DEBUG_ERROR("open can socket error.");
        return false;
    }

    struct timeval tm;
    tm.tv_sec = 1;
    tm.tv_usec = 0;//50000;
    setsockopt(socket_can,SOL_SOCKET,SO_RCVTIMEO,&tm,sizeof(tm));

    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, DEV_CAN);
    if (RET_SUCCESS != ioctl(socket_can, SIOCGIFINDEX, &ifr))
    {
        //DEBUG_ERROR("ioctl SIOCGIFINDEX failed.");
        close(socket_can);
        return false;
    }

    memset(&can_addr, 0, sizeof(can_addr));
    can_addr.can_family  = AF_CAN;
    can_addr.can_ifindex = ifr.ifr_ifindex;



    if(bind(socket_can, (struct sockaddr *)&can_addr, sizeof(can_addr)) < 0)
    {
        //DEBUG_ERROR("bind can socket failed.");
        close(socket_can);
        return false;
    }



    /*struct ifreq ifr;
    struct sockaddr_can can_addr;

    //socket_can = socket(AF_INET, SOCK_STREAM, 0);
    socket_can = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if(socket_can < 0) return false;

    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, DEV_CAN);
    if (RET_SUCCESS != ioctl(socket_can, SIOCGIFINDEX, &ifr))
    {
        //DEBUG_ERROR("ioctl SIOCGIFINDEX failed.");
        close(socket_can);
        return false;
    }

    //�Է�������ַ���ṹserv_addr
    int error=-1, len;
    len = sizeof(int);
    struct timeval tm;
    fd_set set;
    unsigned long ul = 1;
    ioctl(socket_can, FIONBIO, &ul); //����Ϊ������ģʽ

    memset(&can_addr, 0, sizeof(can_addr));
    can_addr.can_family  = AF_CAN;
    can_addr.can_ifindex = ifr.ifr_ifindex;
    if(bind(socket_can, (struct sockaddr *)&can_addr, sizeof(can_addr)) < 0)
    {
        //DEBUG_ERROR("bind can socket failed.");
        close(socket_can);
        return false;
    }
    else
    {
        tm.tv_sec = 2000;
        tm.tv_usec = 0;
        FD_ZERO(&set);
        FD_SET(socket_can, &set);
        if( select(socket_can+1, NULL, &set, NULL, &tm) > 0)
        {
            getsockopt(socket_can, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len);
            if(error == 0)
                return false;
        }
    }


    ul = 0;
    ioctl(socket_can, FIONBIO, &ul); //����Ϊ����ģʽ
    fprintf( stderr , "Connected!n");*/
#endif
    return true;
}
/*************************************************************************
* ��������: Open_buzzer
* ��    ��: �򿪷�����
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::Open_buzzer()
{
#ifdef EMBEDED_ARM
    fd_buzzer = open(DEV_BUZZER, O_RDWR);
    if(fd_buzzer<0)
        return false;
    else
#endif
        return true;

    /*if (fd_buzzer < 0)
    {
        //DEBUG_ERROR("open buzzer device %s error!\n", DEV_BUZZER);
        return false;
    }

    ret = ioctl(fd_buzzer, IOCTL_BUZZER_ON, arg);
    if (0 != ret)
    {
        //DEBUG_ERROR("errno = %d\n", ret);
    }
    else
    {
        sleep(1);
        ret = ioctl(fd_buzzer, IOCTL_BUZZER_OFF, arg);
        if (0 != ret)
        {
            //DEBUG_ERROR("errno = %d\n", ret);
        }
        else
        {
            //DEBUG_INFO("Buzzer Test OK.\n");
        }
    }*/
}
/*************************************************************************
* ��������: buzzer_on
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::buzzer_on()
{
#ifdef EMBEDED_ARM
    return ioctl(fd_buzzer, IOCTL_BUZZER_ON);
#endif
    return false;
}
/*************************************************************************
* ��������: buzzer_off
* ��    ��: ��������
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::buzzer_off()
{
#ifdef EMBEDED_ARM
    return ioctl(fd_buzzer, IOCTL_BUZZER_OFF);
#endif
    return false;
}
/*************************************************************************
* ��������: can_send
* ��    ��: ����CAN֡
* �������: pframe	��Ҫ���͵�CAN֡
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::can_send(CAN_Frame *pframe)
{
#ifdef EMBEDED_ARM
    struct can_frame canf;
    canf.can_id    = 0x123;//pframe->canId;
    canf.can_dlc   = CAN_DATA_LEN_MAX;
    memcpy(canf.data,pframe->data,8);

    if (sizeof(struct can_frame) != write(socket_can, &canf, sizeof(struct can_frame)))
    {
        return false;
    }
    else
    {
        return true;
    }
#endif
    return false;
}
/*************************************************************************
* ��������: can_rcv
* ��    ��: ����CAN֡
* �������: ��
* �������: pframe	���յ���CAN֡
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::can_rcv(CAN_Frame *pframe)
{
#ifdef EMBEDED_ARM
    struct can_frame canf;
    if (sizeof(struct can_frame) != read(socket_can, &canf, sizeof(struct can_frame)))
    {
        return false;
    }
    else
    {
        pframe->canId=canf.can_id;
        memcpy(pframe->data,canf.data,8);
        return true;
    }
    /*struct can_frame canf;
    if (sizeof(struct can_frame) != recv(socket_can, &canf, sizeof(struct can_frame),0))
    {
        return false;
    }
    else
    {
        pframe->canId=canf.can_id;
        memcpy(pframe->data,canf.data,8);
        return true;
    }*/

    /*struct can_frame canf;
    if (sizeof(struct can_frame) != recv(socket_can, &canf, sizeof(struct can_frame),MSG_DONTWAIT))
    {
        return false;
    }
    else
    {
        pframe->canId=canf.can_id;
        memcpy(pframe->data,canf.data,8);
        return true;
    }*/
#else
    return false;
#endif
}

//#endif

//==========================================================================================
// End of file.
//==========================================================================================

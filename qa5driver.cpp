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
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

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

static CAT24CW_S g_stCat24wc[] =
{
    {CAT24CW16, CAT24CW16_SLAVE_ADDR, CAT24CW16_CAPACITY_LEN},
    /* add chips attr in cat24wc family here if needed */
};

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
    close(fd_eeprom);
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
    fd_eeprom       = -1;
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
    Open_eeprom();
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
* ��������: Open_eeprom
* ��    ��: ��eeprom
* �������: ��
* �������: ��
* �� �� ֵ: �ɹ�true��ʧ��false
*************************************************************************/
bool QA5Driver::Open_eeprom()
{
#ifdef EMBEDED_ARM
    fd_eeprom = open(DEV_I2C_0, O_RDONLY, 0);
    if(fd_eeprom<0)
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
int QA5Driver::write_to_cat24wc(int fd, char *chip_name, int reg_addr,
                            char *data_buf, int data_len)
{
#ifdef EMBEDED_ARM
    CAT24CW_S *chip_info;
    char *msg_buf;
    int msg_buf_len = data_len + CAT24CW16_REG_ADDR_LEN;
    int ret;

    if ((NULL == chip_name) || (NULL == data_buf) ||
        (data_len > CAT24CW16_LIMIT_WR_LEN))
    {
        //DEBUG_ERROR("Invalid arguments!\n");
        return RET_FAILED;
    }

    chip_info = get_chip_info(chip_name);
    if(NULL == chip_info)
    {
        //DEBUG_ERROR("can't get the chip info!\n");
        return RET_FAILED;
    }

    msg_buf = (char *)malloc(msg_buf_len);
    if (NULL != msg_buf)
    {
        memset(msg_buf, 0, msg_buf_len);
        msg_buf[0] = reg_addr >> 8;
        msg_buf[1] = reg_addr & 0xff;
        memcpy(msg_buf + CAT24CW16_REG_ADDR_LEN, data_buf, data_len);

        ret = i2c_write(fd, chip_info->slave_addr, msg_buf, msg_buf_len);
    }
    else
    {
        //DEBUG_ERROR("msg_buf memory alloc error!\n");
        ret = RET_FAILED;
    }

    if (msg_buf)
    {
        free(msg_buf);
        msg_buf = NULL;
    }

    return ret;
#endif
    return 0;
}
int QA5Driver::i2c_write(int fd, int slave_addr, char *data_buf, int data_len)
{
#ifdef EMBEDED_ARM
    int ret;
    struct i2c_rdwr_ioctl_data write_opt;

    memset(&write_opt, 0, sizeof(write_opt));
    write_opt.nmsgs = 1;
    write_opt.msgs = (struct i2c_msg *)malloc(write_opt.nmsgs * sizeof(struct i2c_msg));
    if (NULL == write_opt.msgs)
    {
        //DEBUG_ERROR("write_opt.msgs memory alloc error!\n");
        return RET_FAILED;
    }
    memset(write_opt.msgs, 0, write_opt.nmsgs * sizeof(struct i2c_msg));

    write_opt.msgs[0].len = data_len;
    write_opt.msgs[0].addr = slave_addr;
    write_opt.msgs[0].buf = (__u8*)data_buf;

    ret = ioctl(fd, I2C_RDWR, (unsigned long)&write_opt);
    if (write_opt.nmsgs == ret)
    {
        ret = RET_SUCCESS;
    }
    else
    {
        ret = RET_FAILED;
    }

    if (write_opt.msgs)
    {
        free(write_opt.msgs);
        write_opt.msgs = NULL;
    }

    return ret;
#endif
    return 0;
}
int QA5Driver::read_from_cat24wc(int fd, char *chip_name, int reg_addr,
                             char *data_buf, int data_len)
{
#ifdef EMBEDED_ARM
    CAT24CW_S *chip_info;
    char reg_addr_buff[CAT24CW16_REG_ADDR_LEN];
    int ret;

    if ((NULL == chip_name) || (NULL == data_buf) ||
        (data_len > CAT24CW16_LIMIT_RD_LEN))
    {
        //DEBUG_ERROR("Invalid arguments!\n");
        return RET_FAILED;
    }

    chip_info = get_chip_info(chip_name);
    if(NULL == chip_info)
    {
        //DEBUG_ERROR("can't get the chip info!\n");
        return RET_FAILED;
    }

    memset(reg_addr_buff, 0, sizeof(reg_addr_buff));
    reg_addr_buff[0] = reg_addr >> 8;
    reg_addr_buff[1] = reg_addr & 0xff;

    return i2c_read(fd, chip_info->slave_addr, data_buf, data_len, reg_addr_buff, CAT24CW16_REG_ADDR_LEN);
#endif
    return 0;
}
int QA5Driver::i2c_read(int fd,
                    int slave_addr,
                    char *data_buf,
                    int data_len,
                    char *reg_addr,
                    int reg_size)
{
#ifdef EMBEDED_ARM
    int ret;
    struct i2c_rdwr_ioctl_data read_opt;

    memset(&read_opt, 0, sizeof(read_opt));

    read_opt.nmsgs = 2;
    read_opt.msgs = (struct i2c_msg *)malloc(read_opt.nmsgs * sizeof(struct i2c_msg));
    if (NULL == read_opt.msgs)
    {
        //DEBUG_ERROR("read_opt.msgs memory alloc error!\n");
        return RET_FAILED;
    }

    memset(read_opt.msgs, 0, read_opt.nmsgs * sizeof(struct i2c_msg));

    read_opt.msgs[0].len = reg_size;
    read_opt.msgs[0].addr = slave_addr;
    read_opt.msgs[0].buf = (__u8*)reg_addr;

    read_opt.msgs[1].len = data_len;
    read_opt.msgs[1].flags = I2C_M_RD;
    read_opt.msgs[1].addr = slave_addr;
    read_opt.msgs[1].buf = (__u8*)data_buf;

    ret = ioctl(fd, I2C_RDWR, (unsigned long)&read_opt);
    if (read_opt.nmsgs == ret)
    {
        ret = RET_SUCCESS;
    }
    else
    {
        ret = RET_FAILED;
    }

    free(read_opt.msgs);
    read_opt.msgs = NULL;

    return ret;
#endif
    return 0;
}
CAT24CW_S* QA5Driver::get_chip_info(char *name)
{
#ifdef EMBEDED_ARM
    int i;
    CAT24CW_S *chip_info = NULL;

    for (i = 0; i < sizeof(CAT24CW_S) / sizeof(CAT24CW_S); i++)
    {
        if (!strcasecmp(name, g_stCat24wc[i].chip))
        {
            chip_info = &g_stCat24wc[i];
            break;
        }
    }

    return chip_info;
#endif
    return NULL;
}
bool QA5Driver::eepromW(char* data, int len)
{
    int ret;
    ret = write_to_cat24wc(fd_eeprom, CAT24CW16, 0x00, data, len);
    return (bool)ret;
}
bool QA5Driver::eepromR(char* data, int len)
{
    int ret;
    ret = read_from_cat24wc(fd_eeprom, CAT24CW16, 0x00, data, len);
    return (bool)ret;
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

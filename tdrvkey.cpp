/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: tdrvkey.cpp

* ��������: ����ɨ���߳�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include "tdrvkey.h"
#include "qa5driver.h"

/*************************************************************************
* ��������: TDrvKey
* ��   ��: ������
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TDrvKey::TDrvKey(QObject *parent) :
    QThread(parent)
{

}
/*************************************************************************
* ��������: run
* ��   ��: ɨ�躯��
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TDrvKey::run()
{

    while(1)
    {
        int key_no;bool key_lev;
        bool bret = a5drv.read_key(&key_no,&key_lev);

        //printf("key000\n");
        if(bret){
            //printf("no:%x,lev:%x\n",key_no,key_lev);
            emitMsg((DRVTYP)(key_no),(DRVLEV)key_lev);
        }
    }
}
/*************************************************************************
* ��������: emitMSG
* ��   ��: ���Ͱ�����Ϣ
* �������: dt ����ֵ dl ����״̬
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TDrvKey::emitMsg(DRVTYP dt,DRVLEV dl)
{
    MSG msg;
    msg.msgT = dt;
    msg.msgL = dl;
    emit sigKey((int)msg.msg);
}


TDrvKey drv_key;      //�ײ�����ɨ���߳�

//==========================================================================================
// End of file.
//==========================================================================================
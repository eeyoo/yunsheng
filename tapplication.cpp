/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: tapplication.cpp

* ��������: ����ӿڻ���

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include "tapplication.h"
#include "twidmana.h"
#include "ui_mainwindow.h"
#include "qa5driver.h"
#include "tconfig.h"

/*************************************************************************
* ��������: TApplication
* ��   ��: ���캯��
* �������:argc ϵͳ��������� argv ϵͳ���� _internal ϵͳ����
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TApplication::TApplication(int &argc, char **argv, int _internal) :
        QApplication(argc,argv,QT_VERSION)
{

}
/*************************************************************************
* ��������: notify
* ��   ��: ֪ͨ����
* �������:object ������ event ֪ͨ��Ϣ����
* �������: ��
* �� �� ֵ: ��
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

/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: twarn.cpp

* ��������: ����������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include "twarn.h"
#include "ui_mainwindow.h"
#include "ui_frm_run.h"
#include "twidmana.h"

#include <QTextCodec>

/*************************************************************************
* ��������: TWarn
* ��   ��: ���캯��
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TWarn::TWarn()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gbk"));//���������������

    iMsgT = 0;

    WrnMsg wrnm;
    wrnm.wrnN   = W_FILES;
    wrnm.strM   = QObject::tr("�������سɹ���");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_COM;
    wrnm.strM   = QObject::tr("ͨѶʧ�ܣ�����ͨѶ�ߣ�");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_SAVE;
    wrnm.strM   = QObject::tr("����ɹ���");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_ICHK;
    wrnm.strM   = QObject::tr("ͨ�������Ϊ10~44�����������룡");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_OCHK;
    wrnm.strM   = QObject::tr("ͨ�������Ϊ11~28�����������룡");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_STK_SVE;
    wrnm.strM   = QObject::tr("�ѵ�����û�б��棬���ȱ��棡");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_USR_AUTH;
    wrnm.strM   = QObject::tr("��Ĳ���Ȩ�޲��������������Ȩ�ޣ�");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_PSW_INPUT;
    wrnm.strM   = QObject::tr("���볤��Ϊ8λ�����������룡");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_PSW_ERR;
    wrnm.strM   = QObject::tr("����������������룡");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_PSW_MERR1;
    wrnm.strM   = QObject::tr("������������������룡");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_PSW_MERR2;
    wrnm.strM   = QObject::tr("�������������벻ͬ�����������룡");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_MODE_CHANGE;
    wrnm.strM   = QObject::tr("����ֹͣ���ټ���������");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_NEWPRG;
    wrnm.strM   = QObject::tr("ʾ�̳����и��£����������أ�");
    wrnM.push_back(wrnm);

    wrnm.wrnN   = W_NEWPRG_S;
    wrnm.strM   = QObject::tr("ʾ�̳����и��£����ȱ��棡");
    wrnM.push_back(wrnm);
}
/*************************************************************************
* ��������: ShowW2L
* ��   ��: ��ʾ������Ϣ
* �������: warnN ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TWarn::ShowW2L(WRNTYPE warnN)
{
    for(int i=0;i<wrnM.size();i++)
    {
        if(warnN==wrnM[i].wrnN)
        {
            iMsgT = 0;
            wrnM[i].dt = QDateTime::currentDateTime();
            widMana->mainW->ui->lblWarn->setText(wrnM[i].strM);
            wrnH.push_back(wrnM[i]);
        }
    }
}
/*************************************************************************
* ��������: ClearW
* ��   ��: ���������Ϣ
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
void TWarn::ClearW()
{
    iMsgT++;
    if(iMsgT > 30){
        widMana->mainW->ui->lblWarn->setText(QString(""));
    }
}

TWarn   warn;       //������Ϣ�����

//==========================================================================================
// End of file.
//==========================================================================================

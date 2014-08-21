/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: dlg_authority.h

* ��������: �û�������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef DLG_AUTHORITY_H
#define DLG_AUTHORITY_H

#include <QDialog>
#include <QSignalMapper>

#include "twarn.h"
#include "twidmana.h"
#include "ui_mainwindow.h"

namespace Ui {
class Dlg_Authority;
}

class Dlg_Authority : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Authority(QWidget *parent = 0);
    ~Dlg_Authority();

private:
    QSignalMapper  sglMapL;

private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
    void on_le_clicked(int ile);

private:
    Ui::Dlg_Authority *ui;
};



//�û��࣬�����û�Ȩ��
class TUsr
{
public:
    enum USR
    {
        Operator,Administrator,Manufacturer
    };
#pragma pack(1)
    struct Usr_Psw{
        USR     usr;
        quint8  psw[8];
    };
#pragma pack()

    TUsr(){
        memset(usrP,'8',sizeof(Usr_Psw)*3);
        usrP[0].usr = Operator;
        usrP[1].usr = Administrator;
        usrP[2].usr = Manufacturer;

        curUsr = Operator;
    }
    ~TUsr(){}

public:
    bool CheckUsr(USR usr)      //�жϲ���Ȩ��
    {
        if(curUsr < usr){
            warn.ShowW2L(TWarn::W_USR_AUTH);
            return false;
        }
        else
            return true;
    }
    void SetCurUsr(USR curU){
        curUsr = curU;

        QString strU[] = {QObject::tr("����Ա"),QObject::tr("����Ա"),QObject::tr("����")};
        widMana->mainW->ui->btnUsr->setText(strU[curUsr]);
    }

public:
    USR curUsr;
    Usr_Psw usrP[3];
};

extern bool ModeCheck(int modeC, ...);

extern TUsr usr;

#endif // DLG_AUTHORITY_H

//==========================================================================================
// End of file.
//==========================================================================================

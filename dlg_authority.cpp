/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_authority.cpp

* 功能描述: 用户管理窗口

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include "dlg_authority.h"
#include "ui_dlg_authority.h"
#include "dlg_keyboard.h"
#include "twarn.h"
#include "tconfig.h"
#include "qa5driver.h"
#include "twidmana.h"
#include "tcmd.h"

/*************************************************************************
* 函数名称: Dlg_Authority
* 功   能: 构造函数
* 输入参数: QWidget *parent 父类句柄
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Authority::Dlg_Authority(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Authority)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);


    TLineEdit *le[] = {ui->leLPsw,ui->leNPsw,ui->leOPsw,ui->leNPswA};
    for(int i = 0;i<sizeof(le)/sizeof(TLineEdit*);i++)
    {
        sglMapL.setMapping(le[i],i);
        connect(le[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_le_clicked(int)));

    QRadioButton* rb[] = {ui->rb1,ui->rb2,ui->rb3,ui->rb4,ui->rb5,ui->rb6};
    rb[usr.curUsr]->setChecked(true);
    rb[usr.curUsr + 3]->setChecked(true);

    ui->tabw->setCurrentIndex(0);

    a5drv.buzzer_off();

    widMana->bDialog = true;
}
/*************************************************************************
* 函数名称: Dlg_Authority
* 功   能: 析构函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Authority::~Dlg_Authority()
{
    delete ui;
}
/*************************************************************************
* 函数名称: on_btnOk_clicked
* 功   能: 点击确定按钮
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Authority::on_btnOk_clicked()
{
    //TUsr::CheckUsr(TUsr::Operator);
    int index = ui->tabw->currentIndex();
    if(index == 0){
        QString strP = ui->leLPsw->text();
        QRadioButton* rb[] = {ui->rb1,ui->rb2,ui->rb3};
        int iUsr = 0;
        for(iUsr = 0; iUsr < sizeof(rb)/sizeof(QRadioButton*); iUsr++){
            if(rb[iUsr]->isChecked())
                break;
        }

        QString str = QString("%1%2%3%4%5%6%7%8").arg((char)usr.usrP[iUsr].psw[0])
                                                 .arg((char)usr.usrP[iUsr].psw[1])
                                                 .arg((char)usr.usrP[iUsr].psw[2])
                                                 .arg((char)usr.usrP[iUsr].psw[3])
                                                 .arg((char)usr.usrP[iUsr].psw[4])
                                                 .arg((char)usr.usrP[iUsr].psw[5])
                                                 .arg((char)usr.usrP[iUsr].psw[6])
                                                 .arg((char)usr.usrP[iUsr].psw[7]);
        if(str == strP){
            usr.SetCurUsr((TUsr::USR)iUsr);
            config.SaveCfg();
            widMana->bDialog = false;
            QDialog::accept();
        }else{
            warn.ShowW2L(TWarn::W_PSW_ERR);
        }
    }else if(index == 1){
        QString strPO = ui->leOPsw->text();
        QString strPN = ui->leNPsw->text();
        QString strPNA = ui->leNPswA->text();

        QRadioButton* rb[] = {ui->rb4,ui->rb5,ui->rb6};
        int iUsr = 0;
        for(iUsr = 0; iUsr < sizeof(rb)/sizeof(QRadioButton*); iUsr++){
            if(rb[iUsr]->isChecked())
                break;
        }

        QString str = QString("%1%2%3%4%5%6%7%8").arg((char)usr.usrP[iUsr].psw[0])
                                                 .arg((char)usr.usrP[iUsr].psw[1])
                                                 .arg((char)usr.usrP[iUsr].psw[2])
                                                 .arg((char)usr.usrP[iUsr].psw[3])
                                                 .arg((char)usr.usrP[iUsr].psw[4])
                                                 .arg((char)usr.usrP[iUsr].psw[5])
                                                 .arg((char)usr.usrP[iUsr].psw[6])
                                                 .arg((char)usr.usrP[iUsr].psw[7]);

        if(str != strPO){
            warn.ShowW2L(TWarn::W_PSW_MERR1);
            //QDialog::reject();
        }else if(strPN != strPNA){
            warn.ShowW2L(TWarn::W_PSW_MERR2);
            //QDialog::reject();
        }else{
            for(int i = 0; i < 8; i++){
                usr.usrP[iUsr].psw[i] = strPN.at(i).toLatin1();
            }
            usr.SetCurUsr((TUsr::USR)iUsr);
            config.SaveCfg();
            widMana->bDialog = false;
            QDialog::accept();
        }
    }
}
/*************************************************************************
* 函数名称: on_btnCancel_clicked
* 功   能: 点击取消按钮
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Authority::on_btnCancel_clicked()
{
    widMana->bDialog = false;
    QDialog::reject();
}
/*************************************************************************
* 函数名称: on_le_clicked
* 功   能: 点击文本框
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Authority::on_le_clicked(int ile)
{
    Dlg_Keyboard dlg;
    dlg.setModal(true);
    if(dlg.exec() == QDialog::Accepted)
    {
        if(dlg.m_str.length() != 8){
            warn.ShowW2L(TWarn::W_PSW_INPUT);
            return;
        }
        TLineEdit *le[] = {ui->leLPsw,ui->leNPsw,ui->leOPsw,ui->leNPswA};
        le[ile]->setText(dlg.m_str);
    }
}
/*************************************************************************
* 函数名称: ModeCheck
* 功   能: 判断操作模式的切换
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
bool ModeCheck(int modeC, ...)
{
    int *mode = (int*)((&modeC) + 1);
    for(int i = 0; i < modeC; i++){
        if(comF0.rpara.sub_sta == *(mode + i)){
            warn.ShowW2L(TWarn::W_MODE_CHANGE);
            return false;
        }
    }

    return true;
}

TUsr usr;

//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: twidget.cpp

* 功能描述: 窗口类基类

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include "twidget.h"
#include "tlineedit.h"

#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>
#include <QTableView>
#include <QTableWidget>
#include <QComboBox>

/*************************************************************************
* 函数名称: TWidget
* 功   能: 构造函数
* 输入参数: parent 根类句柄
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TWidget::TWidget(QWidget *parent) :
    QWidget(parent)
{
}
/*************************************************************************
* 函数名称: DoAhd
* 功   能: 旋转编码器前进
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoAhd(QWidget* pW, int *pT)
{
    QString strN[] = {"QPushButton","TLineEdit","QCheckBox","QRadioButton",
                     "QComboBox","QTableView","QTableWidget"};
    typedef bool (TWidget::*AhdFun)(QWidget*, int *);
    AhdFun af[] = {
        &TWidget::DoAhd_PushButton,&TWidget::DoAhd_LineEdit,
        &TWidget::DoAhd_CheckBox,&TWidget::DoAhd_RadioButton,
        &TWidget::DoAhd_ComboBox,&TWidget::DoAhd_TableView,
        &TWidget::DoAhd_TableWidget
    };

    for(int i = 0; i < sizeof(af)/sizeof(AhdFun); i++){
        if(pW->metaObject()->className() == strN[i]){
            return (this->*af[i])(pW,pT);
        }
    }
}
/*************************************************************************
* 函数名称: DoAhd_PushButton
* 功   能: 旋转编码器前进
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoAhd_PushButton(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoAhd_LineEdit
* 功   能: 旋转编码器前进
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoAhd_LineEdit(QWidget* pW, int *pT)
{
    TLineEdit *le   = dynamic_cast<TLineEdit *>(pW);
    QString   strT  = le->text();

    if(strT.contains(".")){
        double db = strT.toDouble() + 0.01;
        le->setText(QString::number(db,'f',2));
    }else{
        le->setText(QString("%1").arg(strT.toInt() + 1));
    }
    return false;
}
/*************************************************************************
* 函数名称: DoAhd_CheckBox
* 功   能: 旋转编码器前进
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoAhd_CheckBox(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoAhd_RadioButton
* 功   能: 旋转编码器前进
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoAhd_RadioButton(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoAhd_ComboBox
* 功   能: 旋转编码器前进
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoAhd_ComboBox(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoAhd_TableView
* 功   能: 旋转编码器前进
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoAhd_TableView(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoAhd_TableWidget
* 功   能: 旋转编码器前进
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoAhd_TableWidget(QWidget* pW, int *pT)
{
    return false;
}

/*************************************************************************
* 函数名称: DoBck
* 功   能: 旋转编码器后退
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoBck(QWidget* pW, int *pT)
{
    QString strN[] = {"QPushButton","TLineEdit","QCheckBox","QRadioButton",
                     "QComboBox","QTableView","QTableWidget"};
    typedef bool (TWidget::*BckFun)(QWidget*, int *);
    BckFun bf[] = {
        &TWidget::DoBck_PushButton,&TWidget::DoBck_LineEdit,
        &TWidget::DoBck_CheckBox,&TWidget::DoBck_RadioButton,
        &TWidget::DoBck_ComboBox,&TWidget::DoBck_TableView,
        &TWidget::DoBck_TableWidget
    };

    for(int i = 0; i < sizeof(bf)/sizeof(BckFun); i++){
        if(pW->metaObject()->className() == strN[i]){
            return (this->*bf[i])(pW,pT);
        }
    }
}
/*************************************************************************
* 函数名称: DoBck_PushButton
* 功   能: 旋转编码器后退
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoBck_PushButton(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoBck_LineEdit
* 功   能: 旋转编码器后退
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoBck_LineEdit(QWidget* pW, int *pT)
{
    TLineEdit *le   = dynamic_cast<TLineEdit *>(pW);
    QString   strT  = le->text();

    if(strT.contains(".")){
        double db = strT.toDouble() - 0.01;
        if(db < 0)
            db = 0.00;

        le->setText(QString::number(db,'f',2));
    }else{
        int iT = strT.toInt() - 1;
        if(iT < 0)
            iT = 0;

        le->setText(QString("%1").arg(iT));
    }
    return false;
}
/*************************************************************************
* 函数名称: DoBck_CheckBox
* 功   能: 旋转编码器后退
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoBck_CheckBox(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoBck_RadioButton
* 功   能: 旋转编码器后退
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoBck_RadioButton(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoBck_ComboBox
* 功   能: 旋转编码器后退
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoBck_ComboBox(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoBck_TableView
* 功   能: 旋转编码器后退
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoBck_TableView(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoBck_TableWidget
* 功   能: 旋转编码器后退
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoBck_TableWidget(QWidget* pW, int *pT)
{
    return false;
}


/*************************************************************************
* 函数名称: DoPrs
* 功   能: 旋转编码器按下
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoPrs(QWidget* pW, int *pT)
{
    QString strN[] = {"QPushButton","TLineEdit","QCheckBox","QRadioButton",
                     "QComboBox","QTableView","QTableWidget"};
    typedef bool (TWidget::*PrsFun)(QWidget*, int *);
    PrsFun pf[] = {
        &TWidget::DoPrs_PushButton,&TWidget::DoPrs_LineEdit,
        &TWidget::DoPrs_CheckBox,&TWidget::DoPrs_RadioButton,
        &TWidget::DoPrs_ComboBox,&TWidget::DoPrs_TableView,
        &TWidget::DoPrs_TableWidget
    };

    for(int i = 0; i < sizeof(pf)/sizeof(PrsFun); i++){
        if(pW->metaObject()->className() == strN[i]){
            return (this->*pf[i])(pW,pT);
        }
    }
}
/*************************************************************************
* 函数名称: DoPrs_PushButton
* 功   能: 旋转编码器按下
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoPrs_PushButton(QWidget* pW, int *pT)
{
    QPushButton *btn = dynamic_cast<QPushButton *>(pW);
    btn->click();
    return false;
}
/*************************************************************************
* 函数名称: DoPrs_LineEdit
* 功   能: 旋转编码器按下
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoPrs_LineEdit(QWidget* pW, int *pT)
{
    if((*pT) == 0)
        return true;
    else
        return false;
}
/*************************************************************************
* 函数名称: DoPrs_CheckBox
* 功   能: 旋转编码器按下
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoPrs_CheckBox(QWidget* pW, int *pT)
{
    QCheckBox *cb   = dynamic_cast<QCheckBox *>(pW);
    cb->setChecked(!cb->checkState());
    return false;
}
/*************************************************************************
* 函数名称: DoPrs_RadioButton
* 功   能: 旋转编码器按下
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoPrs_RadioButton(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoPrs_ComboBox
* 功   能: 旋转编码器按下
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoPrs_ComboBox(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoPrs_TableView
* 功   能: 旋转编码器按下
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoPrs_TableView(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* 函数名称: DoPrs_TableWidget
* 功   能: 旋转编码器按下
* 输入参数: pW 控件句柄 pT 控件按下次数
* 输出参数: true 成功 false 失败
* 返 回 值: 无
*************************************************************************/
bool TWidget::DoPrs_TableWidget(QWidget* pW, int *pT)
{
    return false;
}
//==========================================================================================
// End of file.
//==========================================================================================

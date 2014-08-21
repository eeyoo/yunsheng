/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: twidget.cpp

* ��������: ���������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
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
* ��������: TWidget
* ��   ��: ���캯��
* �������: parent ������
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TWidget::TWidget(QWidget *parent) :
    QWidget(parent)
{
}
/*************************************************************************
* ��������: DoAhd
* ��   ��: ��ת������ǰ��
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
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
* ��������: DoAhd_PushButton
* ��   ��: ��ת������ǰ��
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoAhd_PushButton(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoAhd_LineEdit
* ��   ��: ��ת������ǰ��
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
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
* ��������: DoAhd_CheckBox
* ��   ��: ��ת������ǰ��
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoAhd_CheckBox(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoAhd_RadioButton
* ��   ��: ��ת������ǰ��
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoAhd_RadioButton(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoAhd_ComboBox
* ��   ��: ��ת������ǰ��
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoAhd_ComboBox(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoAhd_TableView
* ��   ��: ��ת������ǰ��
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoAhd_TableView(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoAhd_TableWidget
* ��   ��: ��ת������ǰ��
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoAhd_TableWidget(QWidget* pW, int *pT)
{
    return false;
}

/*************************************************************************
* ��������: DoBck
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
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
* ��������: DoBck_PushButton
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoBck_PushButton(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoBck_LineEdit
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
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
* ��������: DoBck_CheckBox
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoBck_CheckBox(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoBck_RadioButton
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoBck_RadioButton(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoBck_ComboBox
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoBck_ComboBox(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoBck_TableView
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoBck_TableView(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoBck_TableWidget
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoBck_TableWidget(QWidget* pW, int *pT)
{
    return false;
}


/*************************************************************************
* ��������: DoPrs
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
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
* ��������: DoPrs_PushButton
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoPrs_PushButton(QWidget* pW, int *pT)
{
    QPushButton *btn = dynamic_cast<QPushButton *>(pW);
    btn->click();
    return false;
}
/*************************************************************************
* ��������: DoPrs_LineEdit
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoPrs_LineEdit(QWidget* pW, int *pT)
{
    if((*pT) == 0)
        return true;
    else
        return false;
}
/*************************************************************************
* ��������: DoPrs_CheckBox
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoPrs_CheckBox(QWidget* pW, int *pT)
{
    QCheckBox *cb   = dynamic_cast<QCheckBox *>(pW);
    cb->setChecked(!cb->checkState());
    return false;
}
/*************************************************************************
* ��������: DoPrs_RadioButton
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoPrs_RadioButton(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoPrs_ComboBox
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoPrs_ComboBox(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoPrs_TableView
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoPrs_TableView(QWidget* pW, int *pT)
{
    return false;
}
/*************************************************************************
* ��������: DoPrs_TableWidget
* ��   ��: ��ת����������
* �������: pW �ؼ���� pT �ؼ����´���
* �������: true �ɹ� false ʧ��
* �� �� ֵ: ��
*************************************************************************/
bool TWidget::DoPrs_TableWidget(QWidget* pW, int *pT)
{
    return false;
}
//==========================================================================================
// End of file.
//==========================================================================================

/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: twidget.h

* ��������: ���������

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef TWIDGET_H
#define TWIDGET_H

#include <QWidget>

class TWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TWidget(QWidget *parent = 0);

    enum QDECT{
        AHD,BCK,PRS
    };

    virtual void OnQdec(QDECT qt){}          //��Ӧ��ת����
protected:
    bool DoAhd(QWidget* pW, int *pT);
    bool DoAhd_PushButton(QWidget* pW, int *pT);
    bool DoAhd_LineEdit(QWidget* pW, int *pT);
    bool DoAhd_CheckBox(QWidget* pW, int *pT);
    bool DoAhd_RadioButton(QWidget* pW, int *pT);
    bool DoAhd_ComboBox(QWidget* pW, int *pT);
    bool DoAhd_TableView(QWidget* pW, int *pT);
    bool DoAhd_TableWidget(QWidget* pW, int *pT);

    bool DoBck(QWidget* pW, int *pT);
    bool DoBck_PushButton(QWidget* pW, int *pT);
    bool DoBck_LineEdit(QWidget* pW, int *pT);
    bool DoBck_CheckBox(QWidget* pW, int *pT);
    bool DoBck_RadioButton(QWidget* pW, int *pT);
    bool DoBck_ComboBox(QWidget* pW, int *pT);
    bool DoBck_TableView(QWidget* pW, int *pT);
    bool DoBck_TableWidget(QWidget* pW, int *pT);

    bool DoPrs(QWidget* pW, int *pT);
    bool DoPrs_PushButton(QWidget* pW, int *pT);
    bool DoPrs_LineEdit(QWidget* pW, int *pT);
    bool DoPrs_CheckBox(QWidget* pW, int *pT);
    bool DoPrs_RadioButton(QWidget* pW, int *pT);
    bool DoPrs_ComboBox(QWidget* pW, int *pT);
    bool DoPrs_TableView(QWidget* pW, int *pT);
    bool DoPrs_TableWidget(QWidget* pW, int *pT);
signals:

public slots:

};

#endif // TWIDGET_H

//==========================================================================================
// End of file.
//==========================================================================================

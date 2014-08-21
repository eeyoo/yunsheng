/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: twidget.h

* 功能描述: 窗口类基类

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
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

    virtual void OnQdec(QDECT qt){}          //响应旋转编码
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

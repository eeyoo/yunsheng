/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: tlineedit.h

* ��������: �Զ���QLineEdit��ͷ�ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.4.15

* ��	��:
**************************************************************************************/

#ifndef TLineEdit_H
#define TLineEdit_H
 
#include <QLineEdit>
#include <QMouseEvent>
 
class TLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit TLineEdit(QWidget *parent = 0);
protected:
    //��дmousePressEvent�¼�
    virtual void mousePressEvent(QMouseEvent *event);
public:
    int iMark;
signals:
    //�Զ���clicked()�ź�,��mousePressEvent�¼�����ʱ����
    void clicked();
 
public slots:
 
};
 
#endif // TLineEdit_H

//==========================================================================================
// End of file.
//==========================================================================================

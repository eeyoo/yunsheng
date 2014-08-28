/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: ttblviewf.h

* ��������: �Զ���QTableView��

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.8.23

* ��	��:
**************************************************************************************/

#ifndef TTBLVIEWF_H
#define TTBLVIEWF_H

#include <QTableView>

class TTblViewF : public QTableView
{
    Q_OBJECT
public:
    explicit TTblViewF(QWidget *parent = 0);

signals:

public slots:
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

};

#endif // TTBLVIEWF_H


//==========================================================================================
// End of file.
//==========================================================================================

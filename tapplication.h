/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: tapplication.h

* ��������: ����ӿڻ���

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#ifndef TAPPLICATION_H
#define TAPPLICATION_H

#include <QApplication>

class TApplication : public QApplication
{
    Q_OBJECT
public:
    TApplication(int &argc, char **argv, int = QT_VERSION);

protected:
    bool notify(QObject *, QEvent *);
signals:

public slots:

};

#endif // TAPPLICATION_H

//==========================================================================================
// End of file.
//==========================================================================================

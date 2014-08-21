/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: tapplication.h

* 功能描述: 程序接口基类

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
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

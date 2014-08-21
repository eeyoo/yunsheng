#ifndef TCLOCK_H
#define TCLOCK_H

#include <QWidget>

class TClock : public QWidget
{
    Q_OBJECT
public:
    explicit TClock(QWidget *parent = 0);

signals:

public slots:
    void UpdateTim();
protected:
    void paintEvent(QPaintEvent *event);
private:
    QPointF RotatePT(QPointF pt, int angle);
};

#endif // TCLOCK_H

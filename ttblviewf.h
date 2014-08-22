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

#ifndef DLG_GENERRELAYOUTPUT_H
#define DLG_GENERRELAYOUTPUT_H

#include <QDialog>
#include <QSignalMapper>

namespace Ui {
class Dlg_GenerRelayOutput;
}

class Dlg_GenerRelayOutput : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_GenerRelayOutput(QWidget *parent = 0);
    ~Dlg_GenerRelayOutput();

private:
    QSignalMapper  sglMapL;
public:
    int iO;

private:
    Ui::Dlg_GenerRelayOutput *ui;

private slots:
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
    void on_btn_clicked(int ibtn);
};

#endif // DLG_GENERRELAYOUTPUT_H

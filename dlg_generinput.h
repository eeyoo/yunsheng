#ifndef DLG_GENERINPUT_H
#define DLG_GENERINPUT_H

#include <QDialog>
#include <QSignalMapper>

namespace Ui {
class Dlg_GenerInput;
}

class Dlg_GenerInput : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_GenerInput(QWidget *parent = 0);
    ~Dlg_GenerInput();

private:
    QSignalMapper  sglMapL;
public:
    int iI;

private:
    Ui::Dlg_GenerInput *ui;
private slots:
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
    void on_btn_clicked(int ibtn);
};

#endif // DLG_GENERINPUT_H

#ifndef DLG_GENERCRYSOUTPUT_H
#define DLG_GENERCRYSOUTPUT_H

#include <QDialog>
#include <QSignalMapper>

namespace Ui {
class Dlg_GenerCrysOutput;
}

class Dlg_GenerCrysOutput : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_GenerCrysOutput(QWidget *parent = 0);
    ~Dlg_GenerCrysOutput();

private:
    Ui::Dlg_GenerCrysOutput *ui;

private:
    QSignalMapper  sglMapL;
public:
    int iO;

private slots:
    void on_btn_clicked(int ibtn);
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
};

#endif // DLG_GENERCRYSOUTPUT_H

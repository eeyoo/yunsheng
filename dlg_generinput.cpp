#include "dlg_generinput.h"
#include "ui_dlg_generinput.h"
#include "twidmana.h"
#include "treadcmd.h"

Dlg_GenerInput::Dlg_GenerInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_GenerInput)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    QPushButton *btn[] = {ui->I1,ui->I2,ui->I3,ui->I4,ui->I5,ui->I6,ui->I7,
                          ui->I8,ui->I9,ui->I10,ui->I11,ui->I12,ui->I13,ui->I14,
                          ui->I15,ui->I16,ui->I17,ui->I18,ui->I19,ui->I20,ui->I21,
                          ui->I22,ui->I23,ui->I24,ui->I25,ui->I26,ui->I27,ui->I28,
                          ui->I29,ui->I30,ui->I31,ui->I32,ui->I33,ui->I34};
    for(int i = 0;i<sizeof(btn)/sizeof(QPushButton*);i++)
    {
        sglMapL.setMapping(btn[i],i);
        connect(btn[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));

        if(i < readCmd.CmdI.size()){
            btn[i]->setText(readCmd.CmdI[i].cmdTil);
        }
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_btn_clicked(int)));

    widMana->bDialog = true;
}

Dlg_GenerInput::~Dlg_GenerInput()
{
    delete ui;
}
/*************************************************************************
* 函数名称: on_btn_clicked
* 功    能: 响应QPushButton点击事件
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_GenerInput::on_btn_clicked(int ibtn)
{
    iI = ibtn;
    widMana->bDialog = false;
    QDialog::accept();
}

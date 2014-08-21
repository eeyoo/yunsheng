/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: dlg_keyboard.cpp

* 功能描述: 自定义大键盘

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include "dlg_keyboard.h"
#include "ui_dlg_keyboard.h"
#include "qa5driver.h"
#include "twidmana.h"

/*************************************************************************
* 函数名称: Dlg_Keyboard
* 功   能: 构造函数
* 输入参数: QWidget *parent 父类句柄
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Keyboard::Dlg_Keyboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Keyboard)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    QPushButton *btn[] = {ui->btn48,ui->btn49,ui->btn50,ui->btn51,ui->btn52,ui->btn53,ui->btn54,
                          ui->btn55,ui->btn56,ui->btn57,ui->btn97,ui->btn98,ui->btn99,ui->btn100,
                          ui->btn101,ui->btn102,ui->btn103,ui->btn104,ui->btn105,ui->btn106,ui->btn107,
                          ui->btn108,ui->btn109,ui->btn110,ui->btn111,ui->btn112,ui->btn113,ui->btn114,
                          ui->btn115,ui->btn116,ui->btn117,ui->btn118,ui->btn119,ui->btn120,ui->btn121,
                          ui->btn122,ui->btn43,ui->btn45,ui->btn42,ui->btn47,ui->btn32,ui->btn40,
                          ui->btn59,ui->btn41,ui->btn46,ui->btn33,ui->btn63};
    for(int i = 0;i<sizeof(btn)/sizeof(QPushButton*);i++)
    {
        sglMapL.setMapping(btn[i],i);
        connect(btn[i], SIGNAL(clicked()), &sglMapL, SLOT(map()));
    }
    connect(&sglMapL,SIGNAL(mapped(int)),this,SLOT(on_btn_clicked(int)));

    setFocusPolicy(Qt::NoFocus);

    a5drv.buzzer_off();

    widMana->bDialog = true;

    ui->btnShift->setText(ui->btnShift->isChecked() ? QString("ABC") : QString("abc"));
}
/*************************************************************************
* 函数名称: Dlg_Keyboard
* 功   能: 析构函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
Dlg_Keyboard::~Dlg_Keyboard()
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
void Dlg_Keyboard::on_btn_clicked(int ibtn)
{
    QPushButton *btn[] = {ui->btn48,ui->btn49,ui->btn50,ui->btn51,ui->btn52,ui->btn53,ui->btn54,
                          ui->btn55,ui->btn56,ui->btn57,ui->btn97,ui->btn98,ui->btn99,ui->btn100,
                          ui->btn101,ui->btn102,ui->btn103,ui->btn104,ui->btn105,ui->btn106,ui->btn107,
                          ui->btn108,ui->btn109,ui->btn110,ui->btn111,ui->btn112,ui->btn113,ui->btn114,
                          ui->btn115,ui->btn116,ui->btn117,ui->btn118,ui->btn119,ui->btn120,ui->btn121,
                          ui->btn122,ui->btn43,ui->btn45,ui->btn42,ui->btn47,ui->btn32,ui->btn40,
                          ui->btn59,ui->btn41,ui->btn46,ui->btn33,ui->btn63};

    QString strBtn = btn[ibtn]->objectName();
    strBtn = strBtn.right(strBtn.length()-3);

    quint8 asc = (quint8)strBtn.toInt();
    if(ui->btnShift->isChecked())
    {
        if(asc >= 'a'&&asc <= 'z')
            asc -= 32;
    }

    m_str = ui->le_input->text();
    m_str += asc;

    ui->le_input->setText(m_str);
}
/*************************************************************************
* 函数名称: on_btnBack_clicked
* 功   能: 点击退格键
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Keyboard::on_btnBack_clicked()
{
    m_str = ui->le_input->text();
    m_str = m_str.left(m_str.length()-1);
    ui->le_input->setText(m_str);
}
/*************************************************************************
* 函数名称: on_btnQuit_clicked
* 功   能: 点击退出
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Keyboard::on_btnQuit_clicked()
{
    widMana->bDialog = false;
    QDialog::reject();
}
/*************************************************************************
* 函数名称: on_btnEnter_clicked
* 功   能: 点击确定按钮
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Keyboard::on_btnEnter_clicked()
{
    widMana->bDialog = false;
    QDialog::accept();
}
/*************************************************************************
* 函数名称: on_btnShift_clicked
* 功   能: 切换大小写
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
void Dlg_Keyboard::on_btnShift_clicked()
{
    QPushButton *btn[] = {ui->btn97,ui->btn98,ui->btn99,ui->btn100,
                          ui->btn101,ui->btn102,ui->btn103,ui->btn104,ui->btn105,ui->btn106,ui->btn107,
                          ui->btn108,ui->btn109,ui->btn110,ui->btn111,ui->btn112,ui->btn113,ui->btn114,
                          ui->btn115,ui->btn116,ui->btn117,ui->btn118,ui->btn119,ui->btn120,ui->btn121,
                          ui->btn122};

    for(int i = 0;i<sizeof(btn)/sizeof(QPushButton*);i++)
    {
        QString strT(ui->btnShift->isChecked()?('A'+(char)i):('a'+(char)i));
        btn[i]->setText(strT);
    }

    ui->btnShift->setText(ui->btnShift->isChecked() ? QString("ABC") : QString("abc"));
}

//==========================================================================================
// End of file.
//==========================================================================================

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setGeometry(50,40,1200,750);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    this->hide();
    login mylogin;
    mylogin.exec();
    this->show();
}

void Widget::on_pushButton_2_clicked()
{
    this->hide();
    reg myreg;
    myreg.exec();
    this->show();
}

void Widget::on_pushButton_3_clicked()
{
    exit(0);
}

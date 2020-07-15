#include "view2.h"
#include "ui_view2.h"

view2::view2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view2)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.exec("select id, name from dept_info where id != '000000'");

    while(query.next()){
        ui->comboBox->addItem(query.value(1).toString());
        //建立index和科室编号的对应关系
        f << query.value(0).toString();
    }
    on_comboBox_currentIndexChanged(0);
}

view2::~view2()
{
    delete ui;
}

void view2::on_pushButton_5_clicked()
{
    accept();
}

void view2::on_comboBox_currentIndexChanged(int index)
{
    //弹出对应科室简介
    QSqlQuery query;
    query.prepare("select location, introduction from dept_info where id = ?");
    QString info = f.value(index);
    query.bindValue(0, info);
    query.exec();
    info.clear();
    if(query.next()){
        info += "位置:";
        info += query.value(0).toString();
        info += "\n介绍:";
        info += query.value(1).toString();
    }
    ui->textBrowser->setText(info);
    return ;
}

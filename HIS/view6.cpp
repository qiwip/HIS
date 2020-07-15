#include "view6.h"
#include "ui_view6.h"

view6::view6(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view6)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,300);
    ui->tableWidget->setColumnWidth(2,300);
}

view6::~view6()
{
    delete ui;
}

void view6::setpatient(QString user)
{
    patient = user;
    QSqlQuery query;
    query.prepare("select name from  patient_info where id = ?");
    query.bindValue(0, patient);
    query.exec();
    while (query.next()) {
        ui->label_4->setText(query.value(0).toString());
        ui->label_5->setText(patient);
    }
    query.prepare("select date, diagnose, content from prescription where patient_id = ?");
    query.bindValue(0, patient);
    query.exec();
    int i = 0;
    while (query.next()) {
        ui->tableWidget->insertRow(i);
        QString temp = query.value(0).toString().mid(0, 10);
        (temp += " ") += query.value(0).toString().mid(11, 10);

        QTableWidgetItem *item0 = new QTableWidgetItem(temp, Qt::AlignHCenter | Qt::AlignVCenter);
        QTableWidgetItem *item1 = new QTableWidgetItem(query.value(1).toString(), Qt::AlignHCenter | Qt::AlignVCenter);
        QTableWidgetItem *item2 = new QTableWidgetItem(query.value(2).toString(), Qt::AlignHCenter | Qt::AlignVCenter);

        ui->tableWidget->setItem(i, 0, item0);
        ui->tableWidget->setItem(i, 1, item1);
        ui->tableWidget->setItem(i, 2, item2);
        i++;
    }
}

void view6::on_pushButton_clicked()
{
    reject();
}

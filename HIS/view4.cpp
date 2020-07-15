#include "view4.h"
#include "ui_view4.h"

view4::view4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view4)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,300);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,100);
}

view4::~view4()
{
    delete ui;
}

void view4::setpatient(QString user)
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
    query.prepare("select date, item, price, number, total from  outlay where patient_id = ?");
    query.bindValue(0, patient);
    query.exec();
    int i = 0;
    int all = 0;
    while (query.next()) {
        all += query.value(4).toInt();
        ui->tableWidget->insertRow(i);
        QTableWidgetItem *item0 = new QTableWidgetItem();
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();
        QTableWidgetItem *item4 = new QTableWidgetItem();
        QString temp = query.value(0).toString().mid(0, 10);

        (temp += " ") += query.value(0).toString().mid(11, 10);
        item0->setText(temp);
        item1->setText(query.value(1).toString());
        item2->setText(query.value(2).toString());
        item3->setText(query.value(3).toString());
        item4->setText(query.value(4).toString());
        item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item4->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableWidget->setItem(i, 0, item0);
        ui->tableWidget->setItem(i, 1, item1);
        ui->tableWidget->setItem(i, 2, item2);
        ui->tableWidget->setItem(i, 3, item3);
        ui->tableWidget->setItem(i, 4, item4);
        i++;
    }
    ui->tableWidget->insertRow(i);
    QTableWidgetItem *item0 = new QTableWidgetItem();
    QTableWidgetItem *item1 = new QTableWidgetItem();
    item0->setText("总计");
    item1->setText(QString::number(all, 10));
    item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(i, 1, item0);
    ui->tableWidget->setItem(i, 4, item1);
}

void view4::on_pushButton_clicked()
{
    reject();
}

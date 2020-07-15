#include "view7.h"
#include "ui_view7.h"

view7::view7(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view7)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,300);
    ui->tableWidget->setColumnWidth(1,300);
    ui->tableWidget->setColumnWidth(2,200);
}

view7::~view7()
{
    delete ui;
}

void view7::setpatient(QString user)
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
    query.prepare("select ward_no, bed_no, date, price from  ward_list where patient_id = ? and free = 0");
    query.bindValue(0, patient);
    query.exec();
    if(!query.next()) {
        ui->tableWidget->setVisible(false);
        ui->label_6->setText("暂无住院记录");
        flag = 0;
        return ;
    }
    flag = 1;
    QString stime = query.value(2).toString().mid(0, 10);
    (stime += " ") += query.value(2).toString().mid(11, 10);
    QDateTime time = QDateTime::fromString(stime, "yyyy-MM-dd hh:mm:ss");
    int time_s = time.toSecsSinceEpoch();//入院时间
    QDateTime time_now = QDateTime::currentDateTime();
    int time_s_now = time_now.toSecsSinceEpoch();//当前时间
    days = (time_s_now - time_s)/60;
    price = query.value(3).toInt();
    QString no;
    for(int i = 0; i < days ; i++){
        time_s_now = time_s + i * 60;
        time_now = QDateTime::fromSecsSinceEpoch(time_s_now);
        stime = time_now.toString("yyyy-MM-dd hh:mm");
        no = "病房号:";
        no += query.value(0).toString();
        no += "    病床号:";
        no += query.value(1).toString();

        ui->tableWidget->insertRow(i);
        QTableWidgetItem *item0 = new QTableWidgetItem();
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();

        item0->setText(stime);
        item1->setText(no);
        item2->setText(query.value(3).toString());
        item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableWidget->setItem(i, 0, item0);
        ui->tableWidget->setItem(i, 1, item1);
        ui->tableWidget->setItem(i, 2, item2);
    }
}

void view7::on_pushButton_clicked()
{
    reject();
}

void view7::on_pushButton_2_clicked()
{
    if(!flag)
        return ;
    QSqlQuery query;
    query.prepare("update ward_list set free = 1 where patient_id = ? and free = 0");
    query.bindValue(0, patient);
    query.exec();
    query.prepare("insert into outlay(patient_id, item, price, number, total, date) values(?, ?, ?, ?, ?, ?)");
    query.bindValue(0, patient);
    query.bindValue(1, "住院费");
    query.bindValue(2, price);
    query.bindValue(3, days);
    query.bindValue(4, price*days);
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    query.bindValue(5, date);
    query.exec();
    accept();
}

#include "doc_manage.h"
#include "ui_doc_manage.h"

doc_manage::doc_manage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::doc_manage)
{
    ui->setupUi(this);
    ui->toolBox->setCurrentIndex(0);
    ui->tableWidget->setColumnWidth(0, 265);
    ui->tableWidget->setColumnWidth(1, 265);
    ui->tableWidget->setColumnWidth(2, 200);
    ui->tableWidget_2->setColumnWidth(0, 260);
    ui->tableWidget_2->setColumnWidth(1, 240);
    ui->tableWidget_3->setColumnWidth(0, 260);
    ui->tableWidget_3->setColumnWidth(1, 240);
}

doc_manage::~doc_manage()
{
    delete ui;
}

void doc_manage::on_pushButton_5_clicked()
{
    reject();
}

void doc_manage::on_pushButton_clicked()
{//每日明细
    int row_count = ui->tableWidget->rowCount(); //获取表单行数
    for(int i = 0; i < row_count; i++){//清空表单
        ui->tableWidget->removeRow(0);
    }
    QSqlQuery query;
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    query.prepare("select date, item, total from  outlay where date between ? and ?");
    QString date1 = date + " 00:00:00";
    query.bindValue(0, date1);
    date1 = date + " 23:59:59";
    qDebug() << date1;
    query.bindValue(1, date1);
    qDebug() << date1;
    query.exec();
    int i = 0;
    int in = 0;
    while (query.next()) {
        in += query.value(2).toInt();
        ui->tableWidget->insertRow(i);
        QTableWidgetItem *item0 = new QTableWidgetItem();
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();

        QString temp = query.value(0).toString().mid(0, 10);
        (temp += " ") += query.value(0).toString().mid(11, 10);
        item0->setText(temp);
        item1->setText(query.value(1).toString());
        item2->setText(query.value(2).toString());
        item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableWidget->setItem(i, 0, item0);
        ui->tableWidget->setItem(i, 1, item1);
        ui->tableWidget->setItem(i, 2, item2);
        i++;
    }
    ui->tableWidget->insertRow(i);
    QTableWidgetItem *item0 = new QTableWidgetItem();
    QTableWidgetItem *item1 = new QTableWidgetItem();
    item0->setText("总额");
    item1->setText(QString::number(in, 10));
    item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(i, 1, item0);
    ui->tableWidget->setItem(i, 2, item1);
    ui->stackedWidget->setCurrentIndex(0);

    //ui->tableWidget
}

void doc_manage::on_pushButton_3_clicked()
{//月视图
    int row_count = ui->tableWidget_2->rowCount(); //获取表单行数
    for(int i = 0; i < row_count; i++){//清空表单
        ui->tableWidget_2->removeRow(0);
    }
    int v1=0, v2=0, v3=0, v4=0;
    QSqlQuery query;
    QString date = QDateTime::currentDateTime().toString("yyyy-MM");
    query.prepare("create view layout_m as select date, item, total from  outlay where date between ? and ?");//为单月的账单建立视图
    QString date1 = date + "-01 00:00:00";
    query.bindValue(0, date1);
    date1 = date + "-31 23:59:59";
    query.bindValue(1, date1);
    query.exec();

    query.prepare("SELECT total FROM layout_m WHERE item = '挂号费'");
    query.exec();
    while(query.next()){
        v1 += query.value(0).toInt();
    }

    query.prepare("SELECT total FROM layout_m WHERE item = '住院费'");
    query.exec();
    while(query.next()){
        v2 += query.value(0).toInt();
    }

    query.prepare("select total FROM layout_m WHERE item  in(  \
                   select name from medicine_list)");
    query.exec();
    while(query.next()){
        v3 += query.value(0).toInt();
    }

    query.prepare("select total FROM layout_m WHERE item  in(  \
                   select name from test_list)");
    query.exec();
    while(query.next()){
        v4 += query.value(0).toInt();
    }
    ui->tableWidget_2->insertRow(0);
    QTableWidgetItem *item0 = new QTableWidgetItem("挂号", Qt::AlignHCenter | Qt::AlignVCenter);
    QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(v1, 10), Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget_2->setItem(0, 0, item0);
    ui->tableWidget_2->setItem(0, 1, item1);

    ui->tableWidget_2->insertRow(1);
    QTableWidgetItem *item2 = new QTableWidgetItem("住院", Qt::AlignHCenter | Qt::AlignVCenter);
    QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(v2, 10), Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget_2->setItem(1, 0, item2);
    ui->tableWidget_2->setItem(1, 1, item3);

    ui->tableWidget_2->insertRow(2);
    QTableWidgetItem *item4 = new QTableWidgetItem("药品", Qt::AlignHCenter | Qt::AlignVCenter);
    QTableWidgetItem *item5 = new QTableWidgetItem(QString::number(v3, 10), Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget_2->setItem(2, 0, item4);
    ui->tableWidget_2->setItem(2, 1, item5);

    ui->tableWidget_2->insertRow(3);
    QTableWidgetItem *item6 = new QTableWidgetItem("检查", Qt::AlignHCenter | Qt::AlignVCenter);
    QTableWidgetItem *item7 = new QTableWidgetItem(QString::number(v4, 10), Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget_2->setItem(3, 0, item6);
    ui->tableWidget_2->setItem(3, 1, item7);

    ui->label_5->setValue(v1, v2, v3, v4);

    query.exec("DROP VIEW layout_m");
    ui->stackedWidget->setCurrentIndex(1);

    //ui->tableWidget_2

}

void doc_manage::on_pushButton_4_clicked()
{//年视图
    int row_count = ui->tableWidget_3->rowCount(); //获取表单行数
    for(int i = 0; i < row_count; i++){//清空表单
        ui->tableWidget_3->removeRow(0);
    }
    int v1=0, v2=0, v3=0, v4=0;
    QSqlQuery query;
    QString date = QDateTime::currentDateTime().toString("yyyy");
    query.prepare("create view layout_y as select date, item, total from  outlay where date between ? and ?");//为当年的账单建立视图
    QString date1 = date + "-01-01 00:00:00";
    query.bindValue(0, date1);
    date1 = date + "-12-31 23:59:59";
    query.bindValue(1, date1);
    query.exec();

    query.prepare("SELECT total FROM layout_y WHERE item = '挂号费'");
    query.exec();
    while(query.next()){
        v1 += query.value(0).toInt();
    }

    query.prepare("SELECT total FROM layout_y WHERE item = '住院费'");
    query.exec();
    while(query.next()){
        v2 += query.value(0).toInt();
    }

    query.prepare("select total FROM layout_y WHERE item  in(  \
                   select name from medicine_list)");
    query.exec();
    while(query.next()){
        v3 += query.value(0).toInt();
    }

    query.prepare("select total FROM layout_y WHERE item  in(  \
                   select name from test_list)");
    query.exec();
    while(query.next()){
        v4 += query.value(0).toInt();
    }
    ui->tableWidget_3->insertRow(0);
    QTableWidgetItem *item0 = new QTableWidgetItem("挂号", Qt::AlignHCenter | Qt::AlignVCenter);
    QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(v1, 10), Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget_3->setItem(0, 0, item0);
    ui->tableWidget_3->setItem(0, 1, item1);

    ui->tableWidget_3->insertRow(1);
    QTableWidgetItem *item2 = new QTableWidgetItem("住院", Qt::AlignHCenter | Qt::AlignVCenter);
    QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(v2, 10), Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget_3->setItem(1, 0, item2);
    ui->tableWidget_3->setItem(1, 1, item3);

    ui->tableWidget_3->insertRow(2);
    QTableWidgetItem *item4 = new QTableWidgetItem("药品", Qt::AlignHCenter | Qt::AlignVCenter);
    QTableWidgetItem *item5 = new QTableWidgetItem(QString::number(v3, 10), Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget_3->setItem(2, 0, item4);
    ui->tableWidget_3->setItem(2, 1, item5);

    ui->tableWidget_3->insertRow(3);
    QTableWidgetItem *item6 = new QTableWidgetItem("检查", Qt::AlignHCenter | Qt::AlignVCenter);
    QTableWidgetItem *item7 = new QTableWidgetItem(QString::number(v4, 10), Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget_3->setItem(3, 0, item6);
    ui->tableWidget_3->setItem(3, 1, item7);


    ui->label_6->setValue(v1, v2, v3, v4);

    query.exec("DROP VIEW layout_y");
    ui->stackedWidget->setCurrentIndex(2);
    //ui->tableWidget_3

}

void doc_manage::on_toolBox_currentChanged(int index)
{
    if(index==1)
        ui->pushButton->click();
}

void doc_manage::on_lineEdit_4_textEdited(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("select name from doctor_info where id = ?");
    query.bindValue(0, arg1);
    query.exec();
    if(query.next()){
        ui->lineEdit->setText(query.value(0).toString());
    }
}

void doc_manage::on_pushButton_2_clicked()
{
    QSqlQuery query;
    query.prepare("select * from doctor_info where id = ?");
    query.bindValue(0, ui->lineEdit_4->text());
    query.exec();
    if(!query.next()){
        ui->lineEdit->setText("没有该医生");
        return ;
    }
    query.prepare("select id from dept_info where name = ?");
    query.bindValue(0, ui->lineEdit_2->text());
    query.exec();
    if(!query.next()){
        ui->lineEdit_2->setText("没有该科室");
        return ;
    }
    QString dept = query.value(0).toString();
    query.prepare("update doctor_info set name = ?, dept = ?, title = ?, level = ? where id = ?");
    query.bindValue(0, ui->lineEdit->text());
    query.bindValue(1, dept);
    query.bindValue(2, ui->lineEdit_3->text());
    if(ui->radioButton->isChecked())
        query.bindValue(3, 2);
    else
        query.bindValue(3, 1);
    query.bindValue(4, ui->lineEdit_4->text());
    query.exec();
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->radioButton->setChecked(false);
}

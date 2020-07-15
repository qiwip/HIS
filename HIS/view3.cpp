#include "view3.h"
#include "ui_view3.h"

view3::view3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view3)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0,40);

    QSqlQuery query;
    query.exec("select id, name from dept_info where id != '000000' and name != '检验科'");

    while(query.next()){
//        if(query.value(1).toString()!="检验科"){
            ui->comboBox->addItem(query.value(1).toString());
            //建立index和科室编号的对应关系
            dept << query.value(0).toString();
        //}
    }
    on_comboBox_currentIndexChanged(0);
}

view3::~view3()
{
    delete ui;
}

void view3::on_radioButton_toggled(bool checked)
{//普通号
    QSqlQuery query;
    doctor.clear();
    if(!checked)
        return ;
    int row_count = ui->tableWidget->rowCount(); //获取表单行数
    for(int i = 0; i < row_count; i++){//清空表单
        ui->tableWidget->removeRow(0);
    }
    query.prepare("select name, title, id from doctor_info where dept = ? and level = 1");
    query.bindValue(0, dept_id);
    query.exec();
    int i = 0;
    while(query.next()){
        ui->tableWidget->insertRow(i);
        QTableWidgetItem *item0 = new QTableWidgetItem();
        QTableWidgetItem *item1 = new QTableWidgetItem();

        item0->setText(query.value(0).toString());
        item1->setText(query.value(1).toString());
        item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item1->setTextAlignment(Qt::AlignJustify | Qt::AlignVCenter);
        ui->tableWidget->setItem(i, 1, item0);
        ui->tableWidget->setItem(i, 2, item1);
        QRadioButton *button = new QRadioButton;
        ui->tableWidget->setCellWidget(i,0,button);
        i++;
        doctor << query.value(2).toString();
    }
    ui->label_4->setText("挂号费:10元");
    flag = 10;
}

void view3::on_radioButton_2_toggled(bool checked)
{
    QSqlQuery query;
    doctor.clear();
    if(!checked)
        return ;
    int row_count = ui->tableWidget->rowCount(); //获取表单行数
    for(int i = 0; i < row_count; i++){//清空表单
        ui->tableWidget->removeRow(0);
    }
    query.prepare("select name, title, id from doctor_info where dept = ? and level = 2");
    query.bindValue(0, dept_id);
    query.exec();
    int i = 0;
    while(query.next()){
        ui->tableWidget->insertRow(i);
        QTableWidgetItem *item0 = new QTableWidgetItem();
        QTableWidgetItem *item1 = new QTableWidgetItem();

        item0->setText(query.value(0).toString());
        item1->setText(query.value(1).toString());
        item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item1->setTextAlignment(Qt::AlignJustify | Qt::AlignVCenter);
        ui->tableWidget->setItem(i, 1, item0);
        ui->tableWidget->setItem(i, 2, item1);
        QRadioButton *button = new QRadioButton;
        ui->tableWidget->setCellWidget(i,0,button);
        i++;
        doctor << query.value(2).toString();
    }
    ui->label_4->setText("挂号费:20元");
    flag = 20;
}

void view3::on_pushButton_clicked()
{
    reject();
}

void view3::on_pushButton_2_clicked()
{//挂号
    int i;
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    for(i = 0; i< ui->tableWidget->rowCount(); i++){
        QWidget * widget=ui->tableWidget->cellWidget(i,0);//获得widget
        QRadioButton *button=(QRadioButton*)widget;//强制转化为QComboBox
        if(button->isChecked())
            break;

    }
    if(i == ui->tableWidget->rowCount()){
        ui->label_5->setText("请选择医生");
        return ;
    }
    doctor_id = doctor.at(i);
    //挂号表中插入新的挂号记录
    QSqlQuery query;
    query.prepare("insert into registration(patient_id, dept, doctor, flag, date) values(?, ?, ?, 1, ?)");
    query.bindValue(0, patient_id);
    query.bindValue(1, dept_id);
    query.bindValue(2, doctor_id);
    query.bindValue(3, date);
    query.exec();
    query.prepare("insert into outlay(patient_id, item, price, number, total, date) values(?, ?, ?, 1, ?, ?)");
    query.bindValue(0, patient_id);
    query.bindValue(1, "挂号费");
    query.bindValue(2, flag);
    query.bindValue(3, flag);
    query.bindValue(4, date);
    query.exec();
    QMessageBox::information(this, QString("提示"), QString("挂号成功"),QMessageBox::Ok);
    accept();
}

void view3::setpatient(QString user)
{
    patient_id = user;
}

void view3::on_comboBox_currentIndexChanged(int index)
{
    dept_id = dept.value(index);
}

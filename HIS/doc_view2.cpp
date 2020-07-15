#include "doc_view2.h"
#include "ui_doc_view2.h"

doc_view2::doc_view2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::doc_view2)
{
    ui->setupUi(this);
    next_patient();
}

doc_view2::~doc_view2()
{
    delete ui;
}


void doc_view2::setId(QString id)
{
    doctor_id = id;
}

void doc_view2::next_patient(){

    QSqlQuery query;
    //清空记录
    ui->label->clear();
    ui->label_4->clear();
    ui->label_5->clear();
    ui->label_9->clear();
    ui->plainTextEdit->clear();
    reg_no = -1;
    test_no = -1;
    query.exec("select no, patient_id from  registration where flag = 2");
    if(query.next()){
        reg_no = query.value(0).toInt();
        QString patient_id = query.value(1).toString();
        query.prepare("select name, sex, id_card_no from  patient_info where id = ?");
        query.bindValue(0, patient_id);
        query.exec();
        if(query.next()){//基本信息
            ui->label->setText(query.value(0).toString());
            ui->label_5->setText(query.value(1).toString());
            int data = query.value(2).toString().mid(6, 4).toInt();
            ui->label_4->setText(QString::number(2017-data, 10));
        }
        query.prepare("select no, item from  test_record where done = 0 and patient_id = ?");
        query.bindValue(0, patient_id);
        query.exec();
        if(query.next()){
            test_no = query.value(0).toInt();
            ui->label_9->setText(query.value(1).toString());
        }
    }
}


void doc_view2::on_pushButton_clicked()
{
    accept();
}

void doc_view2::on_pushButton_2_clicked()
{
    if(reg_no == -1)
        return ;
    if(ui->plainTextEdit->toPlainText().isEmpty())
        return ;
    QSqlQuery query;
    //更新检查单
    query.prepare("update test_record set result = ? , done = 1 where no = ?");
    query.bindValue(0, ui->plainTextEdit->toPlainText());
    query.bindValue(1, test_no);
    query.exec();
    //更新挂号单
    query.prepare("update registration set flag = 3 where no = ?");
    query.bindValue(0, reg_no);
    query.exec();
    next_patient();
    return ;
}

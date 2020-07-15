#include "view5.h"
#include "ui_view5.h"

view5::view5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view5)
{
    ui->setupUi(this);

}

view5::~view5()
{
    delete ui;
}


void view5::setpatient(QString user)
{
    QSqlQuery query;
    patient = user;
    query.prepare("select * from  patient_info where id = ?");
    query.bindValue(0, patient);
    query.exec();
    if(query.next()){
        ui->label_6->setText(query.value(0).toString());
        ui->label_7->setText(query.value(1).toString());
        ui->label_8->setText(query.value(3).toString());
        ui->lineEdit->setText(query.value(4).toString());
    }
}

void view5::on_pushButton_clicked()
{
    reject();
}

void view5::on_pushButton_2_clicked()
{
    QSqlQuery query;
    if(ui->lineEdit->text().isEmpty()){
        ui->label_9->setText("请输入手机号");
        return ;
    }
    if(ui->lineEdit_2->text().isEmpty()){
        ui->label_10->setText("请输入密码");
        return ;
    }

    query.prepare("update patient_info set phone = ?, password = ? where id = ?");

    query.bindValue(0, ui->lineEdit->text());
    query.bindValue(1, ui->lineEdit_2->text());
    query.bindValue(2, patient);
    query.exec();
    if(query.isValid())
        //此处插入成功检测,成功直接以当前ID进入用户界面
        QMessageBox::information(this, QString("提示"), QString("修改成功"),QMessageBox::Ok);
    accept();
}

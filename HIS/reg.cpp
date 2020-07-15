#include "reg.h"
#include "ui_reg.h"

reg::reg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reg)
{
    ui->setupUi(this);
}

reg::~reg()
{
    delete ui;
}

void reg::on_pushButton_clicked()
{
    reject();
}

void reg::on_pushButton_2_clicked()
{
    QSqlQuery query;
    if(ui->lineEdit->text().isEmpty()){
        ui->label_6->setText("请输入就诊卡号");
        return ;
    }
    if(ui->lineEdit_2->text().isEmpty()){
        ui->label_7->setText("请输入姓名");
        return ;
    }
    if(!(ui->radioButton->isChecked() || ui->radioButton_2->isChecked())){
        ui->label_12->setText("请选择性别");
        return ;
    }
    if(ui->lineEdit_3->text().isEmpty()){
        ui->label_8->setText("请输入身份证号");
        return ;
    }
    if(ui->lineEdit_4->text().isEmpty()){
        ui->label_9->setText("请输入手机号");
        return ;
    }
    if(ui->lineEdit_5->text().isEmpty()){
        ui->label_10->setText("请输入密码");
        return ;
    }
    query.prepare("select * from  where id = ?");
    query.bindValue(0, ui->lineEdit->text());
    query.exec();
    if(query.next()){
        ui->label_6->setText("(就诊卡已被注册)");
        return ;
    }
    query.prepare("insert into patient_info(id, name, sex, id_card_no, phone, password) values(?, ?, ?, ?, ?, ?)");
    query.bindValue(0, ui->lineEdit->text());
    query.bindValue(1, ui->lineEdit_2->text());
    if(ui->radioButton->isChecked()){
        query.bindValue(2, "男");
    }
    else
        query.bindValue(2, "女");
    query.bindValue(3, ui->lineEdit_3->text());
    query.bindValue(4, ui->lineEdit_4->text());
    query.bindValue(5, ui->lineEdit_5->text());
    if(!query.exec()){
        QMessageBox::information(this, QString("提示"), QString("就诊卡已被注册！"),QMessageBox::Ok);
        return ;
    }
    //此处插入成功检测,成功直接以当前ID进入用户界面

    view1 mywin;
    mywin.setuser(ui->lineEdit->text());
    this->hide();
    mywin.exec();
    accept();
}

void reg::on_lineEdit_textEdited(const QString &arg1)
{
    ui->label_6->setText("");
    Q_UNUSED(arg1);
}

void reg::on_lineEdit_2_textEdited(const QString &arg1)
{
    ui->label_7->setText("");
    Q_UNUSED(arg1);
}

void reg::on_lineEdit_3_textEdited(const QString &arg1)
{
    ui->label_8->setText("");
    Q_UNUSED(arg1);
}

void reg::on_lineEdit_4_textEdited(const QString &arg1)
{
    ui->label_9->setText("");
    Q_UNUSED(arg1);
}

void reg::on_lineEdit_5_textEdited(const QString &arg1)
{
    ui->label_10->setText("");
    Q_UNUSED(arg1);
}

void reg::on_radioButton_toggled(bool checked)
{
    if(checked)
        ui->label_12->setText("");
}

void reg::on_radioButton_2_toggled(bool checked)
{
    if(checked)
        ui->label_12->setText("");
}

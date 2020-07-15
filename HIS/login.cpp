#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    reject();
}

void login::on_pushButton_3_clicked()
{
    //事务处理界面
    QSqlQuery query;
    if(ui->checkBox->isChecked()){
        query.prepare("select * from  doctor_info where account = ? and  password = ?");
        query.bindValue(0, ui->lineEdit->text());
        query.bindValue(1, ui->lineEdit_2->text());
        query.exec();
        if(query.next()){
            //界面
            this->hide();
            if(query.value(5).toInt()==0){//检验科
                doc_view2 myview;
                myview.setId(query.value(0).toString());
                myview.exec();
            }
            else if(query.value(5).toInt() <= 2){//医生
                doc_view1 myview;
                myview.setId(query.value(0).toString());
                myview.exec();
            }
            else {//管理员
                doc_manage myview;
                myview .exec();
            }
            this->show();
            accept();
        }
        else{
            //
            ui->label_3->setText("账号或密码错误！");
        }
    }
    else{
        query.prepare("select * from  patient_info where id = ? and  password = ?");
        query.bindValue(0, ui->lineEdit->text());
        query.bindValue(1, ui->lineEdit_2->text());
        query.exec();
        if(query.next()){
            //界面
            view1 mywin;
            mywin.setuser(ui->lineEdit->text());
            this->hide();
            mywin.exec();
            accept();
        }
        else{
            //
            ui->label_3->setText("账号或密码错误！");
        }
    }

}

void login::on_lineEdit_textEdited(const QString &arg1)
{
    ui->label_3->setText("");
    ui->label_4->setText("");
    Q_UNUSED(arg1);
}


void login::on_lineEdit_2_textEdited(const QString &arg1)
{
    ui->label_3->setText("");
    ui->label_4->setText("");
    Q_UNUSED(arg1);
}

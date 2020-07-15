#include "doc_view1.h"
#include "ui_doc_view1.h"

doc_view1::doc_view1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::doc_view1)
{
    ui->setupUi(this);

    ui->textBrowser->setVisible(false);
    ui->textBrowser_2->setVisible(false);
    ui->label_8->setVisible(false);
    QSqlQuery query;
    query.exec("select name from test_list");
    ui->comboBox_2->addItem("");
    while (query.next()){
        ui->comboBox_2->addItem(query.value(0).toString());
    }

}

doc_view1::~doc_view1()
{
    delete ui;
}

void doc_view1::clear()
{
    QSqlQuery query;
    //更新排队列表
    ui->comboBox->clear();
    query.prepare("select * from  registration where dept = ? and doctor = ?");
    query.bindValue(0, doctor_dept);
    query.bindValue(1, doctor_id);
    query.exec();
    while(query.next()){
        if(query.value(4).toInt()==1 || query.value(4).toInt()==3)
            ui->comboBox->addItem(query.value(0).toString());//挂号单号
    }
    //清空界面
    ui->label->setText("");
    ui->label_4->setText("");
    ui->label_5->setText("");
    ui->label_8->setVisible(false);
    ui->plainTextEdit->clear();
    ui->textBrowser->setText("");
    ui->textBrowser->setVisible(false);
    ui->textBrowser_2->setText("");
    ui->lineEdit->setText("");
    ui->comboBox_2->setCurrentIndex(0);
    ui->spinBox->clear();
    ui->checkBox->setChecked(false);
    ui->label_11->setText("");
}

void doc_view1::setId(QString id)
{
    doctor_id = id;
    QSqlQuery query;
    query.prepare("select * from  doctor_info where id = ?");
    query.bindValue(0, doctor_id);
    query.exec();
    if(query.next()){
        doctor_name = query.value(1).toString();//医生名
        doctor_dept = query.value(3).toString();//科室编号

    }
    query.prepare("select * from  registration where dept = ? and doctor = ?");
    query.bindValue(0, doctor_dept);
    query.bindValue(1, doctor_id);
    query.exec();
    while(query.next()){
        if(query.value(4).toInt()==1 || query.value(4).toInt()==3)
            ui->comboBox->addItem(query.value(0).toString());//挂号单号
    }
}

void doc_view1::on_pushButton_5_clicked()
{
    reject();
}

void doc_view1::on_checkBox_toggled(bool checked)
{
    if(checked){
        //弹出病房管理
        QSqlQuery query;
        query.prepare("select * from  ward_list where dept_id = ? and free = 1");
        query.bindValue(0, doctor_dept);
        query.exec();
        if(query.next()){
            QString room = query.value(0).toString();//病房号
            int bed = query.value(1).toInt();//病床号

            query.prepare("update ward_list set free = 0, patient_id = ?, date = ? where ward_no = ? and bed_no = ?");
            query.bindValue(0, patient_id);
            QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            query.bindValue(1, date);
            query.bindValue(2, room);
            query.bindValue(3, bed);
            query.exec();
            room += "   病床号:";
            room += QString::number(bed, 10);
            QString temp = "病房号:";
            temp += room;
            ui->label_11->setText(temp);
            return ;
        }
        ui->label_11->setText("病房已满");
    }
    else
        ui->label_11->setText("");
}

void doc_view1::on_lineEdit_textChanged(const QString &arg1)
{
    QString arg = arg1;
    QStringList wordList;
    //构造补全器
    QSqlQuery query;
    query.prepare("select * from  medicine_list where name like ?");
    arg += '%';//任意长度字符串匹配
    query.bindValue(0, arg);
    query.exec();
    while (query.next()) {
        wordList << query.value(1).toString();
    }

    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(completer);

}

void doc_view1::on_pushButton_clicked()
{
    //叫号
    QSqlQuery query;
    if(ui->comboBox->currentText().isEmpty())
        return ;
    query.prepare("select * from  patient_info  \
                  where id in(  \
                  select patient_id from registration   \
                  where no = ? \
                  )");
    query.bindValue(0, ui->comboBox->currentText().toInt());//挂号单号
    query.exec();
    while (query.next()) {
        patient_id = query.value(0).toString();
        ui->label->setText(query.value(1).toString());
        ui->label_5->setText(query.value(2).toString());
        int data = query.value(3).toString().mid(6, 4).toInt();
        ui->label_4->setText(QString::number(2017-data, 10));
    }
    //复诊
    query.prepare("select * from  registration where patient_id = ? and flag = 3");
    query.bindValue(0, patient_id);
    query.exec();
    if(query.next()){
        query.prepare("select result, diagnose from test_record where patient_id = ? and doctor_id = ?");
        query.bindValue(0, patient_id);
        query.bindValue(1, doctor_id);
        query.exec();
        if(query.next()){
            ui->plainTextEdit->setPlainText(query.value(1).toString());//诊断
            ui->textBrowser->setVisible(true);
            ui->label_8->setVisible(true);
            ui->textBrowser->setText(query.value(0).toString());//检查结果
        }
    }
}

void doc_view1::on_pushButton_2_clicked()
{//开药
    if(ui->spinBox->value()==0 || ui->lineEdit->text().isEmpty())
        return ;
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QSqlQuery query;
    ui->textBrowser_2->setVisible(true);
    query.prepare("select * from medicine_list where name = ?");
    query.bindValue(0, ui->lineEdit->text());
    query.exec();
    if(!query.next()){
        ui->textBrowser_2->setText("没有该药品");
        return ;
    }
    chufang += ui->lineEdit->text();//药名
    chufang += '*';
    if(query.value(3).toInt() < ui->spinBox->value()){
        ui->textBrowser_2->setText("药品数量不足");
        return ;
    }
    chufang += QString::number(ui->spinBox->value(), 10);//数量
    chufang += '\n';
    ui->textBrowser_2->setText(chufang);
    float price = query.value(2).toFloat();
    float total = price*ui->spinBox->value();
    //增加病人费用记录
    query.prepare("insert into outlay(patient_id, item, price, number, total, date) values(?, ?, ?, ?, ?, ?)");
    query.bindValue(0, patient_id);
    query.bindValue(1, ui->lineEdit->text());
    query.bindValue(2, price);
    query.bindValue(3, ui->spinBox->value());
    query.bindValue(4, total);
    query.bindValue(5, date);
    query.exec();
    //药品库存--，算了先不做
    ui->spinBox->setValue(0);
}

void doc_view1::on_pushButton_3_clicked()
{
    if(ui->comboBox_2->currentText().isEmpty())
        return ;
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //生成病人检查项，加入检查记录
    QSqlQuery query;
    query.prepare("insert into test_record(done, doctor_id, patient_id, item, diagnose) values(0, ?, ?, ?, ?)");
    query.bindValue(0, doctor_id);
    query.bindValue(1, patient_id);
    query.bindValue(2, ui->comboBox_2->currentText());
    query.bindValue(3, ui->plainTextEdit->toPlainText());
    query.exec();
    //加入账单
    query.prepare("select price from test_list where name = ?");
    query.bindValue(0, ui->comboBox_2->currentText());
    query.exec();
    float price;
    if(!query.next()){
        return ;
    }
    price = query.value(0).toFloat();
    query.prepare("insert into outlay(patient_id, item, price, number, total, date) values(?, ?, ?, 1, ?, ?)");
    query.bindValue(0, patient_id);
    query.bindValue(1, ui->comboBox_2->currentText());
    query.bindValue(2, price);
    query.bindValue(3, price);
    query.bindValue(4, date);
    query.exec();
    //挂号记录flag置为2
    query.prepare("update registration set flag = 2 where patient_id = ?");
    query.bindValue(0, patient_id);
    query.exec();
    clear();
}

void doc_view1::on_pushButton_6_clicked()
{
    if(ui->label->text().isEmpty())
        return ;
    QSqlQuery query;
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //治疗结束，写回病人处方信息
    query.prepare("insert into prescription(patient_id, doctor_id, diagnose, content, date) values(?, ?, ?, ?, ?)");
    query.bindValue(0, patient_id);
    query.bindValue(1, doctor_id);
    if(ui->plainTextEdit->toPlainText().isEmpty())
        query.bindValue(2, "");
    else
        query.bindValue(2, ui->plainTextEdit->toPlainText());
    if(chufang.isEmpty())
        chufang = "";
    query.bindValue(3, chufang);
    query.bindValue(4, date);
    query.exec();
    //挂号记录flag置为0
    query.prepare("update registration set flag = 0 where patient_id = ?");
    query.bindValue(0, patient_id);
    query.exec();
    clear();
}


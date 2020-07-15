#ifndef DOC_VIEW1_H
#define DOC_VIEW1_H

#include <QDialog>
#include <QSqlQuery>
#include <QStringList>
#include <QCompleter>
#include <QDateTime>
#include <QDebug>

namespace Ui {
class doc_view1;
}

class doc_view1 : public QDialog
{
    Q_OBJECT

public:
    explicit doc_view1(QWidget *parent = 0);
    ~doc_view1();
    void setId(QString id);

private slots:

    void on_checkBox_toggled(bool checked);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::doc_view1 *ui;

    int flag;
    QString doctor_id;
    QString doctor_name;//医生名
    QString doctor_dept;//科室
    QString patient_id;
    QString diagnosed;//诊断内容
    QString chufang;//当前病人的处方
    void clear();
};

#endif // DOC_VIEW1_H

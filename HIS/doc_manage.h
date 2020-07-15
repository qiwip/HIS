#ifndef DOC_MANAGE_H
#define DOC_MANAGE_H

#include <QDialog>
#include <QPainter>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>

namespace Ui {
class doc_manage;
}

class doc_manage : public QDialog
{
    Q_OBJECT

public:
    explicit doc_manage(QWidget *parent = 0);
    ~doc_manage();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_toolBox_currentChanged(int index);

    void on_lineEdit_4_textEdited(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::doc_manage *ui;
};

#endif // DOC_MANAGE_H

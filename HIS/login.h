#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include "view1.h"
#include "doc_view1.h"
#include "doc_view2.h"
#include "doc_manage.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

private:
    Ui::login *ui;
};

#endif // LOGIN_H

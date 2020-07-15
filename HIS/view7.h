#ifndef VIEW7_H
#define VIEW7_H

#include <QDialog>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
namespace Ui {
class view7;
}

class view7 : public QDialog
{
    Q_OBJECT

public:
    explicit view7(QWidget *parent = 0);
    ~view7();
    void setpatient(QString user);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::view7 *ui;
    QString patient;
    int flag;
    int days;
    int price;
};

#endif // VIEW7_H

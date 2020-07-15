#ifndef VIEW5_H
#define VIEW5_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
namespace Ui {
class view5;
}

class view5 : public QDialog
{
    Q_OBJECT

public:
    explicit view5(QWidget *parent = 0);
    ~view5();
    void setpatient(QString user);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::view5 *ui;
    QString patient;
};

#endif // VIEW5_H

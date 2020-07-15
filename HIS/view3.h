#ifndef VIEW3_H
#define VIEW3_H

#include <QDialog>
#include <QDebug>
#include <windows.h>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>

namespace Ui {
class view3;
}

class view3 : public QDialog
{
    Q_OBJECT

public:
    explicit view3(QWidget *parent = 0);
    ~view3();
    void setpatient(QString user);
private slots:

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::view3 *ui;
    QList <QString> dept;
    QList <QString> doctor;
    QString dept_id;
    QString doctor_id;
    QString patient_id;
    int flag;
};

#endif // VIEW3_H

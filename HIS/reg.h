#ifndef REG_H
#define REG_H

#include <QDialog>
#include <QSqlQuery>
#include <windows.h>
#include "view1.h"
#include <QMessageBox>
namespace Ui {
class reg;
}

class reg : public QDialog
{
    Q_OBJECT

public:
    explicit reg(QWidget *parent = 0);
    ~reg();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_lineEdit_4_textEdited(const QString &arg1);

    void on_lineEdit_5_textEdited(const QString &arg1);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

private:
    Ui::reg *ui;
};

#endif // REG_H

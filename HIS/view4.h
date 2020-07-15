#ifndef VIEW4_H
#define VIEW4_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class view4;
}

class view4 : public QDialog
{
    Q_OBJECT

public:
    explicit view4(QWidget *parent = 0);
    ~view4();
    void setpatient(QString user);

private slots:
    void on_pushButton_clicked();

private:
    Ui::view4 *ui;
    QString patient;
};

#endif // VIEW4_H

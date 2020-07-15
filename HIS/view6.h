#ifndef VIEW6_H
#define VIEW6_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class view6;
}

class view6 : public QDialog
{
    Q_OBJECT

public:
    explicit view6(QWidget *parent = 0);
    ~view6();
    void setpatient(QString user);

private slots:
    void on_pushButton_clicked();

private:
    Ui::view6 *ui;
    QString patient;
};

#endif // VIEW6_H

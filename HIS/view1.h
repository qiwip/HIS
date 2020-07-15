#ifndef VIEW1_H
#define VIEW1_H

#include <QDialog>
#include "view2.h"
#include "view3.h"
#include "view4.h"
#include "view5.h"
#include "view6.h"
#include "view7.h"


namespace Ui {
class view1;
}

class view1 : public QDialog
{
    Q_OBJECT

public:
    explicit view1(QWidget *parent = 0);
    ~view1();
    void setuser(QString);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::view1 *ui;
    QString user_id;
};

#endif // VIEW1_H

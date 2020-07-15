#ifndef DOC_VIEW2_H
#define DOC_VIEW2_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class doc_view2;
}

class doc_view2 : public QDialog
{
    Q_OBJECT

public:
    explicit doc_view2(QWidget *parent = 0);
    ~doc_view2();
    void setId(QString id);
    void next_patient();
private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::doc_view2 *ui;
    QString doctor_id;
    int reg_no;
    int test_no;
};

#endif // DOC_VIEW2_H

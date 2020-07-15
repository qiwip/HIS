#ifndef VIEW2_H
#define VIEW2_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QList>
namespace Ui {
class view2;
}

class view2 : public QDialog
{
    Q_OBJECT

public:
    explicit view2(QWidget *parent = 0);
    ~view2();

private slots:

    void on_pushButton_5_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::view2 *ui;
    QList <QString> f;
};

#endif // VIEW2_H

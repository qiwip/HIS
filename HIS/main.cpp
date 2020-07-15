#include "widget.h"
#include <QApplication>
#include <QTextCodec>
#include <QtSql>
#include <QMessageBox>

#define user "root"
#define pass "111001"
#define database "hospital"


int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");// 为程序设置字符集
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setPort(3306);

    db.setUserName(user);
    db.setPassword(pass);
    db.setDatabaseName(database);

re: if(!db.open())
    {
        Widget w;
        w.show();
        QMessageBox::StandardButton error;
        error = QMessageBox::critical(NULL, "错误提示", "打开数据库失败！", QMessageBox::Retry | QMessageBox::Close);
      if (error == QMessageBox::Close)
          exit(0);
      else if (error == QMessageBox::Retry)
          goto re;
      else
        exit(0);
    }
    Widget w;
    w.show();
    return a.exec();
}

#include "view1.h"
#include "ui_view1.h"

view1::view1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view1)
{
    ui->setupUi(this);
}

view1::~view1()
{
    delete ui;
}


void view1::setuser(QString user)
{
    user_id = user;
}

void view1::on_pushButton_clicked()
{
    //弹出就医流程图示，可考虑增加科室选择
    view2 myview;
    myview.exec();
    return ;
}

void view1::on_pushButton_2_clicked()
{
    //弹出挂号缴费界面，挂号界面直接选择科室、医生、专家or平诊，支付，缴费界面：显示应缴费多少，计算为：药费(查询全部处方)+住院费(查询所在病房价格*(当前日期-入院日期))
    view3 myviwe;
    myviwe.setpatient(user_id);
    myviwe.exec();
    return ;
}


void view1::on_pushButton_3_clicked()
{
    //查询查询缴费单等
    view4 myviwe;
    myviwe.setpatient(user_id);
    myviwe.exec();
    return ;
}


void view1::on_pushButton_4_clicked()
{
    //修改资料，界面同注册界面，先从注册信息库查询信息放入label中，再读取修改后的更新值
    view5 myviwe;
    myviwe.setpatient(user_id);
    myviwe.exec();
    return ;
}

void view1::on_pushButton_5_clicked()
{//=退出登录，返回welcome界面
    reject();
}

void view1::on_pushButton_6_clicked()
{//弹出诊疗记录界面
    view6 myviwe;
    myviwe.setpatient(user_id);
    myviwe.exec();
    return ;
}

void view1::on_pushButton_7_clicked()
{
    view7 myview;
    myview.setpatient(user_id);
    myview.exec();
}

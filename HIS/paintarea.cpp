#include "paintarea.h"

PaintArea::PaintArea(QWidget *parent) : QLabel(parent)
{

}

void PaintArea::setValue(int v1, int v2, int v3, int v4){
    int total = v1 + v2 + v3 + v4;
    angel1 = 360*v1/total;
    angel2 = 360*v2/total;
    angel3 = 360*v3/total;
    angel4 = 360*v4/total;
}

void PaintArea::paintEvent(QPaintEvent * event){
	Q_UNUSED(event);
	QPainter painter1(this);
    painter1.fillRect(190,30,10,10,Qt::green);
    painter1.drawText(200,40,"挂号");
    painter1.fillRect(190,50,10,10,Qt::blue);
    painter1.drawText(200,60,"住院");
    painter1.fillRect(190,70,10,10,Qt::yellow);
    painter1.drawText(200,80,"药品");
    painter1.fillRect(190,90,10,10,Qt::red);
    painter1.drawText(200,100,"检查");
	painter1.setPen(Qt::NoPen);
    painter1.setBrush(Qt::green);
    painter1.drawPie(40,100,200,200,0,angel1*16);
	painter1.setBrush(Qt::blue);
    painter1.drawPie(40,100,200,200,angel1*16,angel2*16);
	painter1.setBrush(Qt::yellow);
    painter1.drawPie(40,100,200,200,angel1*16+angel2*16,angel3*16);
    painter1.setBrush(Qt::red);
    painter1.drawPie(40,100,200,200,angel1*16+angel2*16+angel3*16, angel4*16);
    return ;
}

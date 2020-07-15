#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QLabel>
#include <QPainter>

class PaintArea : public QLabel
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = 0);
    ~PaintArea(){return ;}
    void paintEvent(QPaintEvent *event);
    void setValue(int v1, int v2, int v3, int v4);
private:
    int angel1;
    int angel2;
    int angel3;
    int angel4;
};

#endif // PAINTAREA_H

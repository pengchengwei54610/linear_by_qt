#include "myarrowitem.h"
#include <QGraphicsScene>
#include <QPainter>

/*
 * 构造函数 :
 * length   : 长度
 * dir      : 箭头方向   0：上     1：右      2：下        3：左
 * size     : 有无箭头   0：无箭头   1：有箭头
 */
MyArrowItem::MyArrowItem ( int length, int dir, int size) : direction(dir), arrowSize(size)
{
    QPoint startP(0,0), endP, p1, p2;//p1，p2为箭头末端两端点

    switch (dir) {
    case 0:
        p1=p2=endP=QPoint(0,-length);
        if(size)
            p1+=QPoint(-SIZE1_HEIGHT,SIZE1_WEIGHT),p2+=QPoint(SIZE1_HEIGHT,SIZE1_WEIGHT);
        mboundingRect=QRect(-SIZE1_HEIGHT,-length,SIZE1_HEIGHT<<1,length);
        break;
    case 1:
        p1=p2=endP=QPoint(length,0);
        if(size)
            p1+=QPoint(-SIZE1_WEIGHT,-SIZE1_HEIGHT),p2+=QPoint(-SIZE1_WEIGHT,SIZE1_HEIGHT);
        mboundingRect=QRect(0,-SIZE1_HEIGHT,length,SIZE1_HEIGHT<<1);
        break;
    case 2:
        p1=p2=endP=QPoint(0,length);
        if(size)
            p1+=QPoint(-SIZE1_HEIGHT,-SIZE1_WEIGHT),p2+=QPoint(SIZE1_HEIGHT,-SIZE1_WEIGHT);
        mboundingRect=QRect(-SIZE1_HEIGHT,0,SIZE1_HEIGHT<<1,length);
        break;
    case 3:
        p1=p2=endP=QPoint(-length,0);
        if(size)
            p1+=QPoint(SIZE1_WEIGHT,SIZE1_HEIGHT),p2+=QPoint(SIZE1_WEIGHT,-SIZE1_HEIGHT);
        mboundingRect=QRect(-length,-SIZE1_HEIGHT,length,SIZE1_HEIGHT<<1);
        break;
    default:
        break;
    }

    line1=QLine(startP,endP);
    line2=QLine(endP,p1);
    line3=QLine(endP,p2);
}

MyArrowItem::~MyArrowItem()
{
}

//执行绘制动作
void MyArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawLine(line1);
    painter->drawLine(line2);
    painter->drawLine(line3);
}

QRectF MyArrowItem::boundingRect() const
{
    return mboundingRect;
}

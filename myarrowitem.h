#ifndef MYARROWITEM_H
#define MYARROWITEM_H

#include <QGraphicsItem>

//自定义箭头，用于Graphics画图架构
class MyArrowItem : public QGraphicsItem
{
    QRectF mboundingRect;
    QLine line1,line2,line3;//line1为线段主体，line2，line3为箭头部分
    int direction;
    int arrowSize;

public:
    explicit MyArrowItem (int length, int dir=1, int size=1) ;
    ~MyArrowItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget=0) Q_DECL_OVERRIDE ;

    QRectF boundingRect() const Q_DECL_OVERRIDE ;

#define SIZE1_WEIGHT 6//箭头长度
#define SIZE1_HEIGHT 3//箭头宽度
};

#endif // MYARROWITEM_H

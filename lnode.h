#ifndef LNODE_H
#define LNODE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QBrush>

#include "myarrowitem.h"

class LinkList;
class CLinkList;

class LNode
{
public:
    LNode(QString dt, LNode *nt);       //构造函数
    ~LNode();                           //析构函数
    void setValueRect(QGraphicsRectItem* vRect);//值边框
    void setPointerRect(QGraphicsRectItem* pRect);//指针边框
    void setTextRect(QGraphicsTextItem* vText);//值
    void setArrowVector(std::vector<MyArrowItem*> aVector);//箭头
    void setNodeStatus(QBrush brush);//节点的颜色设置（用于演示线性表操作过程）
    void removeAll(QGraphicsScene *scene);//删除节点

protected:
    QString data;       //节点数据域
    LNode * next;       //节点指针域

    //节点图形项
    QGraphicsRectItem * valueRect, *pointerRect;
    QGraphicsTextItem * valueText, *pointerText;
    std::vector<MyArrowItem*> arrowVector;

public:
    friend class LinkList;
    friend class CLinkList;
};

#endif // LNODE_H

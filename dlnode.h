#ifndef DLNode_H
#define DLNode_H


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QBrush>

#include "myarrowitem.h"

class DLinkList;

class DLNode
{
public:
    DLNode(QString dt, DLNode *nt);         //构造函数
    ~DLNode();                              //析构函数

    void setNodeStatus(QBrush brush);//节点的颜色设置（用于演示线性表操作过程）
    void removeAll(QGraphicsScene *scene);//删除节点

protected:
    QString data;               //节点数据域
    DLNode * next, *prior;      //节点指针域（前置节点，后置节点）

    //节点图形项
    QGraphicsRectItem * valueRect, *pointerRect, *prePointerRect;
    QGraphicsTextItem * valueText, *pointerText, *prePointerText;
    std::vector<MyArrowItem*> arrowVector, preArrowVector;

public:
    friend class DLinkList;
};

#endif // DLNode_H

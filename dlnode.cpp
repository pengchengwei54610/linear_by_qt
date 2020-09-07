#include "dlnode.h"

DLNode::DLNode(QString dt, DLNode *nt)
{
    data=dt;
    next=nt;
    pointerRect=valueRect=prePointerRect=NULL;
    valueText=pointerText=prePointerText=NULL;
}

DLNode::~DLNode()
{
}

void DLNode::setNodeStatus(QBrush brush)
{
    valueRect->setBrush(brush);
}

void DLNode::removeAll(QGraphicsScene *scene)
{
    if(valueRect)
    {
        scene->removeItem(valueRect);
        delete valueRect;
        valueRect=NULL;
    }

    if(pointerRect)
    {
        scene->removeItem(pointerRect);
        delete pointerRect;
        pointerRect=NULL;
    }

    if(prePointerRect)
    {
        scene->removeItem(prePointerRect);
        delete prePointerRect;
        prePointerRect=NULL;
    }

    if(valueText)
    {
        scene->removeItem(valueText);
        delete valueText;
        valueText=NULL;
    }

    if(pointerText)
    {
        scene->removeItem(pointerText);
        delete pointerText;
        pointerText=NULL;
    }

    if(prePointerText)
    {
        scene->removeItem(prePointerText);
        delete prePointerText;
        prePointerText=NULL;
    }

    for(auto &a:arrowVector)
        scene->removeItem(a);
    arrowVector.clear();

    for(auto &a:preArrowVector)
        scene->removeItem(a);
    preArrowVector.clear();
}

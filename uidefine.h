#ifndef UIDEFINE_H
#define UIDEFINE_H

#define nomalbrushcolour Qt::GlobalColor::lightGray
#define visitedbrushcolour Qt::GlobalColor::yellow
#define markbrushcolour Qt::GlobalColor::cyan
#define defaultwrongcolour Qt::GlobalColor::red
#define defaultsuccesscolour Qt::GlobalColor::green

#define backgroundpic_path ":/ico/resource/background.png"

#define MAX_SLEEP_TIME 150     //演示延时ms

#define SCENE_MAX_W 750         //视图场景最大宽度pix
#define SCENE_MAX_H 500         //视图场景最大高度pix

#define VALUE_RECT_W    75      //节点域矩形框宽度pix
#define POINTER_RECT_W  25      //指针域矩形宽度pix
#define RECT_H      30          //节点域指针域矩形高度pix
#define SPACING     10          //上下间隔pix

#define ARROW_LEN   (25+POINTER_RECT_W/2)                   //一般箭头长度
#define ARROW_H_OFFSET    (VALUE_RECT_W+POINTER_RECT_W/2)   //箭头距离节点图形起始坐标水平偏移
#define ARROW_V_OFFSET    (SPACING+RECT_H/2)                //箭头距离节点图形起始坐标垂直偏移

#define NODE_W (VALUE_RECT_W+POINTER_RECT_W+25)             //每个节点占用宽度
#define NODE_H (RECT_H+SPACING+SPACING)                     //每个节点占用高度

//双向链表节点不同
#define DVALUE_RECT_W 75        //数据域矩形框宽度pix
#define DPOINTER_RECT_W 25      //指针域矩形宽度pix
#define DRECT_H 30              //节点域指针域矩形高度pix
#define DSPACING 15             //上下间隔pix

#define INTERVAL 24             //节点间距
#define DARROW_LEN (DPOINTER_RECT_W/2+INTERVAL)                             //一般箭头长度
#define DARROW_H_OFFSET1 (DPOINTER_RECT_W+DVALUE_RECT_W+DPOINTER_RECT_W/2)  //后继箭头距离节点图形起始坐标水平偏移
#define DARROW_H_OFFSET2 (DPOINTER_RECT_W/2)                                //前驱箭头距离节点图形起始坐标水平偏移
#define DARROW_V_OFFSET1 (DSPACING+DRECT_H/3)                               //后继箭头距离节点图形起始坐标垂直偏移
#define DARROW_V_OFFSET2 (DSPACING+DRECT_H/3*2)                             //前驱箭头距离节点图形起始坐标垂直偏移

#define DNODE_W (DVALUE_RECT_W+DPOINTER_RECT_W*2+INTERVAL)      //每个节点占用宽度
#define DNODE_H (DRECT_H+DSPACING+DSPACING)                     //每个节点占用高度

#define DLEFT_SPACING 10        //距离场景左边界间隔
#define DRIGHT_SPAXING 30       //距离场景右边界间隔
#endif // UIDEFINE_H

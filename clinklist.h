#ifndef CLINKLIST_H
#define CLINKLIST_H

#include <QWidget>
#include <QFile>
#include <QTextBrowser>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QIntValidator>

#include "uidefine.h"
#include "lnode.h"

namespace Ui {
class CLinkList;
}

class CLinkList : public QWidget
{
    Q_OBJECT

public:
    explicit CLinkList(QWidget *parent = 0);			//构造函数
    ~CLinkList();                                       //析构函数

private slots:
    void on_pushButtonInit_clicked();					//点击创建

    void on_pushButtonClear_clicked();                  //点击清空

    void on_pushButtonInsert_clicked();					//点击插入

    void on_pushButtonRandomInsert3_clicked();			//点击随机插入3个节点到链表末尾

    void on_pushButtonDelete_clicked();					//点击删除

    void on_pushButtonLocate_clicked();					//点击查找出现的最靠近头节点的节点

protected:
    Ui::CLinkList *ui;               //UI指针
    QGraphicsScene *scene;          //视图场景指针
    QGraphicsTextItem *headLabel;   //链表符号指针
    MyArrowItem *headArrow;         //符号箭头指针
    LNode *head;                    //头结点指针
    int countNode;                  //节点个数计数（不包括头结点）
    int sleepTime;                  //演示延时时间（ms）

    void initTextBrowser();			//初始设置文本显示区
    void initUI();					//初始UI控件
    void initSceneView();			//初始化视图框架
    void adjustController();		//操作之后调整右侧输入和显示控件

    QPoint getLNodePos(int nodeNumber);						//计算节点的Scene坐标
    void addLNodeGraphicsItem(LNode *pl, QPoint coord);		//添加节点的GraphicsItem
    void adjustLNodeArrow(LNode *pLNode, int nodeNumber);	//调整节点的箭头
    void adjustLNodePos(LNode *pLNode, QPoint coord);		//调整节点Scene坐标
    void setCLinkListNormalBrush();							//设置链表所有节点显示模式

    void initCLinkList();						//创建链表初始化
    void insertLNode(int pos, QString elem);	//插入节点到链表
    void deleteLNode(int pos, QString &elem);	//删除链表节点
    bool locateLNode(int &pos,QString elem);	//查找链表节点
    void destroySelf();							//释放申请的内存空间

private:
    //静态常数据，类似于宏
    const static QBrush normalBursh, visitedBrush, markBrush;
    const static QFont headLabelFont, dataFont;
    const static QIntValidator dataValidator;
};

#endif // CLINKLIST_H

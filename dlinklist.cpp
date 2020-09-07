#include<QDebug>
#include <math.h>
#include "dlinklist.h"
#include "ui_dlinklist.h"
#include "myarrowitem.h"

void sleep(unsigned int msec);

const QBrush DLinkList::normalBrush=QBrush(nomalbrushcolour);
const QBrush DLinkList::visitedBrush=QBrush(visitedbrushcolour);
const QBrush DLinkList::markBrush=QBrush(markbrushcolour);

const QFont DLinkList::headLabelFont=QFont("Consolas");
const QFont DLinkList::dataFont=QFont("Consolas",8);

const QIntValidator DLinkList::dataValidator(-999999999,999999999);

//构造函数
DLinkList::DLinkList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DLinkList)
{
    //初始化数据
    ui->setupUi(this);
    initUI();

    countNode=0;
    head=NULL;
    headLabel=NULL;
    headArrow=NULL;
    scene=NULL;
    sleepTime=MAX_SLEEP_TIME>>1;
    srand(time(NULL));

    this->setWindowTitle("双向循环链表");
}

//析构函数
DLinkList::~DLinkList()
{
    destroySelf();
    delete ui;
}

//初始UI控件
void DLinkList::initUI()
{
    //设置背景图片
    QPixmap background(backgroundpic_path);
    QPalette palette;
    palette.setBrush(QPalette::Background,background);
    this->setPalette(palette);

    //未创建时，除创建按钮外，其余按键一律无效
    ui->pushButtonClear->setEnabled(false);
    ui->pushButtonInsert->setEnabled(false);
    ui->pushButtonRandomInsert3->setEnabled(false);
    ui->comboBoxInsert->setEnabled(false);
    ui->lineEditInsert->setEnabled(false);

    ui->pushButtonDelete->setEnabled(false);
    ui->comboBoxDelete->setEnabled(false);
    ui->lineEditDelete->setEnabled(false);

    ui->pushButtonLocate->setEnabled(false);
    ui->comboBoxLocate->setEnabled(false);
    ui->lineEditLocate->setEnabled(false);

    ui->lineEditState->setEnabled(false);

    ui->lineEditInsert->setFont(dataFont);
    ui->lineEditDelete->setFont(dataFont);
    ui->lineEditLocate->setFont(dataFont);
    ui->lineEditState->setFont(dataFont);
    ui->lineEditInsert->setPlaceholderText("插入值：Int");
    ui->lineEditLocate->setPlaceholderText("查找值：Int");
    ui->lineEditInsert->setValidator(&DLinkList::dataValidator);
    ui->lineEditLocate->setValidator(&DLinkList::dataValidator);
    ui->lineEditState->setText("请选择操作");

}

//初始化视图框架
void DLinkList::initSceneView()
{
    //为 view 配置相应 scene
    scene=new QGraphicsScene;
    scene->setSceneRect(0,0,SCENE_MAX_W,SCENE_MAX_H);
    ui->graphicsView->setScene(scene);

    //添加链表符号及指针箭头
    headLabel=scene->addText("DL",headLabelFont);
    headLabel->setPos(DVALUE_RECT_W/2+DPOINTER_RECT_W,DSPACING-5);
sleep(sleepTime);
    headArrow=new MyArrowItem(DARROW_LEN);
    scene->addItem(headArrow);
    headArrow->setPos(DLEFT_SPACING+DARROW_H_OFFSET1,DARROW_V_OFFSET1);
}

//操作之后调整右侧输入和显示控件
void DLinkList::adjustController()
{
    //当经过插入或删除操作后，节点个数可能会改变，需考虑一些操作的合法性
    ui->pushButtonDelete->setEnabled(countNode);
    ui->comboBoxDelete->setEnabled(countNode);

    if(ui->comboBoxDelete->count()!=countNode)
    {
        QStringList qStringList;
        for(int i=1;i<=countNode;++i)
            qStringList.push_back(QString::number(i));

        ui->comboBoxInsert->clear();
        ui->comboBoxInsert->addItems(qStringList);

        ui->comboBoxDelete->clear();
        ui->comboBoxDelete->addItems(qStringList);
    }
    if(ui->comboBoxInsert->count()!=countNode+1)
        ui->comboBoxInsert->addItem(QString::number(countNode+1));

    ui->lineEditDelete->setText(" ");
    ui->comboBoxLocate->clear();
}

//计算节点的Scene坐标
QPoint DLinkList::getDLNodePos(int nodeNumber)
{
    const static int rowN=(SCENE_MAX_W-DLEFT_SPACING-DRIGHT_SPAXING)/DNODE_W;
    return QPoint((nodeNumber+1)%rowN*DNODE_W+DLEFT_SPACING,(nodeNumber+1)/rowN*DNODE_H);
}

//添加节点的GraphicsItem
void DLinkList::addDLNodeGraphicsItem(DLNode *pDLNode, QPoint coord)
{
    int x=coord.x()+DPOINTER_RECT_W, y=coord.y();

    pDLNode->valueRect   =scene->addRect(x,y+DSPACING,DVALUE_RECT_W,DRECT_H,QPen(),DLinkList::markBrush);
    pDLNode->pointerRect =scene->addRect(x+DVALUE_RECT_W,y+DSPACING,DPOINTER_RECT_W,DRECT_H);
    pDLNode->valueText   =scene->addText(pDLNode->data,DLinkList::dataFont);
    pDLNode->valueText->setPos(x,y+DSPACING+5);

    pDLNode->prePointerRect=scene->addRect(coord.x(),y+DSPACING,DPOINTER_RECT_W,DRECT_H);
//    if(pDLNode->next==NULL)
//    {
//        pDLNode->pointerText=scene->addText(" ^",DLinkList::dataFont);
//        pDLNode->pointerText->setPos(x+VALUE_RECT_W, y+SPACING+5);
//    }
}

//调整节点的箭头
void DLinkList::adjustDLNodeArrow(DLNode *pDLNode, int nodeNumber)
{
    //调整后继指针箭头
    for(auto &a:pDLNode->arrowVector)
        scene->removeItem(a);

    QPoint myCoord=getDLNodePos(nodeNumber);
    QPoint nextCoord=getDLNodePos(nodeNumber+1);

    MyArrowItem *pArrow;

    //若是指向头结点
    if(pDLNode->next==head)
    {
        QPoint point1(myCoord.x()+DARROW_H_OFFSET1,myCoord.y()+DARROW_V_OFFSET1);
        QPoint point2(SCENE_MAX_W-DRIGHT_SPAXING+10, point1.y());
        QPoint point3(point2.x(), 1);
        QPoint point4(DLEFT_SPACING+DNODE_W+DPOINTER_RECT_W+(DVALUE_RECT_W>>1), point3.y());

        pArrow=new MyArrowItem(point2.x()-point1.x(),1,0);
        scene->addItem(pArrow);
        pArrow->setPos(point1);
        pDLNode->arrowVector.push_back(pArrow);

        pArrow=new MyArrowItem(point2.y()-point3.y(),0,0);
        scene->addItem(pArrow);
        pArrow->setPos(point2);
        pDLNode->arrowVector.push_back(pArrow);

        pArrow=new MyArrowItem(point3.x()-point4.x(),3,0);
        scene->addItem(pArrow);
        pArrow->setPos(point3);
        pDLNode->arrowVector.push_back(pArrow);

        pArrow=new MyArrowItem(DSPACING-point4.y(),2,1);
        scene->addItem(pArrow);
        pArrow->setPos(point4);
        pDLNode->arrowVector.push_back(pArrow);
    }
    else if(myCoord.y()==nextCoord.y())
    {
        //节点不是一行最后节点
        pArrow=new MyArrowItem(DARROW_LEN);
        scene->addItem(pArrow);
        pArrow->setPos(myCoord.x()+DARROW_H_OFFSET1,myCoord.y()+DARROW_V_OFFSET1);
        pDLNode->arrowVector.push_back(pArrow);
    }
    else
    {
        //节点是一行中最后节点
        QPoint point1(myCoord.x()+DARROW_H_OFFSET1,myCoord.y()+DARROW_V_OFFSET1);
        QPoint point2(point1.x(),myCoord.y()+DNODE_H+5);
        QPoint point3(DLEFT_SPACING+DPOINTER_RECT_W+DVALUE_RECT_W/2,point2.y());

        pArrow=new MyArrowItem(point2.y()-point1.y(),2,0);
        scene->addItem(pArrow);
        pArrow->setPos(point1);
        pDLNode->arrowVector.push_back(pArrow);

        pArrow=new MyArrowItem(point2.x()-point3.x(),3,0);
        scene->addItem(pArrow);
        pArrow->setPos(point2);
        pDLNode->arrowVector.push_back(pArrow);

        pArrow=new MyArrowItem(DSPACING-5,2);
        scene->addItem(pArrow);
        pArrow->setPos(point3);
        pDLNode->arrowVector.push_back(pArrow);
    }

    //调整前驱指针箭头
    for(auto &a:pDLNode->preArrowVector)
        scene->removeItem(a);

    QPoint preCoord=getDLNodePos(nodeNumber-1);
    QPoint lastCoord=getDLNodePos(countNode);

    if(pDLNode->prior==head)
    {
        QPoint point1(myCoord.x()+DARROW_H_OFFSET2,myCoord.y()+DARROW_V_OFFSET2);
        QPoint point2(DLEFT_SPACING-10,point1.y());
        QPoint point3(point2.x(),lastCoord.y()+DNODE_H-5);
        QPoint point4(lastCoord.x()+(DPOINTER_RECT_W+DVALUE_RECT_W/2),point3.y());

        pArrow=new MyArrowItem(point1.x()-point2.x(),3,0);
        scene->addItem(pArrow);
        pArrow->setPos(point1);
        pDLNode->preArrowVector.push_back(pArrow);

        pArrow=new MyArrowItem(point3.y()-point2.y(),2,0);
        scene->addItem(pArrow);
        pArrow->setPos(point2);
        pDLNode->preArrowVector.push_back(pArrow);

        pArrow=new MyArrowItem(point4.x()-point3.x(),1,0);
        scene->addItem(pArrow);
        pArrow->setPos(point3);
        pDLNode->preArrowVector.push_back(pArrow);

        pArrow=new MyArrowItem(DSPACING-5,0,1);
        scene->addItem(pArrow);
        pArrow->setPos(point4);
        pDLNode->preArrowVector.push_back(pArrow);
    }
    else if(myCoord.y()==preCoord.y())
    {
        //节点不是一行第一节点
        pArrow=new MyArrowItem(DARROW_LEN,3);
        scene->addItem(pArrow);
        pArrow->setPos(myCoord.x()+DARROW_H_OFFSET2,myCoord.y()+DARROW_V_OFFSET2);
        pDLNode->preArrowVector.push_back(pArrow);
    }
    else
    {
        //节点是一行中第一节点
        QPoint point1(myCoord.x()+DARROW_H_OFFSET2,myCoord.y()+DARROW_V_OFFSET2);
        QPoint point2(point1.x(),myCoord.y()-5);
        QPoint point3(preCoord.x()+(DPOINTER_RECT_W+DVALUE_RECT_W/2),point2.y());

        pArrow=new MyArrowItem(point1.y()-point2.y(),0,0);
        scene->addItem(pArrow);
        pArrow->setPos(point1);
        pDLNode->preArrowVector.push_back(pArrow);

        pArrow=new MyArrowItem(point3.x()-point2.x(),1,0);
        scene->addItem(pArrow);
        pArrow->setPos(point2);
        pDLNode->preArrowVector.push_back(pArrow);

        pArrow=new MyArrowItem(DSPACING-5,0);
        scene->addItem(pArrow);
        pArrow->setPos(point3);
        pDLNode->preArrowVector.push_back(pArrow);
    }
}

//调整节点Scene坐标
void DLinkList::adjustDLNodePos(DLNode *pDLNode, QPoint coord)
{
    int x=coord.x()+DPOINTER_RECT_W, y=coord.y();
    pDLNode->prePointerRect->setRect(coord.x(),y+DSPACING,DPOINTER_RECT_W,DRECT_H);
    pDLNode->valueRect->setRect(x,y+DSPACING,DVALUE_RECT_W,DRECT_H);
    pDLNode->pointerRect->setRect(x+DVALUE_RECT_W,y+DSPACING,DPOINTER_RECT_W,DRECT_H);
    pDLNode->valueText->setPos(x,y+DSPACING+5);
//    if(pDLNode->pointerText)
//        pDLNode->pointerText->setPos(x+VALUE_RECT_W, y+SPACING+5);
}

//设置链表所有节点显示模式
void DLinkList::setDLinkListNormalBrush()
{
    head->setNodeStatus(DLinkList::normalBrush);
    for(DLNode *pDLNode=head->next;pDLNode!=head;pDLNode=pDLNode->next)
        pDLNode->setNodeStatus(DLinkList::normalBrush);
}

//创建链表初始化
void DLinkList::initDLinkList()
{
    initSceneView();

    head=new DLNode("头结点", NULL);
    head->next=head;
    head->prior=head;
sleep(sleepTime);
    addDLNodeGraphicsItem(head, getDLNodePos(0));
    adjustDLNodeArrow(head,0);
}

//插入节点到链表
void DLinkList::insertDLNode(int pos, QString elem)
{
    DLNode *pInsertNode=NULL;
    DLNode *pDLNode=head;

    head->setNodeStatus(DLinkList::visitedBrush);
sleep(sleepTime);
    //找到前驱节点指针
    for(int i=0;i<pos-1;++i)
    {
        pDLNode=pDLNode->next;
        pDLNode->setNodeStatus(DLinkList::visitedBrush);

        sleep(sleepTime);
    }

    if(pDLNode->next==NULL){
        scene->removeItem(pDLNode->pointerText);
        pDLNode->pointerText=NULL;
    }

    //新节点插入到链表中
    pInsertNode=new DLNode(elem,pDLNode->next);
    pDLNode->next=pInsertNode;
    ++countNode;

    //添加图形Item
    addDLNodeGraphicsItem(pInsertNode,getDLNodePos(pos));

    for(--pos;pos<=countNode;++pos)
    {
        sleep(sleepTime);

        adjustDLNodePos(pDLNode,getDLNodePos(pos));   //调整节点坐标位置
        adjustDLNodeArrow(pDLNode,pos);               //调整每个节点箭头
        pDLNode=pDLNode->next;
    }
    adjustDLNodeArrow(head,0);                       //调整头节点箭头
}

//删除链表节点
void DLinkList::deleteDLNode(int pos, QString &elem)
{
    DLNode *pDeleteNode=NULL;
    DLNode *pDLNode=head;

    head->setNodeStatus(DLinkList::visitedBrush);

    //找到前驱节点指针
    for(int i=0;i<pos-1;++i)
    {
        sleep(sleepTime);

        pDLNode=pDLNode->next;
        pDLNode->setNodeStatus(DLinkList::visitedBrush);
    }
sleep(sleepTime);
    pDeleteNode=pDLNode->next;
    pDLNode->next=pDeleteNode->next;
    elem=pDeleteNode->data;

    //删除节点，移除图形Item
    pDeleteNode->removeAll(scene);
    delete pDeleteNode;
    --countNode;

    if(pDLNode->next==NULL){
        QPoint coord=getDLNodePos(pos-1);
        pDLNode->pointerText=scene->addText(" ^",DLinkList::dataFont);
        pDLNode->pointerText->setPos(coord.x()+VALUE_RECT_W, coord.y()+SPACING+5);
    }

    for(--pos;pos<=countNode;++pos)
    {
        sleep(sleepTime);

        adjustDLNodePos(pDLNode,getDLNodePos(pos));    //调整节点坐标位置
        adjustDLNodeArrow(pDLNode,pos);               //调整节点箭头
        pDLNode=pDLNode->next;
    }
    adjustDLNodeArrow(head,0);                       //调整头节点箭头
}

//查找链表节点
bool DLinkList::locateDLNode(int &pos, QString elem)
{
    DLNode *pDLNode=head;

    head->setNodeStatus(DLinkList::visitedBrush);
sleep(sleepTime);
    for(pos=1;pDLNode->next!=head&&pDLNode->next->data!=elem;++pos)
    {
        sleep(sleepTime);

        pDLNode=pDLNode->next;
        pDLNode->setNodeStatus(DLinkList::visitedBrush);
    }

    //找到相应节点
    if(pDLNode->next!=head){
        pDLNode->next->setNodeStatus(DLinkList::markBrush);
        return true;
    }
    return false;
}

//释放申请的内存空间
void DLinkList::destroySelf()
{
    if(scene==NULL)
        return ;

    DLNode *pDLNode=head->next, *qDLNode;
    for(;pDLNode!=head;pDLNode=qDLNode)
    {
        sleep(sleepTime);
        qDLNode=pDLNode->next;
        pDLNode->removeAll(scene);       //移除每个节点的图形Item
        delete pDLNode;      //释放内存
    }
sleep(sleepTime);
    ////////////
    head->removeAll(scene);     //移除头结点图形Item
    delete head;                //释放内存
    ///////////////

    scene->removeItem(headLabel);   //移除链表符号Item
    scene->removeItem(headArrow);   //移除链表符号后的箭头Item
    delete headLabel;       //释放内存
    delete headArrow;       //释放内存
    scene=NULL;

    countNode=0;
}

//点击创建
void DLinkList::on_pushButtonInit_clicked()
{
    //若已经建立，需要清除重建
    destroySelf();

    initDLinkList();

    ui->pushButtonClear->setEnabled(true);
    ui->pushButtonInsert->setEnabled(true);
    ui->pushButtonRandomInsert3->setEnabled(true);
    ui->comboBoxInsert->setEnabled(true);
    ui->lineEditInsert->setEnabled(true);
    ui->pushButtonLocate->setEnabled(true);
    ui->lineEditLocate->setEnabled(true);

    adjustController();
    ui->lineEditState->setPalette(defaultsuccesscolour);
    ui->lineEditState->setText("Create Success!");
}

//点击清空
void DLinkList::on_pushButtonClear_clicked()
{
    destroySelf();
    initUI();
}

//点击插入
void DLinkList::on_pushButtonInsert_clicked()
{
    setDLinkListNormalBrush();

    QString edit=ui->lineEditInsert->text();

    //若输入无效或未输入
    if(edit.isEmpty())
    {
        ui->lineEditState->setPalette(defaultwrongcolour);
        ui->lineEditState->setText("Please Input!");
        return ;
    }
sleep(sleepTime);
    insertDLNode(ui->comboBoxInsert->currentText().toInt(),edit);

    //调整右侧控件状态及值
    adjustController();
    ui->lineEditState->setPalette(defaultsuccesscolour);
    ui->lineEditState->setText("Insert Success!");
}

//点击随机插入五个节点到链表末尾
void DLinkList::on_pushButtonRandomInsert3_clicked()
{
    for(int i=0;i<3;++i)
    {
        setDLinkListNormalBrush();
        sleep(sleepTime);
        insertDLNode(countNode+1,QString::number(rand()%999999999));
        adjustController();
        ui->lineEditState->setPalette(defaultsuccesscolour);
        ui->lineEditState->setText("Insert Success!");
    }
}

//点击删除
void DLinkList::on_pushButtonDelete_clicked()
{

        setDLinkListNormalBrush();
        sleep(sleepTime);
        QString deleteData;
        deleteDLNode(ui->comboBoxDelete->currentText().toInt(),deleteData);

        //调整右侧控件状态及值
        adjustController();
        ui->lineEditDelete->setText(deleteData);
        ui->lineEditState->setPalette(defaultsuccesscolour);
        ui->lineEditState->setText("Delete Success!");

}

//点击查找出现的最靠近头节点的节点
void DLinkList::on_pushButtonLocate_clicked()
{
    setDLinkListNormalBrush();
sleep(sleepTime);
    QString edit=ui->lineEditLocate->text();

    //若输入无效或未输入
    if(edit.isEmpty())
    {
        adjustController();
        ui->lineEditState->setPalette(defaultwrongcolour);
        ui->lineEditState->setText("Please Input!");
        return;
    }

    //根据查找结果给出结果输出
    int pos;
    if(locateDLNode(pos,edit))
    {
        ui->comboBoxLocate->addItem(QString::number(pos));
        ui->comboBoxLocate->setCurrentText(QString::number(pos));
        ui->lineEditState->setPalette(defaultsuccesscolour);
        ui->lineEditState->setText("Search Success!");
    }
    else
    {
        adjustController();
        ui->lineEditState->setPalette(defaultwrongcolour);
        ui->lineEditState->setText("Search Fail!");
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
     connect(ui->comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this, &MainWindow::onCreate);//选择模式
    //设置标题
    this->setWindowTitle("Linear by QT");
    //设置背景图片
    QPixmap background(backgroundpic_path);
    QPalette palette;
    palette.setBrush(QPalette::Background,background);
    this->setPalette(palette);
}

void MainWindow::onCreate(int index)
{
    switch (index) {
    case 1:
        linkList.show();
        break;
    case 2:
        clinklist.show();
        break;
    case 3:
        dlinklist.show();
        break;
    default:
        break;
    }
}


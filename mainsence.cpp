#include "mainsence.h"
#include "ui_mainsence.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QSound>

MainSence::MainSence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainSence)
{
    ui->setupUi(this);
    this->setFixedSize(300,588);
    this->setWindowIcon(QPixmap(":/new/prefix1/res/Coin0001.png"));
    setWindowTitle("阿黄带你翻金币");

    connect(ui->exit,&QAction::triggered,[=](){
        this->close();
    });

    QSound * startSound = new QSound(":/new/prefix1/res/TapButtonSound.wav",this);

    MyPushButton * startBtn = new MyPushButton(":/new/prefix1/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5,this->height()*0.7);
    //statr按钮触发
    connect(startBtn,&QPushButton::clicked,[=](){
        startSound->play(); //开始音效
        startBtn->zoomdown();
        startBtn->zoomup();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });

    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
                    chooseScene->setGeometry(this->geometry());
                    this->show();
                });

}

MainSence::~MainSence()
{
    delete ui;
}

void MainSence::paintEvent(QPaintEvent *){
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/new/prefix1/res/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/new/prefix1/res/Title.png");

    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

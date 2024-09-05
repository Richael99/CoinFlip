#include "chooselevelscene.h"
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include<QPixmap>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QLabel>
#include"playscene.h"
#include<QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/new/prefix1/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

//返回按钮
   MyPushButton * closeBtn = new MyPushButton(":/new/prefix1/res/BackButton.png",":/new/prefix1/res/BackButtonSelected.png");
   closeBtn->setParent(this);
   closeBtn->move(this->width()-closeBtn->width(),this->height()-closeBtn->height());
   //返回按钮音效
   QSound *backSound = new QSound(":/new/prefix1/res/BackButtonSound.wav",this);

   //返回按钮功能实现
   connect(closeBtn,&MyPushButton::clicked,[=](){
       backSound->play();
       QTimer::singleShot(500, this,[=](){
           this->hide();
           //触发自定义信号，关闭自身，该信号写到 signals下做声明
           this->setGeometry(this->geometry());
           emit this->chooseSceneBack();
            }
       );
   });

   //选择关卡按钮音效
   QSound *chooseSound = new QSound(":/new/prefix1/res/TapButtonSound.wav",this);

   //创建选择关卡的按钮
   for( int i = 0 ; i < 20 ;i ++)
   {
       MyPushButton * menuBtn = new MyPushButton(":/new/prefix1/res/LevelIcon.png");
       menuBtn->setParent(this);
       menuBtn->move( 25 + i%4 * 70 , 130 + i/4 * 70  );

       //监听每个按钮的点击事件
       connect(menuBtn,&MyPushButton::clicked,[=](){
           chooseSound->play();
           QString str = QString("您选择的是第 %1 关 ").arg( i + 1);
           qDebug() <<str;

           //进入到游戏场景
           if(play == NULL){
               this->hide(); //将选关场景隐藏掉
               play = new PlayScene(i+1); //创建游戏场景
               play->setGeometry(this->geometry());
               play->show();//显示游戏场景

           connect(play,&PlayScene::chooseSceneBack,[=](){
               play->setGeometry(this->geometry());
               this->show();
               delete play;
               play = NULL;
           });
            }
       });

       QLabel * label = new QLabel;
       label->setParent(this);
       label->setFixedSize(menuBtn->width(),menuBtn->height());
       label->setText(QString::number(i+1));
       label->move(25 + i%4 * 70 , 130 + i/4 * 70 );

       //设置 label上的文字对齐方式 水平居中和 垂直居中
       label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
       //设置让鼠标进行穿透   51号属性
       label->setAttribute(Qt::WA_TransparentForMouseEvents);
   }

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

     //加载标题
    pix.load(":/new/prefix1/res/Title.png");
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
}

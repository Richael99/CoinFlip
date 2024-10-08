#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>


PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第 %1 关 ").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建退出 菜单项
    QAction *  quitAction = startMenu->addAction("退出");

    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSound *backSound = new QSound(":/new/prefix1/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/new/prefix1/res/BackButton.png" , ":/new/prefix1/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() , this->height() - backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        qDebug() << "翻金币场景中：点击了返回按钮";

        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });

    });


    //显示当前关卡数
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText( str1);
    label->setGeometry(30, this->height() - 50,120, 50);

    //胜利图片显示
    QLabel* winLabel = new QLabel;
      QPixmap tmpPix;
      tmpPix.load(":/new/prefix1/res/LevelCompletedDialogBg.png");
      winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
      winLabel->setPixmap(tmpPix);
      winLabel->setParent(this);
      winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());

    //创建金币的背景图片
      for(int i = 0 ; i < 4;i++)
      {
          for(int j = 0 ; j < 4; j++)
          {
             //绘制背景图片
              QLabel* label = new QLabel;
              label->setGeometry(0,0,50,50);
              label->setPixmap(QPixmap(":/new/prefix1/res/BoardNode(1).png"));
              label->setParent(this);
              label->move(57 + i*50,200+j*50);
//              //金币对象
//              MyCoin * coin = new MyCoin(":/new/prefix1/res/Coin0001.png");
//              coin->setParent(this);
//              coin->move(59 + i*50,204+j*50);
          }
      }
      //翻金币音效
      QSound *flipSound = new QSound(":/new/prefix1/res/ConFlipSound.wav",this);
      //胜利按钮音效
      QSound *winSound = new QSound(":/new/prefix1/res/LevelWinSound.wav",this);

      dataConfig config;
      for(int i = 0 ; i < 4;i++)
      {
          for(int j = 0 ; j < 4; j++)
          {
              gameArray[i][j] = config.mData[this->levelIndex][i][j];
              QString img;
              if(gameArray[i][j] == 1)
              {
                img = ":/new/prefix1/res/Coin0001.png";
              }
              else
              {
                img = ":/new/prefix1/res/Coin0008.png";
              }
              MyCoin * coin = new MyCoin(img);
              coin->setParent(this);
              coin->move(59 + i*50,204+j*50);
              coin->posX = i; //记录x坐标
              coin->posY = j; //记录y坐标
              coin->flag =gameArray[i][j]; //记录正反标志
              coinBtn[i][j] = coin;
              connect(coin,&MyCoin::clicked,[=](){
                          //禁用所有按钮点击事件
                  flipSound->play();
                              for(int i = 0 ; i < 4;i++)
                                {
                                  for(int j = 0 ; j < 4; j++)
                                  {
                                    coinBtn[i][j]->isWin = true;
                                  }
                                }
                              coin->changeFlag();
                              gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0; //数组内部记录的标志同步修改
                              QTimer::singleShot(300, this,[=](){
                                                  if(coin->posX+1 <=3)
                                                  {
                                                    coinBtn[coin->posX+1][coin->posY]->changeFlag();
                                                    gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                                                  }
                                                  if(coin->posX-1>=0)
                                                  {
                                                    coinBtn[coin->posX-1][coin->posY]->changeFlag();
                                                    gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                                                  }
                                                  if(coin->posY+1<=3)
                                                  {
                                                   coinBtn[coin->posX][coin->posY+1]->changeFlag();
                                                   gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                                                  }
                                                  if(coin->posY-1>=0)
                                                  {
                                                   coinBtn[coin->posX][coin->posY-1]->changeFlag();
                                                   gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                                                  }
                                                  for(int i = 0 ; i < 4;i++)
                                                    {
                                                      for(int j = 0 ; j < 4; j++)
                                                      {
                                                        coinBtn[i][j]->isWin = false;
                                                      }
                                                    }
                                  //判断是否胜利
                                                  isWin = true;
                                                  for(int i = 0 ; i < 4;i++)
                                                  {
                                                      for(int j = 0 ; j < 4; j++)
                                                      {
                                                          //qDebug() << coinBtn[i][j]->flag ;
                                                          if( coinBtn[i][j]->flag == false)
                                                          {
                                                              isWin = false;
                                                              break;
                                                          }
                                                      }
                                                  }
                                  //如果isWin依然是true，代表胜利了！
                                                  if(this->isWin)
                                                    {
                                                      for(int i = 0 ; i < 4;i++)
                                                        {
                                                          for(int j = 0 ; j < 4; j++)
                                                          {
                                                            coinBtn[i][j]->isWin = true;
                                                          }
                                                        }
                                                       winSound->play();
                                                       qDebug() << "胜利";
                                                        QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                                                                        animation1->setDuration(1000);
                                                                        animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                                                                        animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                                                                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                                                                        animation1->start();
                                                                    }

                                              });
                          });

          }
      }


}

void PlayScene::paintEvent(QPaintEvent *)
{
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/new/prefix1/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);

}

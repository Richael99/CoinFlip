#include "mycoin.h"
#include<QPushButton>
#include<QDebug>
#include"playscene.h"
MyCoin::MyCoin(QString butImg)
{

    QPixmap pixmap;
    bool ret = pixmap.load(butImg);
    if(!ret)
    {
        qDebug() << butImg << "加载图片失败!";
    }

    this->setFixedSize( pixmap.width(), pixmap.height() );
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    //金币对象
    //初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    //监听正面翻转的信号槽
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/new/prefix1/res/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->min > this->max) //如果大于最大值，重置最小值，并停止定时器
        {
            this->min = 1;
            this->isAnimation  = false;
            timer1->stop();
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/new/prefix1/res/Coin000%1.png").arg((this->max)-- );
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->max < this->min) //如果小于最小值，重置最大值，并停止定时器
        {
            this->max = 8;
            this->isAnimation  = false;
            timer2->stop();
        }
    });


}

void MyCoin::changeFlag()
{
    if(this->flag) //如果是正面，执行下列代码
    {
        timer1->start(30);
        this->isAnimation  = true;
        this->flag = false;
    }
    else //反面执行下列代码
    {
        timer2->start(30);
        this->isAnimation  = true;
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation|| isWin == true )
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}


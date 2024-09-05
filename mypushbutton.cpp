#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>
#include<QPushButton>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}
MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    this->normalImgPath = normalImg;
    this->pressedImgPath = pressImg;

    QPixmap pixmap;

    bool ret = pixmap.load(normalImgPath);
    if(!ret){
        qDebug()<<normalImg<<"加载图片失败";
    }

    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void MyPushButton::zoomdown(){
    QPropertyAnimation * animationa1 = new QPropertyAnimation(this,"geometry");
    animationa1->setDuration(200);

    animationa1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animationa1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    animationa1->setEasingCurve(QEasingCurve::OutBounce);
    animationa1->start();
}

void MyPushButton::zoomup(){
    QPropertyAnimation * animationa1 = new QPropertyAnimation(this,"geometry");
    animationa1->setDuration(200);

    animationa1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animationa1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    animationa1->setEasingCurve(QEasingCurve::OutBounce);
    animationa1->start();
}

//鼠标事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pressedImgPath != "") //选中路径不为空，显示选中图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(pressedImgPath);
        if(!ret)
        {
            qDebug() << pressedImgPath << "加载图片1失败!";
        }

        this->setFixedSize( pixmap.width(), pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交给父类执行按下事件
    return QPushButton::mousePressEvent(e);
}


void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath != "") //选中路径不为空，显示选中图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(normalImgPath);
        if(!ret)
        {
            qDebug() << normalImgPath << "加载图片2失败!";
        }
        this->setFixedSize( pixmap.width(), pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交给父类执行 释放事件
    return QPushButton::mouseReleaseEvent(e);
}

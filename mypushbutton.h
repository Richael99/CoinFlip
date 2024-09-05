#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include<QMouseEvent>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);
      MyPushButton(QString normalImg,QString pressImg = "");

      QString normalImgPath;
      QString pressedImgPath;

      void zoomdown();
      void zoomup();

      void mousePressEvent(QMouseEvent *e);
      void mouseReleaseEvent(QMouseEvent * e);
signals:

};

#endif // MYPUSHBUTTON_H

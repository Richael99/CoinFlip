#ifndef MAINSENCE_H
#define MAINSENCE_H

#include <QMainWindow>
#include"chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainSence; }
QT_END_NAMESPACE

class MainSence : public QMainWindow
{
    Q_OBJECT

public:
    MainSence(QWidget *parent = nullptr);
    ~MainSence();

    void paintEvent(QPaintEvent*);

    ChooseLevelScene *chooseScene = new ChooseLevelScene;

private:
    Ui::MainSence *ui;
};
#endif // MAINSENCE_H

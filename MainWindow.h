#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QStyle>
#include <QDesktopWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

#include "Card.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void swapCards(int a, int b);
    ~MainWindow();
    void startGame();

private:
    Ui::MainWindow *ui;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVector<Card*> cards;
//    Card *card;
public slots:
    void onSelection();
};
#endif // MAINWINDOW_H

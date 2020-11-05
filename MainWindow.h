#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyle>
#include <QDesktopWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QRadioButton>
#include <QtMath>

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
    void aiTurn();

private:
    Ui::MainWindow *ui;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QVector<Card*> cards;
    QVector<int> cardPos;
    QLabel *msgLabel;
    QPushButton *newGameBut;
    QRadioButton *redBut;
    QRadioButton *greenBut;
    int turn = 1;
    // 1 -- Player turn, 0 -- AI turn
    int playerColor = 0;
    // 0 -- green, 1 -- red
public slots:
    void onSelection();
    void hideMsg();
    void onAnimationEnd();
    void newGameButtonClicked();
};
#endif // MAINWINDOW_H

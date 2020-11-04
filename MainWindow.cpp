#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QRect screenGeometry = QApplication::desktop()->screenGeometry();
//    int x = (screenGeometry.width()-this->width()) / 2;
//    int y = (screenGeometry.height()-this->height()) / 2;
//    this->move(x, y);
    setWindowTitle("Transition");
    this->widget = new QWidget();
    this->gridLayout = new QGridLayout();
    widget->setLayout(gridLayout);
    this->graphicsView = new QGraphicsView();
    gridLayout->addWidget(graphicsView);
    this->scene = new QGraphicsScene();
    graphicsView->setScene(scene);
    setCentralWidget(widget);
    startGame();
}

void MainWindow::swapCards(int a, int b)
{
    QGraphicsItemAnimation *animation1 = new QGraphicsItemAnimation();
    QTimeLine *timer = new QTimeLine(1000);
    animation1->setItem(cards[a]);
    animation1->setTimeLine(timer);
    QGraphicsItemAnimation *animation2 = new QGraphicsItemAnimation();
    animation2->setItem(cards[b]);
    animation2->setTimeLine(timer);
    qreal tempX = 0;
    qreal tempY = 0;
    tempX = cards[a]->x();
    tempY = cards[a]->y();
    animation1->setPosAt(1, QPointF(cards[b]->x(), cards[b]->y()));
    animation2->setPosAt(1, QPointF(tempX, tempY));
    timer->start();
    cards[a]->setIsSelected(false);
    cards[b]->setIsSelected(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    for(int i = 1; i <= 8; i++){
        this->cards.push_back(new Card(i));
    }
    for(int i = 0, j = -4; i < 8; i++, j++){
        this->scene->addItem(cards[i]);
        cards[i]->setPos(j * 120, 0);
    }
    for(int i = 0; i < 8; i++){
        connect(cards[i], &Card::clicked, this, &MainWindow::onSelection);
    }
}

void MainWindow::onSelection()
{
    QVector<int> selectedCardNumbers;
    for(int i = 0; i < 8; i++){
        if(cards[i]->getIsSelected()){
            selectedCardNumbers.push_back(i);
        }
    }
    if(selectedCardNumbers.size() == 2){
        swapCards(selectedCardNumbers[0], selectedCardNumbers[1]);
    }
    else{
        selectedCardNumbers.clear();
    }
}

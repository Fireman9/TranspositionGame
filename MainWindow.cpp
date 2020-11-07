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
    this->msgLabel = new QLabel("");
    msgLabel->setStyleSheet("color: #ff4411; font-size: 48px; font-family: 'Signika', sans-serif;");
    msgLabel->setAlignment(Qt::AlignCenter);
    gridLayout->addWidget(msgLabel);
    msgLabel->hide();
    this->graphicsView = new QGraphicsView();
    gridLayout->addWidget(graphicsView);
    newGameBut = new QPushButton("New Game");
    connect(newGameBut, SIGNAL(released()), this, SLOT(newGameButtonClicked()));
    newGameBut->setStyleSheet("font-size: 38px; font-family: 'Signika', sans-serif;");
    this->vBoxLayout = new QVBoxLayout();
    this->hBoxLayout = new QHBoxLayout();
    this->greenBut = new QRadioButton("Green");
    this->greenBut->setChecked(true);
    greenBut->setStyleSheet("font-size: 20px; font-family: 'Signika', sans-serif; margin-left: 200px;");
    this->redBut = new QRadioButton("Red");
    redBut->setStyleSheet("font-size: 20px; font-family: 'Signika', sans-serif; margin-left: 200px;");
    vBoxLayout->addWidget(greenBut);
    vBoxLayout->addWidget(redBut);
    hBoxLayout->addWidget(newGameBut);
    hBoxLayout->addLayout(vBoxLayout);
    gridLayout->addLayout(hBoxLayout, 2, 0);
    this->scene = new QGraphicsScene();
    graphicsView->setScene(scene);
    setCentralWidget(widget);
    for(int i = 1; i <= 8; i++){
        this->cards.push_back(new Card(i));
    }
    for(int i = 0; i < 8; i++){
        this->scene->addItem(cards[i]);
    }
    for(int i = 0; i < 8; i++){
        connect(cards[i], &Card::clicked, this, &MainWindow::onSelection);
    }
    startGame();
}

void MainWindow::swapCards(int a, int b)
{
    if(cardPos[a] < cardPos[b] && cardPos[b]-cardPos[a] == 1){
        QGraphicsItemAnimation *animation1 = new QGraphicsItemAnimation();
        QTimeLine *timer = new QTimeLine(1000);
        connect(timer, SIGNAL(finished()), SLOT(onAnimationEnd()));
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
        cards[a]->setIsSelected(false);
        cards[b]->setIsSelected(false);
        std::swap(cardPos[a], cardPos[b]);
        if(!checkForWin()){
            if(this->turn == 0){
                turn = 1;
            }
            else{
                turn = 0;
            }
        }
        else{
            this->turn = -1;
        }
        timer->start();
    }
    else if(qFabs(cardPos[b]-cardPos[a]) != 1){
        QTimer timer;
        cards[a]->setIsSelected(false);
        cards[b]->setIsSelected(false);
        msgLabel->setText("Change only neighboring cards");
        msgLabel->show();
        timer.singleShot(3000, this, &MainWindow::hideMsg);
    }
    else if(cardPos[a] > cardPos[b]){
        QTimer timer;
        cards[a]->setIsSelected(false);
        cards[b]->setIsSelected(false);
        msgLabel->setText("Left card bigger than right");
        msgLabel->show();
        timer.singleShot(3000, this, &MainWindow::hideMsg);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    for(int i = 0, j = -4; i < 8; i++, j++){
        cards[i]->setPos(j * 120, 0);
    }
    this->cardPos.clear();
    for(int i = 0; i < 8; i++){
        this->cardPos.push_back(i);
    }
    if(greenBut->isChecked()){
        this->playerColor = 0;
    }
    else{
        this->playerColor = 1;
    }
    if(this->playerColor == 0){
        this->turn = 1;
    }
    else{
        this->turn = 0;
    }
    if(this->turn == 0){
        aiTurn();
    }
}

void MainWindow::aiTurn()
{
    this->turn = 1;
//    swapCards(0, 1);
}

bool MainWindow::checkForWin()
{
    bool end = false;
    if(cardPos[6] < cardPos[4] && cardPos[4] < cardPos[2] && cardPos[2]< cardPos[0]){
        if(this->playerColor == 0){
            this->msgLabel->setText("Green won, you won!");
            this->msgLabel->setStyleSheet("color: #008000; font-size: 48px; font-family: 'Signika', sans-serif;");
            this->msgLabel->show();
        }
        else{
            this->msgLabel->setText("Green won, you lost!");
            this->msgLabel->setStyleSheet("color: #008000; font-size: 48px; font-family: 'Signika', sans-serif;");
            this->msgLabel->show();
        }
        end = true;
    }
    else if(cardPos[7] < cardPos[5] && cardPos[5] < cardPos[3] && cardPos[3] < cardPos[1]){
        if(this->playerColor == 1){
            this->msgLabel->setText("Red won, you won!");
            this->msgLabel->show();
        }
        else{
            this->msgLabel->setText("Red won, you lost!");
            this->msgLabel->show();
        }
        end = true;
    }
    return end;
}

void MainWindow::onSelection()
{
    QVector<int> selectedCardNumbers;
    for(int i = 0; i < 8; i++){
        if(cards[i]->getIsSelected()){
            selectedCardNumbers.push_back(i);
        }
    }
    if(this->turn == 1){
        if(selectedCardNumbers.size() == 2){
            swapCards(selectedCardNumbers[0], selectedCardNumbers[1]);
        }
        else{
            selectedCardNumbers.clear();
        }
    }
    else if(this->turn == -1){
        cards[selectedCardNumbers[0]]->setIsSelected(false);
        selectedCardNumbers.clear();
        return;
    }
    else{
        cards[selectedCardNumbers[0]]->setIsSelected(false);
        selectedCardNumbers.clear();
        QTimer timer;
        msgLabel->setText("It isn't your turn");
        msgLabel->show();
        timer.singleShot(3000, this, &MainWindow::hideMsg);
    }
}

void MainWindow::hideMsg()
{
    this->msgLabel->hide();
}

void MainWindow::onAnimationEnd()
{
    if(this->turn == 0){
        aiTurn();
    }
}

void MainWindow::newGameButtonClicked()
{
    this->msgLabel->hide();
    this->msgLabel->setStyleSheet("color: #ff4411; font-size: 48px; font-family: 'Signika', sans-serif;");
    startGame();
}

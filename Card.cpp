#include "Card.h"

Card::Card(int number)
{
    this->number = number;
    this->isSelected = false;
}

bool Card::getIsSelected()
{
    return this->isSelected;
}

void Card::setIsSelected(bool isSelected)
{
    this->isSelected = isSelected;
    this->update();
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(this->isSelected == false){
        this->isSelected = true;
        this->update();
        emit clicked();
    }
    else{
        this->isSelected = false;
        this->update();
    }
}

QRectF Card::boundingRect() const
{
    return QRectF(-50, -75, 100, 150);
}

void Card::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if(this->isSelected){
        painter->setPen(QPen(QColor("#808080"), 5));
    }
    else{
        painter->setPen(QPen(QColor("#808080"), 2));
    }
    painter->setBrush(QBrush("#D3D3D3"));
    painter->drawRect(-45, -70, 90, 140);
    QString text = "";
    text = QString::number(this->number);

    QFont font("Times", 36);
    font.setWeight(70);
    QFontMetrics fm(font);
    int textWidth = fm.width(text);
    int textHeight = fm.height();
    painter->setFont(font);

    if(this->number % 2 == 0){
        painter->setPen("#ff0000");
    }
    else{
        painter->setPen("#008000");
    }
    painter->drawText(-textWidth/2, textHeight/3, text);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

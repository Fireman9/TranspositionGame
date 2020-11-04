#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Card:public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Card(int number);
    bool getIsSelected();
    void setIsSelected(bool isSelected);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    int number;
    bool isSelected;
signals:
    void clicked();
};

#endif // CARD_H

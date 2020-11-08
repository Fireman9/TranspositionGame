#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <QVector>

class DecisionTree
{
public:
    DecisionTree(QVector<int> cardPosCopy, int depth, int a, int b);
    QVector<int> cards;
    QVector<DecisionTree*> childs;
    int depth;
    int count;
    int a, b;
    bool terminal;
};

#endif // DECISIONTREE_H

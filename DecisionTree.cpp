#include "DecisionTree.h"

DecisionTree::DecisionTree(QVector<int> cardPosCopy, int depth, int a, int b)
{
    this->a = a;
    this->b = b;
    this->terminal = false;
    this->cards = cardPosCopy;
    this->depth = depth;
    if(this->depth < 3){
        for(int i = 0; i < 7; i++){
            if(cards[i] < cards[i + 1]){
                QVector<int> temp = cards;
                std::swap(temp[i], temp[i + 1]);
                childs.push_back(new DecisionTree(temp, this->depth + 1, temp[i + 1], temp[i]));
            }
        }
    }
}

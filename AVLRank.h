#ifndef AVLRANK_H
#define AVLRANK_H

#include "AVLTree.h"
#include "RankNode.h"

template<class T>
class AVLRank : public Tree<RankNode<T>, T> {
public:

    AVLRank() = default;

    AVLRank(const AVLRank& other) = delete;
    AVLRank& operator=(const AVLRank& other) = delete;

    ~AVLRank() = default;

    void add_prize(double prize, int min, int max);

    double calculate_prize(RankNode<T>* node) const;

};

template<class T>
void AVLRank<T>::add_prize(double prize, int min, int max) {
//Use this as a helper function - call first on (max, prize) then on (min-1, -prize)
//Search for the given node
//On the first of a series of right turns, add i to the parent turned right from
//On a left turn that follows at least one right turn, add -i to the parent
//When reaching the given node, if without previous right turns, add i to the given node
//-i to the given node's right child if exists
//On a left turn with no right turn directly before it: do nothing

    //Call the helper function with min-1 and -prize:
    this->m_node->add_prize(prize*(-1), min-1);
    this->m_node->add_prize(prize, max);
}

template<class T>
double AVLRank<T>::calculate_prize(RankNode<T>* node) const {
     return node->calculate_prize();
}

#endif //AVLRANK_H
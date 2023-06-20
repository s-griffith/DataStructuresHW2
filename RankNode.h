#ifndef RANKNODE_H
#define RANKNODE_H

#include "Node.h"
#include "Exception.h"
#include <iostream> //******************************************************************************************************

template <class T>
class RankNode : Node<T> {
public:

    RankNode();

    RankNode(const RankNode& other) = delete;
    RankNode& operator=(const RankNode& other) = delete;

    ~RankNode() = default;

    void add_prize(double prize, int min);

    double calculate_prize();

    void define_prize();

    /*
    * Returns the height of a node
    * @param - none
    * @return - height
    */
    int get_height() const;

    /*
     * Helper functions for testing:
     * Prints a tree, node by node
     * @param - none
     * @return - void
     */
    void inorderWalkNode(bool flag);
    void printNode();
    void printData();

private:

    /*
     * Left-Right Rotation
     * @param - Node with balance factor of +2
     * @return - pointer to ComplexNode
     */
    RankNode* ll_rotation(RankNode* node);

    /*
     * Right-Right Rotation
     * @param - Node with balance factor of -2
     * @return - pointer to ComplexNode
     */
    RankNode* rr_rotation(RankNode* node);

    /*
     * Right-Left Rotation
     * @param - Node with balance factor of -2
     * @return - pointer to ComplexNode
    */
    RankNode* rl_rotation(RankNode* node);

    /*
     * Left-Left Rotation
     * @param - Node with balance factor of +2
     * @return - pointer to ComplexNode
    */
    RankNode* lr_rotation(RankNode* node);

    /*
     * Update balance factor of the current node
     * @param - none
     * @return - void
    */
    void update_bf();
    
    /*
     * Update height of the current node
     * @param - none
     * @return - void
    */
    void update_height();

    /*
     * Helper function for remove_group in streaming:
     * Removes each user from the group
     * @param - none
     * @return - void
    */
    void inorder_remove();

    /*
     * The following class is a friend class in order to allow full access to private fields and functions of
     * RankNode, allowing RankNode to be a mostly private class, while allowing the system to run smoothly.
    */
    template <class N, class M>
    friend class Tree;

    /*
     * The internal fields of RankNode: pointers to the parent node and two child nodes
     */
    RankNode* m_parent;
    RankNode* m_left;
    RankNode* m_right;
    double m_prize;

};

template<class T>
RankNode<T>::RankNode() : m_parent(nullptr), m_left(nullptr), m_right(nullptr), m_prize(0) {}

template <class T>
void RankNode<T>::add_prize(double prize, int min) {
    RankNode<T>* x = this;
    RankNode<T>* parent = nullptr;
    //Find the closest ID from the left side of min:
    while (x != nullptr) {
        parent = x;
        if (x->m_id == min) {
            break;
        }
        if (min > x->m_id) {
            x = x->m_right;
        }
        else {
            x = x->m_left;
        }
    }
    //Went too far down - go back up:
    while (parent->m_id > min && (parent->m_parent != nullptr)) {
        parent = parent->m_parent;
    }
    if (parent->m_id > min) {
        return;
    }
    //Change the prize amounts as necessary by searching for the known ID in the tree:
    x = this;
    while (x != nullptr) {
        if (x->m_id == parent->m_id) {
            if (x->m_parent != nullptr && x->m_parent->m_left == x) {
                x->m_prize += prize;
            }
            else if(x->m_parent == nullptr) {
                x->m_prize += prize;
            }
            if (x->m_right != nullptr) {
                x->m_right->m_prize -= prize;
            }
            break;
        }
        else if (parent->m_id > x->m_id) {
            //If turning right from the root or came after left turn, add prize to the parent turning from:
            if((x->m_parent == nullptr) || (x->m_parent->m_left == x)) {
                x->m_prize += prize;
            }
            x = x->m_right;
        }
        else {
            //If the first left turn after a right turn
            if (x->m_parent != nullptr && x->m_parent->m_right == x) {
                x->m_prize -= prize;
            }
            x = x->m_left;
        }
    }
}

template <class T>
double RankNode<T>::calculate_prize() {
    int prize = 0;
    RankNode<T>* temp = this;
    while (temp != nullptr) {
        prize += temp->m_prize;
        temp = temp->m_parent;
    }
    return prize;
}

template <class T>
void RankNode<T>::define_prize() {
    if (this != nullptr) {
        int prize = this->calculate_prize();
        if (prize == 0) {
            this->m_prize = 0;
        }
        else {
            this->m_prize = (-1)*prize;
        }
    }
} 

//--------------------------------Public Helper Function for streaming--------------------------------------------

template<class T>
int RankNode<T>::get_height() const {
    return this->m_height;
}

//--------------------------------------------Rotations---------------------------------------------------

//Left-Left tree rotation, on the node with balance factor of +2
template <class T>
typename RankNode<T>::RankNode* RankNode<T>::ll_rotation(RankNode<T>* node)
{
    RankNode<T>* tmpToReturn = node;
    //Changing A->B to A->Parent
    m_left->m_parent = m_parent;
    //Changing Parent->B to Parent->A
    if (m_parent != nullptr) {
        if (m_parent->m_left == this) {
            m_parent->m_left = m_left;
        }
        else {
            m_parent->m_right = m_left;
        }
    }
    else {
        tmpToReturn = m_left;
    }
    //Changing B->Parent to B->A
    m_parent = m_left;
    //Changing Ar->A to Ar->B
    if (m_left->m_right != nullptr) {
        m_left->m_right->m_parent = this;
        m_left->m_right->m_prize += m_left->m_prize;
    }
    //Changing B->A to B->Ar
    m_left = m_left->m_right;
    //Changing A->Ar to A->B
    m_parent->m_right = this;
    int tmp = m_prize;
    m_prize = m_parent->m_prize*(-1);
    m_parent->m_prize += tmp;
    return tmpToReturn;
}


//Right-Right tree rotation, on the node with balance factor of -2
template <class T>
typename RankNode<T>::RankNode* RankNode<T>::rr_rotation(RankNode<T>* node)
{
    RankNode<T>* tmpToReturn = node;
    m_right->m_parent = m_parent;
    if (m_parent != nullptr) {
        if (m_parent->m_right == this) {
            m_parent->m_right = m_right;
        }
        else {
            m_parent->m_left = m_right;
        }
    }
    else {
        tmpToReturn = m_right;
    }
    m_parent = m_right;
    if(m_right->m_left != nullptr) {
        m_right->m_left->m_parent = this;
        m_right->m_left->m_prize += m_right->m_prize;
    }
    m_right = m_right->m_left;
    m_parent->m_left = this;
    int tmp = m_prize;
    m_prize = m_parent->m_prize*(-1);
    m_parent->m_prize += tmp;
    return tmpToReturn;
}


//Right-Left tree rotation, on the node with balance factor of -2
template <class T>
typename RankNode<T>::RankNode* RankNode<T>::rl_rotation(RankNode<T>* node)
{
    RankNode<T>* tmp = m_right->ll_rotation(node);
    tmp = rr_rotation(tmp);
    return tmp;
}


//Left-Right tree rotation, on the node with balance factor of +2
template <class T>
typename RankNode<T>::RankNode* RankNode<T>::lr_rotation(RankNode<T>* node)
{
    RankNode<T>* tmp = m_left->rr_rotation(node);
    tmp = ll_rotation(tmp);
    return tmp;
}


//----------------------------------------------Node Stats---------------------------------------------------

//Update the balance factor of the specific node
template <class T>
void RankNode<T>::update_bf()
{
    int heightLeft = 0, heightRight = 0;
    if (m_left != nullptr) {
        heightLeft = m_left->m_height + 1;
    }
    if (m_right != nullptr) {
        heightRight = m_right->m_height + 1;
    }
    this->m_bf = heightLeft - heightRight;
}


//Update the subtree height of the specific node
template <class T>
void RankNode<T>::update_height()
{
    int heightLeft = 0, heightRight = 0;
    if (m_left != nullptr) {
        heightLeft = m_left->m_height + 1;
    }
    if (m_right != nullptr) {
        heightRight = m_right->m_height + 1;
    }
    if (heightLeft >= heightRight) {
        this->m_height = heightLeft;
    }
    else {
        this->m_height = heightRight;
    }
}

//------------------------------------Helper Function for streaming-------------------------------------------------

template <class T>
void RankNode<T>::inorder_remove() {
    if (this != nullptr && this->m_data != nullptr) {
        m_left->inorder_remove();
        this->m_data->update_views();
        this->m_data->remove_group();
        m_right->inorder_remove();
    }
}


template <class T>
void RankNode<T>::printNode() {
    int parent, left, right;
    if (m_parent == nullptr) {
        parent = -1;
    }
    else {
        parent = m_parent->m_id;
    }
    if (m_left == nullptr) {
        left = -1;
    }
    else {
        left = m_left->m_id;
    }
    if (m_right == nullptr) {
        right = -1;
    }
    else {
        right = m_right->m_id;
    }
    int debt = 0;
    int prize = 0;
    if (this->m_id != -1) {
        debt = this->m_data->get_debt();
        prize = m_prize;
    }
    std::cout << "ID = " << Node<T>::m_id << ", Parent = " << parent << ", Left = " 
            << left << ", Right = " << right << ", Debt = " << debt << ", Prize = " << prize << std::endl;
}


template <class T>
void RankNode<T>::printData() {
    std::cout << "ID = " << Node<T>::m_id << std::endl;
}


template <class T>
void RankNode<T>::inorderWalkNode(bool flag) {
    if (this != nullptr) {
        m_left->inorderWalkNode(flag);
        if (flag) {
            this->printNode();
        }
        else {
            this->printData();
        }
        m_right->inorderWalkNode(flag);
    }
}

//-----------------------------------------------------------------------------------------------------------

#endif //RANKNODE_H
#ifndef GENERICNODE_H
#define GENERICNODE_H

#include "Node.h"

/*
* Class Generic Node
* This class is used to create the separate nodes in a basic AVL tree.
*/
template <class T>
class GenericNode : public Node<T> {
public:

    /*
    * Constructor of GenericNode class
    * @param - none
    * @return - A new instance of GenericNode
    */ 
    GenericNode();

    /*
    * Copy Constructor and Assignment Operator of GenericNode class
    * RecordsCompany does not allow two nodes of the same customer or record (repeating ID's).
    * Therefore the system does not allow a copy constructor or assignment operator.
    */
    GenericNode(const GenericNode&) = delete;
    GenericNode& operator=(const GenericNode& other) = delete;

    /*
    * Destructor of GenericNode class
    * @param - none
    * @return - void
    */
    virtual ~GenericNode() = default;

    /*
    * Returns the height of a node
    * @param - none
    * @return - height
    */
    int get_height() const;

    /*
    * Returns the left child of a node
    * @param - none
    * @return - GenericNode*, the node's left child
    */
    GenericNode *get_left();

    /*
    * Returns the right child of a node
    * @param - none
    * @return - GenericNode*, the node's right child
    */
    GenericNode *get_right();
    
    /*
    * An empty function that allows AVLTree to work with RankNode as well as GenericNode
    * @param - none
    * @return - void
    */
    void define_prize();

private:

    /*
     * Left-Right Rotation
     * @param - Node with balance factor of +2
     * @return - pointer to ComplexNode
     */
    GenericNode* ll_rotation(GenericNode* node);

    /*
     * Right-Right Rotation
     * @param - Node with balance factor of -2
     * @return - pointer to ComplexNode
     */
    GenericNode* rr_rotation(GenericNode* node);

    /*
     * Right-Left Rotation
     * @param - Node with balance factor of -2
     * @return - pointer to ComplexNode
    */
    GenericNode* rl_rotation(GenericNode* node);

    /*
     * Left-Left Rotation
     * @param - Node with balance factor of +2
     * @return - pointer to ComplexNode
    */
    GenericNode* lr_rotation(GenericNode* node);

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
    * Helper function for enlarge_hash_table in Records Company:
    * Recursively insert all the customers in tree into the given array
    * @param - array of customers, integer of the current index in the array
    * @return - current index in the array.
    */
    int get_data_inorder(T* array, int index) const;

    /*
     * The following class is a friend class in order to allow full access to private fields and functions of
     * GenericNode, allowing GenericNode to be a mostly private class, while allowing the system to run smoothly.
    */
    template <class N, class M>
    friend class Tree;

    /*
     * The internal fields of GenericNode: pointers to the parent node and two child nodes
     */
    GenericNode* m_parent;
    GenericNode* m_left;
    GenericNode* m_right;

};

//--------------------------------------------Constructor---------------------------------------------------

template <class T>
GenericNode<T>::GenericNode() :
        Node<T>(),
        m_parent(nullptr),
        m_left(nullptr),
        m_right(nullptr)
{}

//--------------------------------Public Helper Functions for RecordsCompany--------------------------------------------

template<class T>
int GenericNode<T>::get_height() const {
    return this->m_height;
}

template<class T>
GenericNode<T> *GenericNode<T>::get_left(){
    return m_left;
}

template<class T>
GenericNode<T> *GenericNode<T>::get_right(){
    return m_right;
}

template <class T>
void GenericNode<T>::define_prize() {}

//--------------------------------------------Rotations---------------------------------------------------

//Left-Left tree rotation, on the node with balance factor of +2
template <class T>
typename GenericNode<T>::GenericNode* GenericNode<T>::ll_rotation(GenericNode<T>* node)
{
    GenericNode<T>* tmpToReturn = node;
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
    }
    //Changing B->A to B->Ar
    m_left = m_left->m_right;
    //Changing A->Ar to A->B
    m_parent->m_right = this;
    return tmpToReturn;
}


//Right-Right tree rotation, on the node with balance factor of -2
template <class T>
typename GenericNode<T>::GenericNode* GenericNode<T>::rr_rotation(GenericNode<T>* node)
{
    GenericNode<T>* tmpToReturn = node;
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
    }
    m_right = m_right->m_left;
    m_parent->m_left = this;
    return tmpToReturn;
}


//Right-Left tree rotation, on the node with balance factor of -2
template <class T>
typename GenericNode<T>::GenericNode* GenericNode<T>::rl_rotation(GenericNode<T>* node)
{
    GenericNode<T>* tmp = m_right->ll_rotation(node);
    tmp = rr_rotation(tmp);
    return tmp;
}


//Left-Right tree rotation, on the node with balance factor of +2
template <class T>
typename GenericNode<T>::GenericNode* GenericNode<T>::lr_rotation(GenericNode<T>* node)
{
    GenericNode<T>* tmp = m_left->rr_rotation(node);
    tmp = ll_rotation(tmp);
    return tmp;
}


//----------------------------------------------Node Stats---------------------------------------------------

//Update the balance factor of the specific node
template <class T>
void GenericNode<T>::update_bf()
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
void GenericNode<T>::update_height()
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

//------------------------------------Helper Function for RecordsCompany-----------------------------------------------

template <class T>
int GenericNode<T>::get_data_inorder(T* array, int index) const
{
    if (this != nullptr) {
        index = m_left->get_data_inorder(array, index);
        array[index++] = this->m_data;
        index = m_right->get_data_inorder(array, index);
    }
    return index;
}

//-----------------------------------------------------------------------------------------------------------

#endif //GENERICNODE_H
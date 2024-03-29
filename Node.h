#ifndef NODE_H
#define NODE_H

/*
* Class Node
* This class is used as a base class for the specific kinds of nodes in the tree.
*/
template <class T>
class Node {
public:

    /*
    * Constructor of Node class
    * @param - none
    * @return - A new instance of Node
    */     
    Node();

    /*
    * Copy Constructor and Assignment Operator of Node class
    * RecordsCompany does not allow two nodes of the same customer or record (repeating ID's).
    * Therefore the system does not allow a copy constructor or assignment operator.
    */    
    Node(const Node&) = delete;
    Node& operator=(const Node& other) = delete;

    /*
    * Destructor of Node class
    * @param - none
    * @return - void
    */
    virtual ~Node();

    /*
    * Returns the ID of a node
    * @param - none
    * @return - ID
    */
    int getID() const;

    /*
    * Returns the data of a node
    * @param - none
    * @return - T&, a reference to the node's data
    */
    T& get_data();

protected:

    /*
     * The internal fields of Node:
     *   The data of the node of type T
     *   The height of the subtree of the node
     *   The balance factor of the node
     *   The key by which the tree is sorted (id)
     */
    T m_data;
    int m_height;
    int m_bf;
    int m_id;

    /*
     * The following class is a friend class in order to allow full access to private fields and functions of
     * Node.
     * This allows Node to be a mostly protected class, while allowing the system to run smoothly.
    */    
    template <class N, class M>
    friend class Tree;
};


template <class T>
Node<T>::Node() :
    m_data(nullptr),
    m_height(-1),
    m_bf(0),
    m_id(-1)
{}

template <class T>
Node<T>::~Node()
{
    m_data = nullptr;
}

template <class T>
int Node<T>::getID() const {
    return m_id;
}

template<class T>
T& Node<T>::get_data(){
    return m_data;
}



#endif //NODE_H
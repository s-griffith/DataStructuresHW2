#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

/*
* Class NodeNotFound : std::exception
* This class represents an exception thrown when a requested node is not found.
*/
class NodeNotFound : public std::exception {

    /*
    * Provide information regarding the error - the node that was searched was not found.
    * @param - none
    * @return - const char* - description of exception
    */
    const char* what() const noexcept override
    {
        return "Node Not Found Error: The following node does not exist in the tree";
    }

};


/*
* Class InvalidID : std::exception
* This class represents an exception thrown when an ID number given is invalid.
*/
class InvalidID : public std::exception {

    /*
    * Provide information regarding the error - the ID given already exists in the tree.
    * @param - none
    * @return - const char* - description of exception
    */
    const char* what() const noexcept override {
        return "Invalid ID Error: ID already exists in the tree.";
    }
    
};

/*
* Class InvalidRange : std::exception
* This class represents an exception thrown when a range of ID numbers given is invalid.
*/
class InvalidRange : public std::exception {

    /*
    * Provide information regarding the error - the ID range given does not exist in the tree.
    * @param - none
    * @return - const char* - description of exception
    */
    const char* what() const noexcept override {
        return "Invalid Range Error: ID range does not exist in the tree.";
    }
    
};

#endif //EXCEPTION_H
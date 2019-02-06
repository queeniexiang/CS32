#include <iostream>
#include <cstdlib>
#include "Set.h"


using namespace std;

Set::Set() {
    m_head = new Node;
    m_head->next = m_head;
    m_head->previous = m_head;
    m_size = 0;
}

//Destructor
//Deletes Nodes objects of a Set including the dummy node
Set::~Set() {
    
    //Set pointer starting at the first node of the set
    Node * p = m_head->next;
    
    //Traverse through the set
    while (p != m_head) {
        Node * temp = p;
        p = p->next;
        delete temp;
    }
    
    //Delete the head or the dummy node
    delete p;
    
    
    /*
    //Pointer p that points to the head node of the set
    //This pointer will iterate through the set

    Node * p = m_head;
    //Iterating through the set to delete nodes
    for (int i = 0; i < m_size-1; i++) {
     
        //Create a temporary node that points to the current node
        Node* temp = p;
        
        //Move current node to the next node in the list
        p = p->next;
        
        //Delete the temporary node that was pointing to the original current node
        delete temp;
     
        if (i == m_size-2) {
            delete p;
        }
    }
    */
   
    
}

//Copy Constructor
Set::Set(const Set& other) {
    //Allocating the memory for the new variable/set
    m_size = other.m_size;
    
    //Creating a dummy node that the head points to for the new set
    m_head = new Node;
    
    //Set a pointer that points to the head of the new set
    //Needed for iterating through the new set (because we need to copy contents of the other set into the new set)
    Node* currentNodePointer = m_head;
    
    //This loop is for copying contents from the other set into the new set (not including the dummy node
    for (Node*p = other.m_head->next; p != other.m_head; p = p->next) {
        
        //This node (which is a copy of node p from the other set) will be added into (connected into) the new set
        Node* newNode = new Node;
        newNode->value = p->value;
        
        //Connecting the newNode into the new set
        //Connects the previous node of the new set to this newNode
        currentNodePointer->next = newNode;
        newNode->previous = currentNodePointer;
        
        //Sets up currentNodePointer to point to the newly linked node in the set
        //This allows for the traverseral through the new set
        currentNodePointer = newNode;
    }
    
    //Finishes up linking by making the new set (linked list) circular
    m_head->previous = currentNodePointer;    //The head will point to the last node or tail of the set
    currentNodePointer->next = m_head;       //The tail will point to the head
}


//Assignment Operator overloading
Set& Set::operator=(const Set& rhs) {
    if (this != &rhs) {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

//Returns if a set is empty or not
bool Set::empty() const {
    return m_size == 0;
}

//Returns the size of the set
int Set::size() const {
    return m_size;
}

//Inserts a new node into the set
bool Set::insert(const ItemType& value) {
    
    //If value already exists in the set, return false
    if ( contains(value) ) {
            //cerr << "Value already exist, can't insert!" << endl;
            return false;
    }
    
    //Base case:
    //If there are no nodes in the set yet, insert a new node into the set
    if (m_size == 0) {
        //Creating new node with the given value
        Node * newNode = new Node;
        newNode->value = value;
        
        //Links new node into the set:
        //Because there are no elements in the list yet, link the newNode to the dummy node
        //newNode's next and previous nodes will be the dummy node
        newNode->next = m_head;
        newNode->previous = m_head;
        
        //Link the dummy node to the newNode
        m_head->next = newNode;
        m_head->previous = newNode;
        
        //Increase size
        m_size++;
        return true; 
    }
    
    //If there are already nodes in the set, insert this new node according to alphabetical order from a-z where a is the front/head of the set and z is ithe end/tail
    //Note that the loop starts at m_head->next which means it ignores the dummy node
    else {
        //This boolean checks to the see if the value was inserted or not
        //This is needed because you don't want to insert the value in yet if it hasn't been compared to the entire set
        bool valueInserted = false;
        
        
        for (Node * p = m_head->next; p != m_head; p = p->next) {
            
            //cerr << "inserting: " << value << endl;
            
            //If valueTBInserted is not greater than the current node in the set
            if (! (value > p->value) ) {
                
                //cerr << "value is not greater than current node " << endl;
                
                //Create a new node with the given value
                Node * newNode = new Node;
                newNode->value = value;
                
                //Create a pointer to the previous node in the set (previous to the current node in the loop)
                Node* prev = p->previous;
                
                //Link the newNode into the set
                //The newNode should fall between the current node (p) and the previous node(prev)
                //i.e : prev->newNode->p
                //Hence, the newNode's next node should be p. newNodes' previous node should be prev
                newNode->next = p;
                newNode->previous = prev;
                
                //Link the already existing nodes in the set to the newNode
                //Following the model: prev->newNode->p
                //Hence: previous node's next should point to the newNode. Current node's previous should point to newNode
                prev->next = newNode;
                p->previous = newNode;
                
                /*
                //Printing out new list
                for (Node* p = m_head->next; p != m_head; p = p->next) {
                    cerr << p->value << endl;
                }
                 */
                
                //Value has been inserted in the correct spot, break because insertion is done
                valueInserted = true;
                break;
            }
        }
        
        //If value hasn't been inserted yet upon comparing with all the nodes in the set, it means value is the greatest alphabetically, so put it at the end of the set
        if (!valueInserted) {
            //cerr << value << " wasn't inserted. inserting now " << endl;
            
            //Create a pointer p to the first node of the set and iterate it through until it points to the last node of the set
            Node *p = m_head->next;
            for (int i = 0; i < size()-1; i++) {
                p = p->next;
            }
            
            //Create a new node with the given value
            Node * newNode = new Node;
            newNode->value = value;
            
           // cerr << "p next" << p->next->value;
            
            //Insert p at the end of the set
            //Because p is at the end of the set, it should point to the head as the next element (to make the linked list circular)
            //i.e. node->lastNode(p)->head
            p->next = newNode;
            newNode->previous = p;
            newNode->next = m_head;
            
            //The head of the list should point to the tail to make the list circular
            m_head->previous = newNode;
            
            //Value has been inserted
            valueInserted = true;
        }
        
        //Because value has been inserted, increase the size and return true
        if (valueInserted) {
            //increase size
            m_size++;
            return true; 
        }
    }
    return false;
}


//Erase a node in the set
bool Set::erase(const ItemType& value) {
    //This loops through the entire set of nodes
    //Note: it ignores the dummy node, hence Node* p starts at m_head->next
    for (Node* p = m_head->next; p != m_head; p = p->next) {
        
        //If the value to be removed is found:
        if (p->value == value) {
            
            //Here's a model for how the nodes look like:
            //prevNode->p(which is TB removed)->nextNode
            
            //To get rid of p, simply set prevNode and nextNode to point to each other (link them together)
            //What you want in the end should look like this:
            //prevNode->nextNode;
            
            //Setting up prevNode and nextNode: prevNode is the node before p, nextNode is the node after p
            Node * prevNode = p->previous;
            Node * nextNode = p->next;
            
            //Linking prevNode and nextNode to each other and thus taking p out of the set
            //prevNode's next node will be nextNode
            //nextNode's previous node will be prevNode
            prevNode->next = nextNode;
            nextNode->previous = prevNode;
            
            //Delete the nodeTBRemoved
            delete p;
            
            //Subtract one from size
            m_size--;
            
            //Finished, so return true
            return true;
        }
    }
    //If the value was not found in the set, return false
    return false;
}

bool Set::contains(const ItemType& value) const {
    //Search through the entire set (linearly OR node by node)
    for (Node* p = m_head->next; p != m_head; p = p->next) {
        //If node with the given value is found, return true
        if (p->value == value) {
            return true;
        }
    }
    
    //If node is not found, return false
    return false;
}


bool Set::get(int pos, ItemType& value) const {
    //If pos is greater than or equal to 0 and pos is less than m_size, look for the  given value
    if (0 <= pos && pos < size() ) {
        
        //Node p is a pointer node which will traverse through the set of nodes (to get the value)
        Node * p = m_head->next;
        
        //Node p will traverse through the set pos number of times
        //Because the set is already organized in alphabetical order, we just need to iterate through the set and stop at the right place (at position pos)
        for (int i = 0; i < pos; i++) {
            p = p->next;
        }
        
        //Put the value that fits the criteria into value
        value = p->value;
        
        //Finished, return true
        return true;
    }
    
    else {
        //If the position pos was out of bounds, return false:
        return false;
    }
}

void Set::swap(Set& other) {
    
    //Swapping head pointers
    Node * temp_head = m_head;
    m_head = other.m_head;
    other.m_head = temp_head;
    
    //Swapping sizes
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
}

/*
void Set::dump() {
    for (Node* p = m_head->next; p != m_head; p = p->next) {
        cerr << p->value << endl;
    }
}
*/

//Non-member functions:

//When this function returns, result must contain one copy of each of the values that appear in s1 or s2 or both, and must not contain any other values.
void unite(const Set& s1, const Set& s2, Set& result) {
    
    //Add everything in s1 into result, if it's not already in result
    for (int i = 0; i < s1.size(); i++) {
        ItemType value;
        if ( (s1.get(i, value)) && (!(result.contains(value))) ) {
            result.insert(value);
        }
    }
    
    //Add everything in s2 into result, if it's not already in result
    for (int i = 0; i < s2.size(); i++) {
        ItemType value;
        if ( (s2.get(i, value)) && (!(result.contains(value))) ) {
            result.insert(value);
        }
    }
}

//When this function returns, result must contain one copy of each of the values that appear in s1 but not s2, and must not contain any other values.
void subtract(const Set& s1, const Set& s2, Set& result) {
    
    //Remove everything from result that's in s2
    for (int i = 0; i < s2.size(); i++) {
        ItemType value;
        s2.get(i, value);
        result.erase(value);
    }
    
    //If anything that remains in result is in s1 but also in s2, remove it
    for (int i = 0; i < s1.size(); i++) {
        ItemType value;
        result.get(i, value);
        if (s2.contains(value)) {
            result.erase(value);
        }
    }
}

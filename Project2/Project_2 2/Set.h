#include <string>

#ifndef SET_INCLUDED
#define SET_INCLUDED

using namespace std;
using ItemType = std::string; 

class Set
{
public:
    Set();      //Default constructor
    ~Set();     //Deconstructor
    Set(const Set& other);        //Copy constructor
    Set& operator = (const Set& other);       //Assignment operator
    
    //Member functions:
    bool empty() const;   // Return true if the set is empty, otherwise false
    
    int size() const;     // Return the number of items in the set.
    
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    
    bool erase(const ItemType& value);
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
    bool contains(const ItemType& value) const;
     // Return true if the value is in the set, otherwise false.
    
    bool get(int pos, ItemType& value) const;
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
    
    //void dump(); 
    
private:
    int m_size; //Holds the size of the set or how many nodes are in the set
    
    
    //Declares Node as its own type with its own properties
    //Each node has points to a next node, previous node, and has a value of ItemType
    struct Node {
        Node* next;
        Node* previous;
        ItemType value;
    };
    
    //Pointer to the first/head node of the set
    Node* m_head;
};

//Non-member functions
void unite(const Set& s1, const Set& s2, Set& result);
  //When this function returns, result must contain one copy of each of the values that appear in s1 or s2 or both, and must not contain any other values.
    // You must not assume result is empty when it is passed in to this function; it might not be

void subtract(const Set& s1, const Set& s2, Set& result);
  //When this function returns, result must contain one copy of each of the values that appear in s1 but not s2, and must not contain any other values.
    // You must not assume result is empty when it is passed in to this function; it might not be

#endif /* SET_INCLUDED */

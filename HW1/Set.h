#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

//using ItemType = std::string;
using ItemType = unsigned long;

const int DEFAULT_MAX_ITEMS = 250;

class Set
{
public:
    Set();         // Create an empty set (i.e., one with no items).
    
    bool empty() const;  // Return true if the set is empty, otherwise false.
    
    int size() const;    // Return the number of items in the set.
    
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    bool insert(const ItemType& value);
    
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    bool erase(const ItemType& value);
    
    // Return true if the value is in the set, otherwise false.
    bool contains(const ItemType& value) const;
    
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    bool get(int i, ItemType& value) const;
    
    // Exchange the contents of this set with the other one.
    void swap(Set& other);
    
private:
    ItemType m_arr[DEFAULT_MAX_ITEMS]; //array containing values
    int m_size = 0; //size of the array 
};

#endif //SET_INCLUDED

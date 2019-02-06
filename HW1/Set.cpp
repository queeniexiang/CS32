#include <iostream>

#include "Set.h" 
using namespace std;

Set::Set() {
    m_size = 0;
}

bool Set::empty() const {
    if (size() == 0) {
        return true;
    }
    
    return false;
}

// Return the number of items in the set.
int Set::size() const {
    return m_size;
}

// Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.

//Note: insert() inserts values in alphabetically from a to z to make get() easier
bool Set::insert(const ItemType& value) {

    //Leave the set unchanged and return false if the value was not inserted
    //(perhaps because it was already in the set or because the set has a fixed capacity and
    // is full).
    if (contains(value) || m_size >= DEFAULT_MAX_ITEMS) {
        return false;
    }
    
    else {
        
        //Base case
        if (m_size == 0) {
            m_arr[m_size] = value;
            m_size++;
        }
        
        //Insert everything to the back and compare alphabetical order starting from the back
        else {
            m_arr[m_size] = value; //inserting to the back or the m_size position
            int i = m_size;
            while (i > 0) { //Loop that starts comparison
                if (! (m_arr[i] > m_arr[i-1]) ) {
                    //If the current word is not greater than the previous word, swap the positions of the two
                    ItemType temp = m_arr[i];
                    m_arr[i] = m_arr[i-1];
                    m_arr[i-1] = temp;
                }
                
                else {
                    i--;
                }
            }
            m_size++; //Increase size because you added a new word
        }
    }
         
    /*
    cerr << "****************" << endl;
    cerr << "current m_arr: " << endl;
    for (int i = 0; i < m_size; i++) {
        cerr << m_arr[i] << endl;
    }
    cerr << "****************" << endl;
    */
    
    return true;
}


// Remove the value from the set if present.
// Return true if the value was removed;
// Otherwise, leave the set unchanged and return false.
bool Set::erase(const ItemType& value) {
    if (contains(value)) { //value is present
        for (int i = 0; i < m_size; i++) { //using a for-loop to erase value
            if (m_arr[i] == value) {
                for (int j = i; j < size()-1; j++) {
                    //if value is at position i, copy position i+1 into i's spot
                    //This way, value will be replaced by what's at i+1
                    m_arr[j] = m_arr[j+1];
                }
                m_size--;
                return true;
                
                /*
                cerr << "****************" << endl;
                cerr << "current m_arr: " << endl;
                for (int i = 0; i < m_size; i++) {
                    cerr << m_arr[i] << endl;
                }
                cerr << "****************" << endl;
                */
            }
        }
    }
    
    return false;
}

// Return true if the value is in the set, otherwise false.
bool Set::contains(const ItemType& value) const {
    for (int i = 0; i < size(); i++) {
        if (m_arr[i] == value) {
            return true;
        }
    }
    return false;
}


// If 0 <= i < size(), copy into value the item in the set that is
// strictly greater than exactly i items in the set and return true.
// Otherwise, leave value unchanged and return false.
bool Set::get(int i, ItemType& value) const {
    if ( 0 <= i && i < size() ) {
        value = m_arr[i]; //everything should be alphabetically organized from a-z by insert() function
        return true;
    }
    
    else {
        return false; 
    }
}

// Exchange the contents of this set with the other one.
void Set:: swap(Set& other) {
    //Creating a temporary set to hold the values of current set
    Set temp_array;
    temp_array.m_size = m_size;
    for (int i = 0; i < m_size; i++) { //copying values into temp m_array
        temp_array.m_arr[i] = m_arr[i];
    }
    
    //Copy contents and size of other into current set
    m_size = other.size();
    for (int i = 0; i < m_size; i++) {
        m_arr[i] = other.m_arr[i];
    }
    
    //Copy contents of current set (stored in temp set) into other 
    other.m_size = temp_array.size();
    for (int i = 0; i < other.size(); i++) {
        other.m_arr[i] = temp_array.m_arr[i];
    }
    
    /*
    cerr << "****************" << endl;
    cerr << "current m_arr: " << endl;
    for (int i = 0; i < m_size; i++) {
        cerr << m_arr[i] << endl;
    }
    cerr << "****************" << endl;
    
    cerr << "****************" << endl;
    cerr << "other m_arr: " << endl;
    for (int i = 0; i < other.m_size; i++) {
        cerr << other.m_arr[i] << endl;
    }
    cerr << "****************" << endl;
     */
}


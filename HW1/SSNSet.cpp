#include<iostream>

#include "SSNSet.h"

using namespace std;

// Create an empty SSN set.
SSNSet::SSNSet() {
}

// Add an SSN to the SSNSet.  Return true if and only if the SSN
// was actually added.
bool SSNSet::add(unsigned long ssn) {
    return m_set.insert(ssn);
}

// Return the number of SSNs in the SSNSet.
int SSNSet::size() const {
    return m_set.size();
}

// Write every SSN in the SSNSet to cout exactly once, one per
// line.  Write no other text.
void SSNSet::print() const {
    ItemType temp_holder;
    
    for (int i = 0; i < m_set.size(); i++) {
        m_set.get(i, temp_holder);
        cout << temp_holder << endl;
    }

}



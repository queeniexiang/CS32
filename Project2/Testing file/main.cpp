
#include "Set.h"
#include <iostream>
#include <cassert>
    
    using namespace std;
    
    void test()
    {
        Set ss;  // ItemType is std::string
        ss.insert("aaa");
        ss.insert("ccc");
        ss.insert("bbb");
        ss.insert("aaa");
        ss.insert("bolonge");
        ss.insert("bell");
        ss.insert("carrot");
        ss.insert("apple");
        assert(ss.size() == 7);
        
        ItemType x = "apple";
        assert(ss.get(0, x) && x=="aaa");
        assert(ss.get(1, x) && x=="apple");
        assert(ss.get(2, x) && x=="bbb");
        assert(ss.get(3, x) && x=="bell");
        assert(ss.erase("aaa"));
        assert(!ss.contains("aaa"));
        assert(ss.size() == 6);
        assert(!ss.erase("bab"));
        assert(ss.erase("bbb"));
        assert(!ss.contains("bbb"));
        assert(ss.contains("ccc"));
        assert(ss.size() == 5);
        
    }
    
    int main()
    {
        test();
        cerr << "DONE" << endl;
    }
    


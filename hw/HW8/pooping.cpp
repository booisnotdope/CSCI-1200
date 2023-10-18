#include <iostream>
#include <cassert>
#include "BPlusTree.h"
#include <fstream>

int main(){
    BPlusTree<int> b1(5);
    b1.insert(0);
    b1.insert(1);
    b1.insert(2);
    
    assert(b1.find(0) -> contains(0));
    assert(b1.find(1) -> contains(1));
    assert(b1.find(2) -> contains(2));

    assert(b1.find(54) == b1.find(0));
}
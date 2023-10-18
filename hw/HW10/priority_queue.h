#ifndef priority_queue_h_
#define priority_queue_h_

#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include "image.h"

// The DistancePixel_PriorityQueue is a customized, non-templated
// priority queue that stores DistancePixel pointers in a heap.  The 
// elements in the heap can be looked up in a map, to quickly find out
// the current index of the element within the heap.

// ASSIGNMENT: The class implementation is incomplete.  Finish the
//   implementation of this class, and add any functions you need.

// =========================================================================

class DistancePixel_PriorityQueue {

 public:
  
  // --------------------------
  // CONSTRUCTORS
  // default constructor
  DistancePixel_PriorityQueue() {}
  // construct a heap from a vector of data
  DistancePixel_PriorityQueue(const std::vector<DistancePixel*> &values) {
    m_heap = values;
    for(DistancePixel* i: values) this -> push(i);
  }

  // ------------------------
  // ACCESSORS
  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }
  int last_non_leaf() { return (size()-1) / 2; }
  int get_parent(int i) { assert (i > 0 && i < size()); return (i-1) / 2; }
  bool has_left_child(int i) { return (2*i)+1 < size(); }
  bool has_right_child(int i) { return (2*i)+2 < size(); }
  int get_left_child(int i) { assert (i >= 0 && has_left_child(i)); return 2*i + 1; }
  int get_right_child(int i) { assert (i >= 0 && has_right_child(i)); return 2*i + 2; }

  // read the top element
  const DistancePixel* top() const  {
    assert(!m_heap.empty());
    return m_heap[0]; 
  }

  // is this element in the heap?
  bool in_heap(DistancePixel* element) const {
    std::map<DistancePixel*,int>::const_iterator itr = backpointers.find(element);
    return (itr != backpointers.end());
  }

  // add an element to the heap
  void push(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr == backpointers.end());
    m_heap.push_back(element);
    backpointers[element] = m_heap.size()-1;
    this->percolate_up(int(m_heap.size()-1));
  }

  // the value of this element has been edited, move the element up or down
  void update_position(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr != backpointers.end());
    this->percolate_up(itr->second);
    this->percolate_down(itr->second);
  }
  
  // remove the top (minimum) element
  void pop() {
    assert(!m_heap.empty());
    int success = backpointers.erase(m_heap[0]);
    assert (success == 1);
    m_heap[0] = m_heap.back();
    m_heap.pop_back();
    this->percolate_down(0);
  } 

 private:

  // REPRESENTATION
  // the heap is stored in a vector representation (the binary tree
  // structure "unrolled" one row at a time)
  std::vector<DistancePixel*> m_heap;
  // the map stores a correpondence between elements & indices in the heap
  std::map<DistancePixel*,int> backpointers;
  // private helper functions
  //taken from lab 11
  void percolate_up(int i) {
    for(; i > 0 && m_heap[i] < m_heap[(i-1)/2]; i = (i-1)/2){
      int back_temp = backpointers[m_heap[i]];
      backpointers[m_heap[i]] = backpointers[m_heap[(i-1/2)]];
      backpointers[m_heap[(i-1/2)]] = back_temp;
      DistancePixel* temp = m_heap[(i-1)/2];
      m_heap[(i-1)/2] = m_heap[i];
      m_heap[i] = temp;
    }
  }
  
  //taken from lab 11
  void percolate_down(long unsigned int i) {
    for(; i < m_heap.size()/2 + 1; ){
          unsigned int j = 2*i+1;
          if(2*i+2 < m_heap.size() && m_heap[2*i+2] < m_heap[j]){
              j = 2*i+2;
          }
          if(m_heap[j] < m_heap[i]){
              int back_temp = backpointers[m_heap[i]];
              backpointers[m_heap[i]] = backpointers[m_heap[j]];
              backpointers[m_heap[j]] = back_temp;
              DistancePixel* temp = m_heap[i];
              m_heap[i] = m_heap[j];
              m_heap[j] = temp;
              i = j;
          } else {
              break;
          }
      }
  }
};

#endif

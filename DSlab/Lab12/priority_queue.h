#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;
  void percolate_up(unsigned int i){
    for(; i > 0 && m_heap[i] < m_heap[(i-1)/2]; i = (i-1)/2){
        T temp = m_heap[(i-1)/2];
        m_heap[(i-1)/2] = m_heap[i];
        m_heap[i] = temp;
    }
  }

  void percolate_down(unsigned int i){
      for(; i < m_heap.size()/2 + 1; ){
          unsigned int j = 2*i+1;
          if(2*i+2 < m_heap.size() && m_heap[2*i+2] < m_heap[j]){
              j = 2*i+2;
          }
          if(m_heap[j] < m_heap[i]){
              T temp = m_heap[i];
              m_heap[i] = m_heap[j];
              m_heap[j] = temp;
              i = j;
          } else {
              break;
          }
      }
  }

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values ){   
    m_heap = values;
    for (int i = m_heap.size() / 2 - 1; i >= 0; i--) {
      percolate_down(i);
    }
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry ){
    m_heap.push_back(entry);
    percolate_up(m_heap.size() - 1);
  }

  void pop(){
    assert( !m_heap.empty() );
    m_heap[0] = m_heap.back();
    m_heap.pop_back();
    percolate_down(0);
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( ){
    return this->check_heap( this->m_heap );  
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap ){
    for (unsigned int i = 0; i < heap.size(); i++)
    {
      if (2 * i + 1 < heap.size() && heap[2 * i + 1] < heap[i]) {
        return false;
      }
      if (2 * i + 2 < heap.size() && heap[2 * i + 2] < heap[i]) {
        return false;
      }
    }
    return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr ){
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v ){  
  priority_queue<T> heap(v);
  for (int i = 0; i < v.size(); ++i){
    v[i] = heap.top();
    heap.pop();
  }

}

#endif

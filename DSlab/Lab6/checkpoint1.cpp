#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>


// template <class T>
// void print(std::vector<T> &data, const std::string &label) {
//   std::cout << label << " ";
//   for (int i = 0; i < data.size(); i++) {
//     std::cout << " " << data[i];
//   }
//   std::cout << std::endl;
// }

// template <class T>
// void reverse(std::vector<T> &data) {
//   int data_half = data.size()/2 + data.size()%2;
//   for (int i = 0; i < data_half; i++){
//     T temp = data[i];
//     data[i] = data[data.size() - i - 1];
//     data[data.size() - i - 1] = temp;
//   }
// }

template <class T>
void print(std::list<T> &data, const std::string &label) {
  std::cout << label << " ";
  typename std::list<T>::iterator i;
  for(i = data.begin(); i != data.end(); ++i){
    std::cout << ' ' << (*i);
  }
  std::cout << std::endl;
}

template <class T>
void reverse(std::list<T> &data) {
  typename std::list<T>::iterator i = data.begin();
  for (; i != data.end(); ){
    T temp = (*i);
    i = data.erase(i);
    data.push_front(temp);
  }
}

// template <class T>
// void reverse(std::list<T> &data) {
//   typename std::list<T>::reverse_iterator i = data.rbegin();
//   for (i; i != data.rend();--i){
//     T temp = (*i);
//     i = data.erase(i);
//     data.push_back(temp);
//   }
// }

int main() {
  std::list<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::list<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");
}

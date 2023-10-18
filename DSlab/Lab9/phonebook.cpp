// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
void add(std::map<int, string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(map<int, string> & phonebook, int number) {
  std::map<int, string>::iterator i = phonebook.find(number);
  if (i == phonebook.end()){
    cout << "who are you" << endl;
  } else {
    cout << phonebook[number] << " slid into your dms" << endl;
  }
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  map<int, string> phonebook;

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);
  identify(phonebook, 20000000);
}
//vector is allocated 10000 spaces but only 3 of them are being used

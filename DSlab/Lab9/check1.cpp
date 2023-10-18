#include <iostream>
#include <map>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]){
    std::map<int, int> poop;
    std::ifstream in_str(argv[1]);
    int temp;
    while (in_str >> temp){
        std::map<int, int>::iterator pee = poop.find(temp);


        if (pee == poop.end()){

            poop.insert(std::pair<int, int>(temp, 1));
        } else {
            int yum = pee -> first;
            int yumm = pee -> second;

            poop.erase(pee);
            poop.insert(std::pair<int, int>(yum, yumm+1));

        }
    }
    std::vector<int> found_ya;
    int highest = 0;
    std::map<int, int>::const_iterator pee;
    for (pee = poop.begin(); pee != poop.end(); pee++){
        if(pee -> second > highest){
            found_ya.clear();
            found_ya.push_back(pee -> first);
            highest = pee -> second;
        } else if (pee -> second == highest){
            found_ya.push_back(pee -> first);
        }
    }
    for(int i = 0; i < found_ya.size(); i++){
        std::cout << found_ya[i] << std::endl;
    }
}
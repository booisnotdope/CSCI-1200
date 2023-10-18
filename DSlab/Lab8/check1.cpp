#include <iostream>

int find_path(int x, int y){
    if (x == 0 || y == 0){
        return 1;
    }
    return find_path(x, y - 1) + find_path(x - 1, y);
}

int main(){
    std::cout << find_path(0, 0) << std::endl << find_path(2, 1)
    << std::endl << find_path(2, 2) << std::endl << find_path(16, 16) << std::endl;
    return 0;
}
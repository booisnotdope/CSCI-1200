#include <iostream>

int main(int argc, char* argv[]){
    
    int total = 1;
    for (int x = 1; x < argc; ++x){
        total *= atoi( argv[x]);

    }
    std::cout << "product of integers: " << total << std::endl;






    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//using namespace
using vecstr = std::vector<std::string>; using str = std::string;
using agrid = std::vector<std::vector<char>>;
using vecgrid = std::vector<std::vector<std::vector<char>>>;

//all functions used in this program
void errors(const int argv, char** &argc);
void reading_and_checker (char** &argc, int &rows, int &columns, 
                          vecstr &good_words, vecstr &bad_words);
vecgrid make_grids(const int rows, const int cols, 
                   vecstr &good_words, vecstr &bad_words);
bool in_bounds(agrid &grid, str word, const int d, const int x, const int y);
bool valid_letters(agrid &grid, str word, const int d, const int x, const int y);
void inserter(agrid &grid, const str &word, const int d, const int x, const int y);
std::vector<int> index_mover(agrid &grid, int d, int x, int y);
void make_a_grid(agrid &grid, const int rows, const int cols);
void clear_grid(agrid &grid);
void check_goodies(vecgrid &valid_grids, agrid grid, const vecstr &words, const int word_index,
                   const int dir, const int x, const int y);
// void check_baddies(vecgrid &valid_grids, vecstr &bad_words);
void print_grids(vecgrid &valid_grids);

//check for errors in the input files. then create rows, columns and a list of good
//words and bad words. recursively put the words in and check for bad words.
//print out the grids that make it through the checking
int main(int argv, char* argc[]){
    errors(argv, argc);
    int rows, columns;
    vecstr good_words, bad_words;
    reading_and_checker(argc, rows, columns, good_words, bad_words);
    vecgrid valid_grids = make_grids(rows, columns, good_words, bad_words);
    print_grids(valid_grids);
}

//check if there are 4 inputs. then check if the input and output text files 
//are correct. then check if the last argument is one_solution or all_solution
void errors(const int argv, char** &argc){
    if (argv < 4){
        std::cerr << "Not enough inputs" << std::endl;
        exit(1);
    } else if (argv > 4){
        std::cerr << "Too many inputs" << std::endl;
    }
    str solution = argc[3];
    if (solution != "one_solution" && solution != "all_solutions"){
        std::cerr << "Specify solution type" << std::endl;
        exit(1);
    }  
    std::ofstream out_str(argc[2]);
    if (!out_str.good()){
        std::cerr << "Can't open " << argc[2] << std::endl;
        exit(1);
    }
}

//given the input file, create a list of good and bad words
void reading_and_checker(char** &argc, int &rows, int &columns, 
                         vecstr &good_words, vecstr &bad_words){
    std::ifstream in_str(argc[1]);
    if (!in_str.good()){
        std::cerr << "Can't open " << argc[1] << std::endl;
        exit(1);
    }
    vecstr text;
    str temp;
    int counter = 0;
    while (in_str >> temp){
        if (counter == 0){
            columns = stoi(temp);
        } else if (counter == 1){
            rows = stoi(temp);
        } else {
            text.push_back(temp);
        }
        counter++;
    }
    for (unsigned int i = 0; i < text.size(); i++){
        if (text[i] == "+"){
            good_words.push_back(text[i + 1]);
        } else if (text[i] == "-"){
            bad_words.push_back(text[i + 1]);
        }
    }
}

//function is recursive. recusrively checks if the word can be placed at every place
//at every dirction. if it can place it. if it can't, move the word clockwise
//and then move it index. repeat until the word_index reaches the end or
//the x and y reach the end. then stop and based on which one comes first do 
//something with the grid
void check_goodies(vecgrid &valid_grids, agrid grid, const vecstr &words, const int word_index, 
                   const int d, const int x, const int y){
    int row_size = grid.size();
    // int col_size = grid[0].size();
    int word_size = words.size();
    if (word_index == word_size){
        // std::cout << "grid found" << std::endl;
        valid_grids.push_back(grid);
        return;// check_goodies(valid_grids, grid, words, word_index - 1, d + 1, x, y);
    }
    if (x >= row_size){
        return;
    }
    //if the word is not in bounds, then based on the direction and position, change it
    //to move to the next index.
    if (!in_bounds(grid, words[word_index], d, x, y)){   
        std::vector<int> new_index = index_mover(grid, d, x, y);
        return check_goodies(valid_grids, grid, words, word_index, 
                             new_index[0], new_index[1], new_index[2]); 
    }
    std::cout << "bounds are good " << x << ' ' << y << ' ' << d << std::endl;
    std::cout << words[word_index] << std::endl;
    //if the word is can not be put in, change the index based on its current direction
    //and position
    if (!valid_letters(grid, words[word_index], d, x, y)){
        std::vector<int> new_index = index_mover(grid, d, x, y);
        return check_goodies(valid_grids, grid, words, word_index, 
                             new_index[0], new_index[1], new_index[2]); 
    }
    std::cout << "letters are good " << x << ' ' << y << ' ' << d << std::endl;
    //at this point the word can be put in without problem switch based on direction to
    //place the word.
    inserter(grid, words[word_index], d, x, y);
    check_goodies(valid_grids, grid, words, word_index + 1, 0, 0, 0);
}

// void check_baddies(vecgrid &valid_grids, vecstr &bad_words){
//     //bruh
// }

//for every row and columns, call the check_goodies. When a grid is found, return
//and push back into the valid grids vector. then call the check_baddies
//where i check if an invalid word is present. if it is remove it from the vector
//return the valid grid
vecgrid make_grids(const int rows, const int cols,
                   vecstr &good_words, vecstr &bad_words){
    vecgrid valid_grids;
    agrid grid;
    make_a_grid(grid, rows, cols);
    for (int x = 0; x < rows; x++){
        for (int y = 0; y < cols; y++){
            // for (int d = 0; d < 8; d++){
            //     std::cout << in_bounds(grid, good_words[0], d, x, y) << std::endl;
            // }
            check_goodies(valid_grids, grid, good_words, 0, 0, x, y);
            valid_grids.push_back(grid);
            clear_grid(grid); 
        }
    }
    // check_baddies(valid_grids, bad_words);
    valid_grids.push_back(grid);
    return valid_grids;
}

//given a grid, word, direction, x and y, find if the word placed in the grid in that
//direction will fit. the switch statement switches based on the direction put in
//returns a bool
bool in_bounds(agrid &grid, str word, const int d, const int x, const int y){
    int posx = x + word.size();
    int negx = x - word.size();
    int posy = y + word.size();
    int negy = y - word.size();
    int row_size = grid.size();
    int col_size = grid[0].size();
    switch (d){
        case 0: return 0 <= negx && negx <= row_size;
        case 1: return (0 <= negx && negx <= row_size) && 
                        (0 <= posy && posy <= col_size);
        case 2: return 0 <= posy && posy <= col_size;
        case 3: return (0 <= posx && posx <= row_size) && 
                        (0 <= posy && posy <= col_size);
        case 4: return 0 <= posx && posx <= row_size;
        case 5: return (0 <= posx && posx <= row_size) && 
                        (0 <= negy && negy <= col_size);
        case 6: return 0 <= negy && negy <= col_size;
        case 7: return (0 <= negx && negx <= row_size) && 
                        (0 <= negy && negy <= col_size);
    }
}

//given a grid, word, direction, x, and y, see if the place where the word will go
//is a valid place to put. if it is a empty or same letter then return true.
//otherwise return false. returns a bool.
bool valid_letters(agrid &grid, str word, const int d, const int x, const int y){
    unsigned int counter = 0;
    for (unsigned int i = 0; i < word.size(); i++){
        switch (d){
            case 0: counter += (word[i] == grid[x - i][y] ||
                                    '.' == grid[x - i][y]); break;
            case 1: counter += (word[i] == grid[x - i][y + i] ||
                                    '.' == grid[x - i][y + i]); break;
            case 2: counter += (word[i] == grid[x][y + i] ||
                                    '.' == grid[x][y + i]); break;
            case 3: counter += (word[i] == grid[x + i][y + i] || 
                                    '.' == grid[x + i][y + i]); break;
            case 4: counter += (word[i] == grid[x + i][y] ||
                                    '.' == grid[x + i][y]); break;
            case 5: counter += (word[i] == grid[x + i][y - i] ||
                                    '.' == grid[x + i][y - i]); break;
            case 6: counter += (word[i] == grid[x][y - i] ||
                                    '.' == grid[x][y - i]); break;
            case 7: counter += (word[i] == grid[x - i][y - i] ||
                                    '.' == grid[x - i][y - i]); break;
        }
    }
    std::cout << counter << std::endl;
    return counter == word.size();
}

//based on a direction, change the chars in the grid to be the word
void inserter(agrid &grid, const str &word, const int d, const int x, const int y){
    for (unsigned int i = 0; i < word.size(); i++){
        switch (d){
            case 0: grid[x - i][y] = word[i]; std::cout << grid[x - i][y] << std::endl; break;
            case 1: grid[x - i][y + i] = word[i]; std::cout << grid[x - i][y + i] << std::endl; break;
            case 2: grid[x][y + i] = word[i];std::cout << grid[x][y + i] << std::endl; break;
            case 3: grid[x + i][y + i] = word[i]; std::cout << grid[x + i][y + i] << std::endl; break;
            case 4: grid[x][y + i] = word[i]; std::cout  << grid[x][y + i] << std::endl;break;
            case 5: grid[x + i][y - i] = word[i]; std::cout << grid[x + i][y + i] << std::endl; break;
            case 6: grid[x][y - i] = word[i]; std::cout << grid[x][y - i] << std::endl; break;
            case 7: grid[x - i][y - i] = word[i]; std::cout << grid[x - i][y - i] << std::endl; break;
        }
    }
}

//moves the index based on the direction and position. if the direction
//is at 8 or greater, change the y. if y is greater than the max, 
//change the x
std::vector<int> index_mover(agrid &grid, int d, int x, int y){
   std::vector<int> indexers;
   int col_size = grid[0].size();
    if (d >= 8){
        indexers.push_back(0);
        if (y >= col_size){
            indexers.push_back(x + 1);
            indexers.push_back(0);
        } else {
            indexers.push_back(x);
            indexers.push_back(y + 1);
        }
    } else {
        indexers.push_back(d + 1);
        indexers.push_back(x);
        indexers.push_back(y);
    }
    return indexers;
}

void make_a_grid(agrid &grid, const int rows, const int cols){
    for(int i = 0; i < rows; i++){
            std::vector<char> row;
            for(int j = 0; j < cols; j++){
                row.push_back('.');
            }
            grid.push_back(row);
        }
}

void clear_grid(agrid &grid){
    for (unsigned int i = 0; i < grid.size(); i++){
        for(unsigned int j = 0; j < grid[0].size(); j++){
            grid[i][j] = '.';
        }
    }
}

void print_grids(vecgrid &valid_grids){
    for(unsigned int i = 0; i < valid_grids.size(); i++){
        std::cout << "Board:" << std::endl;
        for(unsigned int x = 0; x < valid_grids[0].size(); x++){
            std::cout << "  ";
            for(unsigned int y = 0; y < valid_grids[0][0].size(); y++){
                std::cout << valid_grids[i][x][y];
            }
            std::cout << std::endl;
        }
    }
}
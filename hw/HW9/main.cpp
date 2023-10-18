#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Hash.h"

using str = std::string;
using uint = unsigned int;

//Forward decelrations
void cinning(str &genome, int &t_size, float &occupancy, int &kmer, str &query);
str txt_open(str& genome_txt);

int main(){
    str genome, query;
    int kmer, t_size = 100;
    float occupancy = 0.5;
    cinning(genome, t_size, occupancy, kmer, query);
}


//given inputs from the user, open the text file, set variables according 
//to what the user wants and find the genome that the user needs.
void cinning(str &genome, int &t_size, float &occupancy, int &kmer, str &query){
    str command;
    str value;
    str q_genome;
    
    //loops until query is inputed into the command
    while(true){
        std::cin >> command;
        if (command == "query") break;
        std::cin >> value;

        if (command == "genome"){
            genome = txt_open(value);
        }
        else if (command == "table_size"){
            t_size = stoi(value);
        } 
        else if (command == "occupancy"){
            occupancy = stof(value);
        } 
        else if (command == "kmer"){
            kmer = stoi(value);
            break;
        } 
    }

    //Hash table is created
    Hash hash_table(genome, t_size, occupancy, kmer);
    hash_table.insert();

    //loops until quit is put into the command
    while(true){
        std::cin >> command;
        if (command == "quit") break;
        std::cin >> value;
        std::cin >> q_genome;
        query = q_genome;
        std::cout << "Query: " << query << std::endl;
        hash_table.find(query, stoi(value));
    }
    
}

//check if the given text file can be opened and put the 
//contents into a string. return it
str txt_open(str& genome_txt){
    std::ifstream in_str(genome_txt);
    str genome = "";
    str temp;
    if (!in_str.good()){
        std::cerr << "Can't open " << genome_txt << std::endl;
        exit(1);
    }
    while(in_str >> temp){
        genome += temp;
    }
    return genome;
}
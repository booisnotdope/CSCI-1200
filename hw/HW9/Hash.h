#include <iostream>
#include <string>
#include <vector>

using str = std::string;
using uint = unsigned int;
using hash_tabler = std::vector<std::vector <std::pair<uint, str> > >;
using value = std::vector<std::pair<uint, str> >;
using pair = std::pair<uint, str>;

//PURPOSE: decleration and implementation of the hash table

class Hash{
    public:
    //CONSTRUCTOR
    Hash(str agenome, int at_size, float aoccupancy, int akmer) :
        genome(agenome), t_size(at_size), occupancy(aoccupancy), 
        kmer(akmer), size(0), hash_table(t_size){}

    //Accessors  

    /*take a kmer sized sub string of the genome and pass it through the
    hash function. then pass it through a probing function to make
    sure it can be inserted. make a pair of location and k_genome
    and push back into the hash map. if it grows too big resize
    by doubling and adding 1 to the size.*/
    void insert(){
        for(uint i = 0; i < genome.size(); i++){
            str k_genome = genome.substr(i, kmer);
            uint index = hash_function(k_genome) % t_size;
            index = quad_probing(index, k_genome);
            pair p;
            p.first = i; p.second = k_genome;
            hash_table[index].push_back(p);
            size++;
            if (size >= t_size*occupancy){
                resize();
            }
        }
    }

    /*given a query, take the first part of the query and try to find
    a match in the hash table. if there is a match, print out the
    position and number of mismatches. if there were no prints, 
    print out there were no matches.*/
    void find(const str &query, const int errors){
        str k_query = query.substr(0, kmer);
        uint index = hash_function(k_query) % t_size;
        index = quad_probing(index, k_query);

        //if the index returns an empty vector there are no matches
        if(hash_table[index].empty()){
            std::cout << "No Match\n";
            return;
        }
        value found = hash_table[index];
        
        //printing each position the query can appear
        bool printed = false;
        int count = 0;
        for(pair i: found){
            str genome_found = genome.substr(i.first, query.size());
            if(query.size() != genome_found.size()) continue;
            for(uint j = 0; j < genome_found.size(); j++){
                if(genome_found[j] != query[j]) count++;
            }
            if (count <= errors){
                std::cout << i.first << ' '
                          << count << ' '
                          << genome_found << std::endl;
                printed = true;
            }
            count = 0;
        }
        if (printed == false) std::cout << "No Match\n";
    }

    /*set a temp variable to the old hash and change the size of
    the hash. then place the contents of the old hash into the 
    new hash based on the hash function.*/
    void resize(){
        hash_tabler old_hash = hash_table;
        hash_table.clear();
        hash_table.resize(t_size * 2 + 1);
        t_size *= 2;
        t_size++;
        for(uint i = 0; i < old_hash.size(); i++){
            if (old_hash[i].empty()) continue;
            uint index = hash_function(old_hash[i][0].second) % t_size;
            index = quad_probing(index, old_hash[i][0].second);
            hash_table[index] = old_hash[i];
        }
    }

    private:
    //private variables
    str genome;
    int t_size;    
    const float occupancy;
    const int kmer;
    uint size;
    hash_tabler hash_table;

    /* HASH FUNCTION */
    uint hash_function(const str& key){
        uint hash = 258775219;
        for(unsigned int i = 0; i < key.length(); i++)
            hash ^= ((hash << 5) + key[i] + (hash >> 2));
        return hash;
    }

    //if the pair can't be placed it will quadratically increase the 
    //index of the new index until it can be placed into a new place
    uint quad_probing(uint index, str& string){
        if(hash_table[index].empty()) return index;
        if(hash_table[index][0].second == string) return index;

        int i = 1;
        uint new_index = (hash_function(string) + i*i) % t_size;
        while(hash_table[new_index].empty() || 
                hash_table[new_index][0].second == string){
            new_index = (hash_function(string) + i*i) % t_size;
            i++;
        }
        return new_index;
    }   
};
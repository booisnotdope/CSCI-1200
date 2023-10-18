#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <map>
#include <set>
#include "Fighter.h"

//Using namespace
using str = std::string;
using setstr = std::set<std::string>;
using fighter_map = std::map<str, Fighter>;
using frame_fighter = std::map<int, std::set<str> >;

//Changed the original array into a set
const setstr move_names = {"jab", "forward-tilt", "up-tilt", "down-tilt", 
							 "forward-smash", "up-smash", "down-smash"};

//all forward declerations
void errors(const int argc, char** &argv);
void reading_data(fighter_map &fighters, char* &data);
void reading_inputs(fighter_map &fighters, char* &inputs, char* &out);
int get_data(fighter_map &fighters, const str &arg1, const str &arg2);
frame_fighter get_names(fighter_map &fighters, 
									   const str &arg1);
int get_frame(fighter_map::iterator i, str move);

int main(int argc, char* argv[]){
	errors(argc, argv);
	fighter_map fighters;

	reading_data(fighters, argv[1]);
	
	reading_inputs(fighters, argv[2], argv[3]);
	return 0;
}

//Checks for errors in the files
void errors(const int argc, char** &argv){
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		exit(1);
	}

	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
		exit(1);
	}

	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
		exit(1);
	}

	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
		exit(1);
	}
}

//reads the data into a map
void reading_data(fighter_map &fighters, char* &data){
	std::ifstream in_str(data);
	str name, jab, ftilt, utilt, dtilt, fsmash, usmash, dsmash;
	while (in_str >> name >> jab >> ftilt >> utilt >> 
		   dtilt >> fsmash >> usmash >> dsmash){

		//if this is the beginning of the text file, continue
		if (name == "character-name") continue;

		//add a pair of character name and fighting class into the nap
		fighters[name] = Fighter(stoi(jab), stoi(ftilt), stoi(utilt)
						, stoi(dtilt), stoi(fsmash), stoi(usmash), stoi(dsmash));
	}
}

//based on the inputs of what the user wants, print out the corrsponding data 
void reading_inputs(fighter_map &fighters, char* &input, char* &out){
	std::ifstream in_str(input);
	std::ofstream out_str(out);
	str action, arg1, arg2;
	while(in_str >> action >> arg1 >> arg2){

		//-q outputs a fighter's frame data based on its move. if the user 
		//wants all its moves it will do that too
		if (action == "-q"){

			//check if the user inputs a valid character name and move
			if (fighters.find(arg1) == fighters.end()){
				out_str << "Invalid character name: " << arg1 
						<< std::endl << std::endl;
				continue;
			}
			if (move_names.find(arg2) == move_names.end() && arg2 != "all"){
				out_str << "Invalid move name: " << arg2 
						<< std::endl << std::endl;
				continue;
			}

			//if the user request all the moves, it will loop through all the moves
			//of a fighter and output its frame data
			if (arg2 == "all"){
				for(str move_name: move_names){
					int frame = get_data(fighters, arg1, move_name);
					out_str << arg1 << ' ' << move_name << ": " << frame << std::endl;
				}
			} else{

				//just output the frame data for a specified character for a specific move
				int frame = get_data(fighters, arg1, arg2);
				out_str << arg1 << ' ' << arg2 << ": " << frame << std::endl;
			}
			out_str << std::endl;

		//-f, -s, and -d share a lot of the same code which is why they are chuncked
		//into one else statement.
		} else {

			//if the given name is not a valid move name, output an error message
			if(move_names.find(arg1) == move_names.end()){
				out_str << "Invalid move name: " << arg1 
						<< std::endl << std::endl;
				continue;
			}
			out_str << action << ' ' << arg1 << ' ' << arg2 << std::endl;

			//get a map based on frame data as the key and character names in a set
			//as values. the frame data is based on the given move
			frame_fighter  move_map = get_names(fighters, arg1);

			//depending on the action output different things.
			if (action == "-f"){

				//go through move_map and output the names of the fighters and the frame
				//data of the given move
				int j = 0;
				for(std::pair<int, std::set<str> > map_i: move_map){

					//make sure that you don't output more than the requested
					if(j >= stoi(arg2)){
						break;
					}
					for (str name: map_i.second){
						if(j >= stoi(arg2)){
							break;
						}
						out_str << name << ' ' << map_i.first << std::endl;
						j++;
					}
				}

			//if the action is -s then just do what -f did but in reverse. 
			} else if (action == "-s"){
				frame_fighter::reverse_iterator i = move_map.rbegin();
				int j = 0;
				for(; i != move_map.rend(); i++){

					//make sure you don't output more than the requested
					if(j >= stoi(arg2)){
						break;
					}
					for(str name: i -> second){
						if (j >= stoi(arg2)){
							break;
						}
						out_str << name << ' ' << i -> first << std::endl;
						j++;
					}
				}
				
			//if the action is -d, just find the frame data in move_set and output
			//all the names of the fighters
			} else {
				if(move_map.find(stoi(arg2)) == move_map.end()){
				continue;
				}
				for(str name: move_map.find(stoi(arg2)) -> second){
					out_str << name << std::endl;
				}
			}
			out_str << std::endl;
		}
	}
}

//given a map of fighters, a name and a move, find the fighters in the map and then
//find the given frame data for that move. return that number
int get_data(fighter_map &fighters, const str &arg1, const str &arg2){
	int frame = get_frame(fighters.find(arg1), arg2);
	return frame;
}

//given a map of fighters and a move, go through all the fighters and put the 
//a pair of frame data and set of fighter names into frame_fighter.
//return that map
frame_fighter get_names(fighter_map &fighters, const str &arg1){
	frame_fighter move_map;
	fighter_map::iterator i = fighters.begin();
	for (; i != fighters.end(); i++){
		move_map[get_frame(i, arg1)].insert(i -> first);
	}
	return move_map;
}

//given an iterator and a move, return a int frame data.
int get_frame(fighter_map::iterator i, str move){
	if (move == "jab"){
		return i -> second.get_jab();
	} else if (move == "forward-tilt"){
		return i -> second.get_ftilt();
	} else if (move == "up-tilt"){
		return i -> second.get_utilt();
	} else if (move == "down-tilt"){
		return i -> second.get_dtilt();
	} else if (move == "forward-smash"){
		return i -> second.get_fsmash();
	} else if (move == "up-smash"){
		return i -> second.get_usmash();
	} else{
		return i -> second.get_dsmash();
	}
}
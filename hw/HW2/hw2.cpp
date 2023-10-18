#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "team.h"
#include "player.h"

/* PURPOSE:
Parses through text give from the user and parses throught the text. Based on the type of statistic
the user wants, it will write out the data into a text file. The data will be formated into 
neat columns.
*/

//This function checks if there are the right amount of inputs and if the data type is a valid one
void errors(std::vector<std::string> inputs){
  int input_size = inputs.size();
  if (input_size < 3) {
    std::cerr << "Not enough inputs" << std::endl;
    exit(1);
  } else if (input_size > 3) {
    std::cerr << "Too many inputs" << std::endl;
    exit(1);
  }
  std::string data_type = inputs[2];
  if (data_type != "--team_stats" && data_type != "--player_stats" && data_type != "--custom_stats"){
    std::cerr << data_type << " is not a valid data type" << std::endl;
    exit(1);
  }
}

//Parses through the text and checks for key words such as "goal" and "penalty". 
//Then the word that came before will be a valid team.
//If the team already exist im the teams vector then it will be skipped and the return will be 
//a set of all Team classes.
std::vector<Team> get_teams(const std::vector<std::string>& text){
  int text_size = text.size();
  std::vector<std::string> teams;
  for (int i = 0; i < text_size; i++){
    if (text[i] == "goal" || text[i] == "penalty"){
      int exist = std::count(teams.begin(), teams.end(), text[i-1]);
      if (exist == 0){        
        teams.push_back(text[i-1]);
      }
    }
  }
  int team_size = teams.size();
  std::vector<Team> team_classes;
  for (int i = 0; i < team_size; i++){
    team_classes.push_back(Team(teams[i]));
  }
  return team_classes;
}

//This fuction parses through the text a second time to get the information it need to output goals and such
//It will look for keywords such as "goal", "penalty", and "FINAL" to gather information it needs.
//It will return a vector of Team classes with the added information.
std::vector<Team> team_info(const std::vector<std::string>& text){
  std::vector<Team> teams = get_teams(text);
  int text_size = text.size();
  int team_size = teams.size();
  for (int i = 0; i < text_size; i++){
    if (text[i] == "goal"){
      for (int j = 0; j < team_size; j++){
        if (text[i-1] == teams[j].getname()){
          teams[j].addgoals();
          break;
        }
      }
    } else if (text[i] == "penalty"){
      for (int j = 0; j < team_size; j++){
        if (text[i-1] == teams[j].getname()){
          teams[j].addpenalities();
          break;
        }
      }
    } else if (text[i] == "FINAL"){
      std::string team1 = text[i+1], team2 = text[i+3];
      int score1 = stoi(text[i+2]), score2 = stoi(text[i+4]);
      if (score1 > score2){
        for (int j = 0; j < team_size; j++){
          if (team1 == teams[j].getname()){
            teams[j].addwins();
          }
          if (team2 == teams[j].getname()){
            teams[j].addlosses();
          }
        }
      } else if (score1 == score2){
        for (int j = 0; j < team_size; j++){
          if (team1 == teams[j].getname() || team2 == teams[j].getname()){
            teams[j].addties();
          }
        }        
      } else {
        for (int j = 0; j < team_size; j++){
          if (team1 == teams[j].getname()){
            teams[j].addlosses();
          }
          if (team2 == teams[j].getname()){
            teams[j].addwins();
          }
        }
      }
    }
  }
  sort(teams.begin(), teams.end(), better);
  return teams;
}

//Parses through the text to find all players. It will look for keywords such as "penalty", "goal", and "(". 
//the information it will push into the vector if the player name and the school they went to. 
//if the player already exist in the vector, the player is skipped. 
//returns a vector of Player classes.
std::vector<Player> get_players(const std::vector<std::string>& text){
  std::vector<std::string> player_school;
  int text_size = text.size();
  for (int i = 0; i < text_size; i++){
    if (text[i] == "penalty"){
      std::string school = text[i-1];
      std::string player = text[i+1];  
      if (player == "BENCH"){
        continue;
      }    
      int exist = std::count(player_school.begin(), player_school.end(), text[i+1]);
      if (exist == 0){        
        player_school.push_back(player);
        player_school.push_back(school);
      }
    } else if (text[i] == "goal"){
      std::string school = text[i-1];
      std::vector<std::string> goal_players;
      goal_players.push_back(text[i+1]);
      i+=2;
      while (text[i] != ")"){
        i++;
        if (text[i] == ")"){      
          continue;
        }
        goal_players.push_back(text[i]);
      }
      int goal_players_size = goal_players.size();
      for (int i = 0; i < goal_players_size; i++){
        int exist = std::count(player_school.begin(), player_school.end(), goal_players[i]);
        if (exist == 0){
          player_school.push_back(goal_players[i]);
          player_school.push_back(school);
        }
      }
    }
  }
  int number_players = player_school.size();
  std::vector<Player> player_classes;
  for (int i = 0; i < number_players; i += 2){
    player_classes.push_back(Player(player_school[i], player_school[i + 1]));
  }
  return player_classes;
}

//Parses through the text again and adds information for each player. It looks for keywords such as 
//"goal", "penalty", "(", and ")" to add goals, penalties and assists. At the end, it sorts the fucntion 
//with the stronger function in my player's class. It returns a vector of player classes.
std::vector<Player> player_info(const std::vector<std::string>& text){
  std::vector<Player> players = get_players(text);
  int player_size = players.size();
  int text_size = text.size();
  for (int i = 0; i < text_size; i++){
    if (text[i] == "penalty"){
      for (int j = 0; j < player_size; j++){
        if (players[j].getplayer() == text[i+1]){
          players[j].addpenalities();
          break;
        }
      }
    } else if (text[i] == "goal"){
      for (int j = 0; j < player_size; j++){
        if (players[j].getplayer() == text[i+1]){
          players[j].addgoals();
          break;
        }
      }
    } else if (text[i] == "("){
      while (text[i] != ")"){
        i++;
        for (int j = 0; j < player_size; j++){
          if (players[j].getplayer() == text[i]){
            players[j].addassists();
            break;
          }          
        }
      }
    }
  }
  sort(players.begin(), players.end(), stronger);
  return players;
}

//after sorting the players based on goals and assists, look at every player's school. the first 4
//players with different schools are their team mvps. Returns a vector of Player classes.
std::vector<Player> star_player(const int& team_size, const std::vector<Player>& players){
  int player_size = players.size();
  std::vector<Player> mvp;
  int mvp_size = 0;
  for (int i = 0; i < player_size; i++){
    if (mvp_size >= team_size){
      break;
    }
    if(i==0){
      mvp.push_back(players[i]);
      mvp_size++;
      continue;
    }
    for (int j = 0; j < mvp_size; j++){
      if (mvp[j].getteam() == players[i].getteam()){
        break;
      } else if (mvp[j].getteam() != players[i].getteam() && j + 1 == mvp_size){
        mvp.push_back(players[i]);
        mvp_size++;
      } 
    }
  }
  return mvp;
}

//for every Team object, compare the names and find the longest one. If there is one that longer than
//"Team Name", then the longest word will be that name otherwise, the longest name is "Team Name"
std::string longest_team_word(std::vector<Team> teams){
  std::string longest = "Team Name";
  int team_size = teams.size();
  for (int i = 0; i < team_size; i++){
    if (longest.length() < teams[i].getname().length()){
      longest = teams[i].getname();
    }
  }
  return longest;
}

//loops through all the players and finds the longest player name and school name. otherwise
//the default will be "Player Name " and "Team".
std::vector<std::string> longest_player_word(std::vector<Player> players){
  std::vector<std::string> long_words;
  std::string longest_player = "Player Name";
  std::string longest_team = "Team";
  int number_players = players.size();
  for (int i = 0; i < number_players; i++){
    if (longest_player.length() < players[i].getplayer().length()){
      longest_player = players[i].getplayer();
    }
    if (longest_team.length() < players[i].getteam().length()){
      longest_team = players[i].getteam();
    }
  }
  long_words.push_back(longest_player);
  long_words.push_back(longest_team);
  return long_words;
}

//based on the longest team name, output data into a neat table. Then for each team
//print out their stats.
void print_teams(std::vector<Team> teams, std::ostream& out_str){
  int longest_team = longest_team_word(teams).length();
  int team_size = teams.size();  
  out_str << "Team Name" << std::setw(longest_team - 4) 
          << 'W' << std::setw(4) << 'L' << std::setw(4) 
          << 'T' << std::setw(7) << "Win%" << std::setw(7) 
          << "Goals" << std::setw(11) << "Penalties" << std::endl;
  for (int i = 0; i < team_size; i++){
      int spaces = longest_team - teams[i].getname().length() + 5;
      out_str << teams[i].getname() << std::setw(spaces) 
              << teams[i].getwins() << std::setw(4) 
              << teams[i].getlosses() << std::setw(4) 
              << teams[i].getties() << std::setw(7) << std::setprecision(2) << std::fixed
              << teams[i].get_win_percent() << std::setw(7) 
              << teams[i].getgoals() << std::setw(11) 
              << teams[i].getpenalities() << std::endl;
  }
}

//based on the longest player name and longest team name, print out a neat table with data.
//for every player, print out their team, goals, assists and penalties.
void print_players(std::vector<Player> player, std::string word, std::ostream& out_str){
  std::vector<std::string> long_words = longest_player_word(player);
    int name_length = long_words[0].length();
    int team_length = long_words[1].length();
    int number_players = player.size();    
    out_str << word << std::setw(name_length - 5) 
            << "Team" << std::setw(team_length + 5) 
            << "Goals" << std::setw(11) 
            << "Assists" << std::setw(12) 
            << "Penalties" << std::endl;
  for (int i = 0; i < number_players; i++){
      std::string player_name = player[i].getplayer();
      std::string team_name = player[i].getteam();
      int player_spaces = name_length - player_name.length() + 2 + team_name.length();
      int team_spaces = team_length - team_name.length() + 9;
      out_str << player_name << std::setw(player_spaces) 
              << team_name << std::setw(team_spaces) 
              << player[i].getgoals() << std::setw(11) 
              << player[i].getassists() << std::setw(12) 
              << player[i].getpenalities() << std::endl;
  }
}

int main(int argv, char* argc[]){
  std::vector<std::string> inputs;
  for (int i = 1; i < argv; i++){
    inputs.push_back(argc[i]);
  }
  errors(inputs);
  std::string data_type = argc[3];

  //checks if a read file exist and if a write file exist.
  std::ifstream in_str(argc[1]);
    if (!in_str.good()) {
      std::cerr << "Can't open " << argc[1] << " to read.\n";
      exit(1);
  }
  std::ofstream out_str(argc[2]);
    if (!out_str.good()) {
        std::cerr << "Can't open " << argc[2] << " to write.\n";
        exit(1);
    }

  std::vector<std::string> text;
  std::string temp;
  while (in_str >> temp){
    text.push_back(temp);
  }
  std::vector<Team> team_classes = team_info(text);  
  std::vector<Player> Player_classes = player_info(text);  

  //depending on the data type the user wants output certain data.
  if (data_type == "--team_stats"){
    print_teams(team_classes, out_str);
  } else if (data_type == "--player_stats"){
    print_players(Player_classes, "Player Name", out_str);
  } else {
    int team_size = team_classes.size();
    std::vector<Player> mvp = star_player(team_size, Player_classes);
    print_players(mvp, "Star Player", out_str);
  }
  return 0;
}
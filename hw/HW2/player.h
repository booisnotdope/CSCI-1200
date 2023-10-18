#include <string>
#include <fstream>

//PURPPOSE: header for player class
class Player{
    public:
    Player(std::string player, std::string team);

    //Accessors
    std::string getplayer() const;
    std::string getteam() const;
    int getgoals() const;
    int getassists() const;
    int getpenalities() const;

    //Modifiers
    void addgoals(int i = 1);
    void addassists(int i = 1);
    void addpenalities(int i = 1);
    
    private:
    //Representation
    std::string player;
    std::string team;
    int goals;
    int assists;
    int penalities;
};

//function compares 2 player's goals and assists, then least penalities, then alphabetically
bool stronger(const Player &player1, const Player &player2);
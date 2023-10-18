#include <string>
#include <fstream>

// PURPOSE: header for the team class
class Team{
    public:
    Team(std::string name);

    //Accessors
    std::string getname() const;
    int getwins() const;
    int getlosses() const;
    int getties() const;
    double get_win_percent() const;
    int getgoals() const;
    int getpenalities() const;

    //Modifiers
    void addwins(int i = 1);
    void addlosses(int i = 1);
    void addties(int i = 1);
    void win_percent();
    void addgoals(int i = 1);
    void addpenalities(int i = 1);
    
    private:
    //Representation
    std::string name;
    int wins;
    int losses;
    int ties;
    int goals;
    int penalities;

};

//fucntion used to sort teams based on win%, goals then alphabetically.
bool better(const Team &team1, const Team &team2);
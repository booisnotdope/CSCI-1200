#include <string>

class Animal {
public:
  Animal();
  Animal(std::string name);

  const std::string name;
  double weight;
  bool on_land;
  bool in_water;
  bool meat;
  bool veggies;

  void setweight(double weight);
  void setland(bool on_land);
  void setwater(bool in_water);
  void setmeat(bool meat);
  void setveggies(bool veggies);

  bool is_amph() const;
  bool is_ovm() const;

private:
};

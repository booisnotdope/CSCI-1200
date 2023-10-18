#include <vector>

//Purpose: Include functions that we aren't allowed to add to traincar.h

//Required Functions
float AverageDistanceToDiningCar(TrainCar* &train);
int ClosestEngineToSleeperCar(TrainCar* &train);
void PushBack(TrainCar* &train, TrainCar* car);
void DeleteAllCars(TrainCar* &train);
std::vector<TrainCar*> ShipFreight(TrainCar* &engines, TrainCar* &freights, const int min_speed, const int max_cars);
void TotalWeightAndCountCars(TrainCar* train, int &weight, int &engines, int &freight, 
                            int &passenger, int &dining, int &sleeping);

float CalculateSpeed(TrainCar* train);
void Separate(TrainCar* &train1, TrainCar* &train2, TrainCar* &train3);

//Helper function
void train_linker(TrainCar* &train1, TrainCar* &train2);

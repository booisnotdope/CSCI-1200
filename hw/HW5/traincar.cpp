#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "traincar.h"

//Purpose: Implementation of the functions mentioned in traincar_prototypes.h

//Helper Function
//The purpose of this function is to add a car from train2 to the front of train1.
//The different if and else if are the different test cases that can happen.
void train_linker(TrainCar* &train1, TrainCar* &train2){
    TrainCar* temp = NULL;
    TrainCar* temp2 = NULL;
    //If train2 is NULL, don't do anything
    if (train2 == NULL){
        return;
    }
    //If there is just one car in train2, just add it to the front of train1.
    //depending on what train1 is.
    if (train2 -> prev == NULL && train2 -> next == NULL){
        if (train1 == NULL){
            train1 = train2;
            train2 = NULL;
        } else {
            temp = train2;
            temp -> next = train1;
            train1 -> prev = temp;
            train1 = temp;
            train2 = NULL;
        }
        return;
    //If the car passed through is at the front of the list, take it off
    //and put it in the front of train1. remember to switch the train1
    //pointer when changing the start of train1.
    } else if (train2 -> prev == NULL){
        temp = train2;
        train2 = train2 -> next;
        temp -> next = NULL;
        temp -> prev = NULL;
        train2 -> prev = NULL;
    //if the car passed through is at the end of the list.
    //remember to change the pointer when changing the start of train1.
    } else if (train2 -> next == NULL) {
        temp = train2;
        train2 = train2 -> prev;
        temp -> next = NULL;
        temp -> prev = NULL;
        train2 -> next = NULL;
    //if the car passed through is in the middle of the list, set 2 temp
    //pointers. have those 2 temp pointers set to each other and then take
    //the car out. remember to change the pointer when changing the start
    //of train1.
    } else {
        temp = train2;
        temp2 = train2 -> prev;
        train2 = train2 -> next;
        train2 -> prev = temp2;
        temp2 -> next = train2;
        temp -> next = NULL;
        temp -> prev = NULL;
    }
    //Adding the car we took out to train1. if train1 is NULL, set the 
    //car we took out to train1
    if (train1 == NULL){
        train1 = temp;
    } else {
    //otherwise just set the front of train1 to temp and change the pointer.
        train1 -> prev = temp;
        temp -> next = train1;
        train1 = temp;
    }
}

//This function calculates the average distance from a passenger car to their
//closest dining car. 
//function is O(n) n being the train size.
float AverageDistanceToDiningCar(TrainCar* &train){
    float total_distance = 0;
    float distance = 0;
    float cars = 0;
    float temp_counter = 0;
    TrainCar* temp = train;
    while (temp -> next != NULL){
        //edge case where temp is passenger car. keep looping until we hit a 
        //dining car. depenging on the cars we pass along the way, either
        //add mroe distance or return -1 as we have a passenger that can't 
        //go to a dining car
        if (temp -> isPassengerCar()){
            cars++;
            distance++;
            while(!temp -> isDiningCar() && temp -> next != NULL){
                temp = temp -> next;
                if (temp -> isPassengerCar()){
                    temp_counter++;
                    cars++;
                } else if (temp -> isEngine() || temp -> isFreightCar()){
                    return -1;
                }
                distance += temp_counter;
            }
            total_distance += distance;
            distance = 0;
            temp_counter = 0;
        } else if (temp -> isDiningCar()) {
        //if temp is a dining car, loop until we hit a engine or freight car.
        //add distance based on what we pass through
            while (!temp -> isEngine() && !temp -> isFreightCar()){               
                if (temp -> next == NULL){
                    break;
                }
                temp = temp -> next;
                distance++;
                if (temp -> isPassengerCar()){
                    total_distance += distance;
                    cars++;
                }
            }
            distance = 0;
        } else {
            temp = temp -> next;
        }
    }      
    return total_distance / cars;
}

//calculates the closest distance between a sleeping car and an engine to
//minimuze noise. similar logic to the function on top
//the function is O(n) n being the train size
int ClosestEngineToSleeperCar(TrainCar* &train){
    int distance = 99999;
    int car = 0;
    TrainCar* temp = train;
    while (temp -> next != NULL){
        //if temp is an engine, loop until we see a sleeping car or we reach
        //the end of the list. calculate the distance
        if(temp -> isEngine()){
            while(!temp -> isSleepingCar() && temp -> next != NULL){
                if (temp -> isEngine()){
                    car = 0;
                }
                temp = temp -> next;
                car++;
            }
            if (car < distance){
                distance = car;
            }
            car = 0;
        } else if (temp -> isSleepingCar()){
            //if temp is a sleeping car loop until we see a engine or the end
            //of the list.
            while(!temp -> isEngine() && temp -> next != NULL){
                if (temp -> isSleepingCar()){
                    car = 0;
                }
                temp = temp -> next;
                car++;
            }
            if(car < distance){
                distance = car;
            }
            car = 0;
        } else {
        temp = temp -> next;
        }
    }
    return distance;
}

//takes a car and loops the temp variable until we reach the end of the train.
//set the end of the train to the new car and the car's front to the end of train.
//this function is O(n) n being the train size.
void PushBack(TrainCar* &train, TrainCar* car){
    if (train == NULL){
        train = car;
    } else {
        TrainCar* temp = train;
        while (temp -> next != NULL){
            temp = temp -> next;
        }
        temp -> next = car;
        temp -> next -> prev = temp;
    }
}

//go through the entire trian and as we go along delete the prev.
//at the end delete train.
//this function is O(n) n being the trian size.
void DeleteAllCars(TrainCar* &train){
    if (train != NULL){
        TrainCar* temp = train;
        while (temp -> next != NULL){
            temp = temp -> next;
            delete temp -> prev;
        }   
        delete temp;
        train = NULL;
    }
}

//max_weight is calculated by the min_speed passed through.
//most of this function is described in the README. 
//the function is O(f * (f||e)) f being freight size and e being engine size.
//whether f or e is bigger will determine the O notation
std::vector<TrainCar*> ShipFreight(TrainCar* &engines, TrainCar* &freights, const int min_speed, const int max_cars){
    float max_weight = (9.375 * 3000) / min_speed;
    std::vector<TrainCar*> valid_trains;
    TrainCar* train = NULL;
    TrainCar* train_engine = NULL;
    TrainCar* train_freight = NULL;
    float weight = 150;
    float cars = 1;
    //if engines or freights is NULL, dont do anything.
    if (engines == NULL || freights == NULL || max_cars <= 0){
        return valid_trains;
    }
    while (engines != NULL && freights != NULL){
        train_linker(train_engine, engines);
        while(cars < max_cars && freights != NULL){
            if(weight + freights -> getWeight() < max_weight){
                weight += freights -> getWeight();
                train_linker(train_freight, freights);
                cars++;
                continue;
            } else if (weight + freights -> getWeight() >= max_weight){
                    if (cars * 2 <= max_cars && engines != NULL){
                        train_linker(train_engine, engines);
                        weight = weight - max_weight + 150;
                        cars++;       
                    } else {
                        break;
                    }
                
            } else {
                break;
            }
        }
        PushBack(train, train_engine);
        PushBack(train, train_freight);
        valid_trains.push_back(train);
        train = NULL;
        train_engine = NULL;
        train_freight = NULL;
        cars = 1;
        weight = 150;
    }
    return valid_trains;
}

//loops through the trian and counts the number of trains, weight, engines,
//passenger cars, diningcars, sleeping cars, and freights.
//function is O(n) n being the train size.
void TotalWeightAndCountCars(TrainCar* train, int &weight, int &engines, int &freight, 
                            int &passenger, int &dining, int &sleeping){
    weight = 0; engines = 0; freight = 0; passenger = 0; dining = 0; sleeping = 0;
    TrainCar* temp = train;
    while (temp -> next != NULL){
        weight += temp -> getWeight();
        if (temp -> isEngine() == true){
            engines++;
        } else if (temp -> isFreightCar() == true){
            freight++;
        } else if (temp -> isPassengerCar() == true){
            passenger++;
        } else if (temp -> isDiningCar() == true){
            dining++;
        } else {
            sleeping++;
        }
        temp = temp -> next;
    }
    weight += temp -> getWeight();
        if (temp -> isEngine() == true){
            engines++;
        } else if (temp -> isFreightCar() == true){
            freight++;
        } else if (temp -> isPassengerCar() == true){
            passenger++;
        } else if (temp -> isDiningCar() == true){
            dining++;
        } else {
            sleeping++;
        }

}
//calcualtes the speed based on the information passed in through
//TotalWeightAndCountCars. 
//function is O(n) n being the trian size.
float CalculateSpeed(TrainCar* train){
    int weight, engines, freight, passenger, dining, sleeping;
    TotalWeightAndCountCars(train, weight, engines, freight, passenger, dining, sleeping);
    unsigned long horsepower = engines * 3000;
    return (horsepower * 550 * 3600) / ((20 / 0.01) * 0.02 * 5280 * weight);    
}

//seperates a train into 2 sp their speeds match while using the least amount
//of swaps. I took out all the engines and split the rest into based on the nubmer
//of engies. distribute the engines accodingly. 
//this function is O(s) + O(s) + O(e) s being the train size and e being engine nubmers.
void Separate(TrainCar* &train1, TrainCar* &train2, TrainCar* &train3){
    TrainCar* engines = NULL;
    TrainCar* others = NULL;
    train2 = NULL;
    train3 = NULL;
    float engine_num = 0;
    float other_num = 0;
    while(train1 != NULL){
        if(train1 -> isEngine()){
            train_linker(engines, train1);
            engine_num++;
        } else {
            train_linker(others, train1);
            other_num++;
        }
    }
    int halver_engine = engine_num / 2;
    int halver_other = halver_engine * other_num / engine_num;
    float counting = 0;
    while(counting < halver_engine){
        train_linker(train3, engines);
        counting++;
    }
    counting = 0;
    while(counting < halver_other){
        train_linker(train3, others);
        counting++;
    }    
    while (engines != NULL){
        train_linker(train2, engines);
    }    
    while (others != NULL){
        train_linker(train2, others);
    }
}
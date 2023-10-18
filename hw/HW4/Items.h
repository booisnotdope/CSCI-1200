#ifndef __ITEMS_H__
#define __ITEMS_H__
#include <iostream>
#include <string>
#include <list>

#include "Customers.h"

//PURPOSE: Deceleration of the item class

using str = std::string;
using uint = unsigned int;
using custlist = std::list<Customers>;

class Items{
    public:
    //Constructor
    Items(str id, uint quantity, str name);

    //Accessors
    str get_id() const {return id;}
    uint get_quantity() const {return quantity;}
    str get_name() const {return name;}
    custlist get_renting() const {return renting;}
    custlist get_pending() const {return pending;}
    
    //Adders
    void quantity_change(int adder);

    //Sorter
    custlist::iterator sort_cust(custlist &cust, str id);

    //Public Varibales
    custlist all;
    custlist renting;
    custlist pending;

    private:
    str id;
    uint quantity;
    str name;
};

//printing function
std::ostream& operator<< (std::ostream &out, Items &item);
#endif
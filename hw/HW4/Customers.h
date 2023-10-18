#ifndef __CUSTOMERS_H__
#define __CUSTOMERS_H__
#include <iostream>
#include <string>
#include <list>

//PURPOSE: Deceleration of the Customer class

using str = std::string;
using uint = unsigned int;

class Customers{
    public:
    //Constructors
    Customers(str cust_id, str action, uint quantity, str item_id, str name);

    //Accessors
    str get_cust() const {return cust_id;}
    str get_action() const {return action;}
    uint get_quantity() const {return quantity;}
    str get_item() const {return item_id;}
    str get_name() const {return name;}

    //Public Variables
    str action;

    private:
    str cust_id;
    uint quantity;
    str item_id;
    str name;
};
//printing function
std::ostream &operator<< (std::ostream &out, const Customers &cust);
#endif
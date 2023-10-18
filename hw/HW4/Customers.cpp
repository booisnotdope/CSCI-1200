#include <iostream>
#include <string>
#include <iomanip>
#include <list>

#include "Customers.h"

//PURPOSE: Implementaion of the Customer class

using str = std::string;
using uint = unsigned int;

//Constructor
Customers::Customers(str acust_id, str aaction, uint aquantity, str aitem_id, str aname){
    cust_id = acust_id;
    action = aaction;
    quantity = aquantity;
    item_id = aitem_id;
    name = aname;
}

// printing function 
std::ostream &operator<< (std::ostream &out, const Customers &cust){
    out << cust.get_cust() << ' ' << cust.get_name() << std::endl;
    if (cust.get_action() == "rent"){
        out << "Rentals: ";
    } else if (cust.get_action() == "pending"){
        out << "Pending: ";
    }
    out << cust.get_item() << " (" << cust.get_quantity() << ") ";
    return out;
}

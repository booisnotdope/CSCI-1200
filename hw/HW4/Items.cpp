#include <iostream>
#include <string>
#include <iomanip>
#include <list>

#include "Items.h"

//PURPOSE: Implementation of the items class

using str = std::string;
using uint = unsigned int;
using custlist = std::list<Customers>;

//Constructor
Items::Items(str aid, uint aquantity, str aname){
    id = aid;
    quantity = aquantity;
    name = aname;
    renting = {};
    pending = {};
    all = {};
}

//Changes the quantity based on what is passed through
void Items::quantity_change(int adder){
    quantity += adder;
}

//sorts the customers in a customer list
custlist::iterator Items::sort_cust(custlist &cust, str id){
    custlist::iterator i;
    for(i = cust.begin(); i != cust.end(); ++i){
        if(i -> get_cust() > id){
            break;
        }
    }
    return i;
}

//print out item. if there is rental customers, print those out.
//if there are pending customers, print those out.
std::ostream& operator<< (std::ostream &out, Items &item){
    out << item.get_id() << ' ' << item.get_quantity() 
        << " available " << item.get_name() << std::endl;
    //sorts then prints
    if(item.get_renting().size() != 0){
        custlist renting = item.get_renting();
        custlist renting_sort;
        custlist::iterator i;
        custlist::iterator j;
        for(i = renting.begin(); i != renting.end(); ++i){
            j = item.sort_cust(renting_sort, (*i).get_cust());
            renting_sort.insert(j, (*i));
        }
        out << "Rental Customers: ";
        for(i = renting_sort.begin(); i != renting_sort.end(); ++i){
            Customers temp = (*i);
            out << temp.get_cust() << ' ' << temp.get_name() 
                << " (" << temp.get_quantity() << ") ";
        }
        out << std::endl;
    }
    //sorts then prints
    if(item.get_pending().size() != 0){
        custlist pent = item.get_pending();
        custlist pent_sort;
        custlist::iterator k;
        custlist::iterator l;
        for(l = pent.begin(); l != pent.end(); ++l){
            k = item.sort_cust(pent_sort, (*l).get_cust());
            pent_sort.insert(k, (*l));
        }
        out << "Pending Customers: ";
        for(k = pent.begin(); k != pent.end(); ++k){
            Customers tempp = (*k);
            out << tempp.get_cust() << ' ' << tempp.get_name() 
                << " (" << tempp.get_quantity() << ") ";
        }
        out << std::endl;
    }
    return out;
}
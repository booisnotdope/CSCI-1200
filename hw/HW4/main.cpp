#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <list>

#include "Customers.h"
#include "Items.h"

/* PURPOSE: Given customers and items, have customers rent and return items
based on what they ask for. If there are errors in the renting and returning
process, print out a error message.
*/

//Shorthand to make code eaiser to read
using strlist = std::list<std::string>; using itemlist = std::list<Items>;
using custlist = std::list<Customers>; using str = std::string;
using uint = unsigned int; using std::stoi; using std::next;

//All the functions used in this program
void errors(const int argv, char** &argc);
strlist text_create(char* &txt);
itemlist::iterator sort_item(itemlist &item, str id);
custlist::iterator sort_cust(custlist &cust, str id);
itemlist item_create(char* &txt);
custlist customer_create(char* &txt);
void doing(itemlist &item, custlist &cust, custlist &remain);
void print(std::ofstream &item_out, std::ofstream &cust_out, itemlist &item, custlist &remain);

int main(int argv, char* argc[]){
    errors(argv, argc);
    std::ofstream item_out(argc[3]);
    std::ofstream cust_out(argc[4]);

    itemlist item_classes = item_create(argc[1]);
    custlist cust_classes = customer_create(argc[2]);
    custlist remaining_cust;
    
    doing(item_classes, cust_classes, remaining_cust);
    print(item_out, cust_out, item_classes, remaining_cust);

    return 0; 
}

//Checks if the files are valid
void errors(const int argv, char** &argc){
    if (argv < 5){
        std::cerr << "Too little inputs" << std::endl;
        exit(1);
    } else if(argv > 5){
        std::cerr << "Too many inputs" << std::endl;
        exit(1);
    }
    std::ofstream items_out(argc[3]);
    std::ofstream customers_out(argc[4]);
    if (!items_out.good()){
        std::cerr << "Can't open" << argc[3] << std::endl;
        exit(1);
    }
    if (!customers_out.good()){
        std::cerr << "Can't open" << argc[4] << std::endl;
        exit(1);
    }
}

//Parses through a text file and sees if it is good. If it is put it
//into a list and return it.
strlist text_create(char* &txt){
    std::ifstream in_str(txt);
    if (!in_str.good()){
        std::cerr << "Can't open" << txt << std::endl;
        exit(1);
    }
    strlist text;
    str temp;
    while(in_str >> temp){
        text.push_back(temp);
    }
    return text;
}

//Function to sort items based on their id numerically
//returns an iterator
itemlist::iterator sort_item(itemlist &item, str id){
    itemlist::iterator i;
    for (i = item.begin(); i != item.end(); ++i){
        if(i -> get_id() > id){
            break;
        }
    }
    return i;
}

//Function to sort customers based on their id numerically
//returns an iterator
custlist::iterator sort_cust(custlist &cust, str id){
    custlist::iterator i;
    for(i = cust.begin(); i != cust.end(); ++i){
        if(i -> get_cust() > id){
            break;
        }
    }
    return i;
}

//using the list created in the text create, create items.
//sorts the items by id. returns a list of item classes.
itemlist item_create(char* &txt){
    strlist item_list = text_create(txt);
    strlist::iterator i;
    itemlist item_classes;
    itemlist::iterator j;
    for(i = item_list.begin(); std::distance(i, item_list.end()) > 0; std::advance(i, 3)){
        str id = *i;
        j = sort_item(item_classes, id);
        if (id[0] == 'T' && id.size() == 5 && stoi(*next(i)) != 0){
            item_classes.insert(j, Items(id, stoi(*next(i)), *next(i, 2)));
        } else {
            std::cerr << "Invalid inventory ID " << id <<
                " found in the inventory file." << std::endl;
        }
    }
    return item_classes;
}

//using the list created in the text create, create customers
//sorts the customers by time. returns a list of customers
custlist customer_create(char* &txt){
    strlist cust_list = text_create(txt);
    strlist::iterator i;
    custlist cust_classes;
    for(i = cust_list.begin(); std::distance(i, cust_list.end()) > 0; std::advance(i, 6)){
        str cust_id = *i;
        str item_id = *next(i, 4);
        cust_classes.push_back(Customers(cust_id, *next(i), stoi(*next(i, 3)), 
                                         item_id, *next(i, 5)));
    }
    return cust_classes;
}

//takes in request from customers and changes item quantites
void doing(itemlist &item, custlist &cust, custlist &remain){
    custlist::iterator i; itemlist::iterator j;
    custlist::iterator k; custlist::iterator l;
    //for each customer and each item
    for(i = cust.begin(); i != cust.end(); ++i){
        for(j = item.begin(); j != item.end(); ++j){
            //If the customer's id doesn't start with a C, print an error message
            if (i -> get_cust()[0] != 'C'){
                std::cerr << "Invalid customer information found for ID " <<
                i -> get_cust() << " in the customer file." << std::endl;
                break;
            }
            //if the item's id doesnt match with the customer's item, continue
            if (i -> get_item() !=  j -> get_id()){
                //if the j iterator has reached the end of the list, print out
                //an error message based on whether its renting or returning
                if (next(j) == item.end()){
                    if (i -> get_action() == "rent"){
                        std::cerr << "Customer " << i -> get_cust() << 
                        " requested item " << i -> get_item() << 
                        " which is not in the inventory." << std::endl;
                    } else if (i -> get_action() == "return"){
                        std::cerr << "Customer " << i -> get_cust() << 
                        " attempted to return item " << i -> get_item() << 
                        " which is not in the inventory." << std::endl;
                    }
                }
                continue;
            }
            //if it has passed all the contitions, ask if it is renting or returning
            //if it is renting, check if there is enough quantity.
            //if there is then push them into the renting list. otherwise push them into
            //the pending list         
            if( i -> get_action() == "rent"){
                if (j -> get_quantity() >= i -> get_quantity()){
                    j -> renting.push_back((*i));
                    j -> quantity_change(-i -> get_quantity());
                } else {
                    j -> pending.push_back((*i));
                }
            } 
            //if they are returning 
            else if(i -> get_action() == "return") {
                int counter = 0;
                //loop through the renting list. if the renter is the same as
                //the returner, this means they are a valid renter. otherwise
                //they have returned something they don't have and print an error message
                l = j -> renting.begin();
                while (l != j -> renting.end()){
                    if(l -> get_cust() == i -> get_cust()){                        
                        j -> quantity_change(i -> get_quantity());
                        l = j -> renting.erase(l);
                        break;
                    } else {
                        if (next(l) == j -> renting.end()){
                            std::cerr << "Customer " << i -> get_cust() << " attempted to return item " 
                            << i -> get_item() << " which she/he did not rent." << std::endl;
                            counter++;
                            break;
                        }
                    }
                    ++l;
                }
                //if they have returned properly, go through the pending list and ask who want the
                //extra quantity. 
                k = j -> pending.begin();
                while (k != j -> pending.end() && counter != 1){
                    if (j -> get_quantity() >= k -> get_quantity()){
                        j -> renting.push_back((*k));
                        j -> quantity_change(-k -> get_quantity());
                        k = j -> pending.erase(k);
                    } else {
                        ++k;
                    }
                }
            }
            break;
        }
    }
    //puts both the renting and pending list into remain for each item
    //as they are put into the list, sort them
    for(j = item.begin(); j != item.end(); ++j){
        for(k = j -> renting.begin(); k != j -> renting.end(); ++k){
            i = sort_cust(remain, k -> get_cust());
            remain.insert(i, *k);
        }
        for(l = j -> pending.begin(); l != j -> pending.end(); ++l){
            i = sort_cust(remain, l -> get_cust());
            l -> action = "pending";
            remain.insert(i, *l);
        }
    }
}

//prints the items and customers into their respective files.
void print(std::ofstream &item_out, std::ofstream &cust_out, itemlist &item, custlist &remain){
    itemlist::iterator i;
    for (i = item.begin(); i != item.end(); ++i){
        item_out << (*i) << std::endl;
    }
    custlist::iterator j; custlist::iterator k;
    for(j = remain.begin(); j != remain.end(); ++j){
        if (j != remain.begin()){
            k = std::prev(j);
            if (k -> get_cust() == j -> get_cust()){
                cust_out << j -> get_item() << " (" << j -> get_quantity() << ") ";
                continue;
            } else {
                cust_out << std::endl << std::endl;
            }
        }
        cust_out << (*j);
    }
    cust_out << std::endl << std::endl; 
}
HOMEWORK 4: TOOL RENTAL LISTS


Ryan So


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

https://www.geeksforgeeks.org/list-cpp-stl/

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >



ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.


i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file:
O(i^2) 
parses through all the items but as it parses through,
it goes through all the already sorted items to insert

Rental event:
O(i * c)
goes through all the items and customers to see which 
items are valid 

Return event - no pending customer(s):
O(i * c * r)
goes through all the items and customers. goes through all
the renting customers and removes them. then goes through all
the pending customers and checks if there are customers that 
want the item. if not, nothing happens

Return event - with pending customer(s):
O(i * c * r) + O(p)
similar to the no pending customers but if there are customers
that want the item, give it to them. p is refering to total 
pending customers

Entire program:
O(e) + O(i^2) + O(c) + O(i^2) + O(c^2) + O(i) + O(c)
the largest O notation plus reading the text files, sorting
the items and customers, and printing the sorted lists.

MISC. COMMENTS TO GRADER:
(optional, please be concise!)


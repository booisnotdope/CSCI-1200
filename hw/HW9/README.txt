HOMEWORK 9: MINIBLAST


NAME:  Ryan So


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Hash function was taken from lab 11
Mirand Zheng

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10


HASH FUNCTION DESCRIPTION

the hash funciton was taken from the lab 11. the only thing changed
was the intial hash number.



HASH TABLE IMPLEMENTATION

much of the resize was taken from the lab 11 header

insert goes through the entire genome and inserts it into 
the hash table.

find uses the hash function and finds its position in the 
hash table. then it loops through the duplicates.

The basis of the structure is a vector of vector of pairs

ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?

O(L - k) the memory taken is the entire genome.

What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

Command genome
O(L)

Command table_size
O(1)

Command occupancy
O(1)

Command kmer
O(1)

Command query
O(q * p) uses the find function

Command quit
O(1)

Performance of insert
O(L) but insert inserts all the genomes at the same time.
If insert inserted 1 value at a time, it would insert in O(1)

Performace of find
O(q * p) however find accounts for printing and comparations of
the genome and query. If find were to return a vector of pairs,
find would be O(1)

Performace of resize
O(L - k). The number of keys is based on the genome. 


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)



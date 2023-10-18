HOMEWORK 3: MATRIX CLASS


NAME:  Ryan So


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Nick Wang

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  12



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get
O(1)

set
O(1)

num_rows
O(1)

get_column
O(rows)

operator<<
O(rows * columns)

quarter
O(new_row * new_col)

operator==
O(row1 * col1)

operator!=
O(row1 * col1)

swap_rows
O(columns)

rref (provided in matrix_main.cpp)
O(row^2 * columns)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

Looking at the error messages Valgrind gave helped me pinpoint 
which lines are not allocating memory correctly. I also used the lab
memory debugger to help me see what lines of code are giving me 
errors.


EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.

The resize function is very similar to how I did the transpose function.
I first create a matrix of row, col, and a fill. I fill the matrix with
the fill variable. Then I delete my old matrix and set the new one to be 
the old one.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


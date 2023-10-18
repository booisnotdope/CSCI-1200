HOMEWORK 9: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  Ryan So


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

priority queue constructor was taken from the lab 11
percolate_up and percolate_down were taken from the lab 11
Raymond Chen, Miranda Zheng, Brian Wang Chen

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  13



NAIVE ALGORITHM:

Order Notation:

O((w * h)^2)

Timing Experiment Data:

Tiny_5x5: Real: 0m 0.061s | user: 0m 0s | sys: 0m 0.011s
small_10x10: Real: 0m 0.065s | user: 0m 0s | sys: 0m 0.009s
squiggle_30x30: Real: 0m 0.063s | user: 0m 0.014s | sys: 0m 0.007s
lines_100x100: Real: 0m 1.024s | user: 0m 0.832s | sys: 0m 0.027s
data_structures_300x300: Real: 1m39.689s | user: 1m 39.549s | sys: 0m 0.02s


Discussion:
It is O((w * h)^2) because it has to go through the entire picture
for each pixel in the picture. 



IMPROVED ALGORITHM:

Order Notation:

2O(w * h)

Timing Experiment Data:

tiny_5x5: Real: 0m 0.066s | user: 0m 0.0s | sys: 0m 0.02s
small_10x10: Real: 0m 0.055s | user: 0m 0.006s | sys: 0.005s
squiggle_30x30: Real: 0m 0.0103s | user: 0m 0.001s | sys: 0m 0.009s
lines_100x100: Real: 0m 0.117s | user: 0m 0.056s | sys: 0m 0.008s
data_structures_300x300: Real: 0m 13.623s | user: 0m 12.396s | sys: 0m 0.028s

Discussion:
It goes through the entire picture once to find all the black pixels. 
then it goes through the entire picture and compares it to the black pixels


FAST MARCHING METHOD (with a map):

Order Notation:

O(w * h) + O(8 * w * h)

Timing Experiment Data:

tiny_5x5: Real: 0m 0.07s | user 0m 0s | sys: 0m 0.031s (seg fault)
small_10x10: Real 0m 0.57s | 0m 0.008s | sys: 0m 0.0103s
squiggle_30x30: Real 0m 0.064s | 0m 0.006s | sys: 0m 0.012s
lines_100x100: Real 0m 0.116s | 0m 0.11s | sys: 0m 0.001s

Discussion:
goes through the entire photo to find the black pixels. then
goes through each black pixel and finds its neighbors. repeats until 
all pixels are touched.


DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!







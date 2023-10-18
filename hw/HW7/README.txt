HOMEWORK 7: SUPER SMASH BROS. FRAMES


NAME:  Ryan So


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Raymond Chen
https://cplusplus.com/reference/set/set/
https://cplusplus.com/reference/map/map/?kw=map

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity for both running
time AND space along with a short justification for each of the queries below.
For the commands, do not count the space occupied by the database in the space
complexity analysis.

f: The total number of fighters
m: The number of different moves
t: The highest number of moves that have the same starting frame for a particular move

reading the database/populating your initial data structure:
Time Complexity: O(f * log(f))
Space Complexity: O(f)

-q (specific move):
Time complexity: O(2 * log(f)) + O(log(m))
Space Complexity: O(1)

-q (all):
Time complexity: O(m * log(f)) + O(log(f)) + O(log(m))
Space Complexity: O(1)

-f:
Time complexity: O(log(m)) + O(f * log(t)) + O(f)
Space Complexity: O(t)

-s:
Time complexity: O(log(m)) + O(f * log(t)) + O(f)
Space Complexity: O(t)

-d:
Time complexity: O(log(m)) + O(f * log(t)) + O(log(t)) + O(t)
Space Complexity: O(t)


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)







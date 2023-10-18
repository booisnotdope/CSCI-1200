HOMEWORK 5: LINKED TRAIN CARS


NAME:  Ryan So


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Miranda Zheng, Raymond Chen

https://www.geeksforgeeks.org/data-structures/linked-list/

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30



DESCRIPTION OF IMPROVED SHIPFREIGHT ALGORITHM FOR EXTRA CREDIT 
Aiming for optimal (fastest train speed, most freight, fewest number
of engines used, and fewest resulting trains) for any input.  Note:
Student choice on how to prioritze between these goals.  Describe your
priorization and your implementation.

Priorization: Most freight, fewest number of engines and fewest resulting trains

I had a weight counter that calculated the maximum weight an engine can hold 
based on the minimum speed. I would add freights to a freight variable and
if the freights' weight exceeded the maximum weight, I would stop the loop.
But if the number of cars including the engine were less than half of the maximum
cars allowed, it meant another train with about the same size and weight could
be added before it dips past the maximum car. at this point, either the maximum
cars would be reached or the weight has exceeded the limit again. This would 
keep looping until one the guards is staisfied. I pushback the train and start anew.


DESCRIPTION OF IMPROVED SEPARATE ALGORITHM FOR EXTRA CREDIT 
Aiming for optimally comfortable trains (smaller values for average
distance to dining and/or larger values for closest engine to sleeper)
and/or optimally handling cases with > 2 engines.  Student choice on how 
to prioritze between these goals.  Describe your priorization and your
implementation.


MISC. COMMENTS TO GRADER:  
Optional, please be concise!



without changing anything, when compiling there is 1 error and 3 warnings. the error
the error is: redefinition of 'class point' point.h:8:7
the 3 warnings are: statement has no effect. line.cpp:25:14
                    control reaches end of non-void function line.cpp:40:1
                    unused variable point.cpp:23:10


I added #include <algorithm> into the roads.cpp and in the line.cpp I commented out #include <point.h>
I did that because I already used #include <point.h> in the line.h so I don't need to inlcude it into the 
line.cpp.

When I compiled I also used -Wall -Wextra to get all the warnings. When I did this, there are 5 warnings and 0 errors
Warning 1: reference to local variable roads.cpp:18:10
Warning 2: comparsion of interger expressions of different signedness roads.cpp:32:21
Warning 3: statement has no effect line.cpp:25:14
Warning 4: control reaches end of non-void function line.cpp:40:1
Warning 5: unused variable point.cpp:23:10

How I plan to fix them: 
Fix 1: delete the '&' at the top of the fuction
Fix 2: Set roads.size() to another int variable and when comparing in the for loop set roads.size() to the variable you just set.
Fix 3: gradient *= -1
Fix 4: Both if statements might not be seen so to fix that change the second if to an else.
Fix 5: The variable answer was never used so to fix that return answer.


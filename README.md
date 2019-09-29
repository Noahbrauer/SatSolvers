# SatSolvers
**First! You need to initially use make on the command line. This is compiled with optimization O3, but you can type make O2 and make O1 to optimize lower.
After that you can run it by the command ./SATAlg "filename" where filename is equations. Once started the program will ask you to choose from one of 3 SAT algorithms to test. 

*The first being DPLL which will print the output only once since it is complete.
*The second being GSAT which will initially ask you for the number of tries and flips to attempt inside the algorithm. It will test 5 times using these inputs and each time output the sat and fitness.
*The last being walkSAT which will be very similar to GSAT but indie the algorithm it uses randomness instead of optimization.

-readSATFile-
This file contains a class readsatfile thats fairly self explanatory. When called the file reads in cnf files and creates a vector<vector<int>> of the clauses and literals. It also holds the values of nvbar and nbclause.

-DPLL-
For implementing this algorithm I followed the technique learned in class. I first check for the formula to be a set of literals, if so I return true. I next check for empty clauses, and if found I return false. Next, I propogate for every unit clause and propogate for pure literals. I finally return either the function with the new changes or the function with the new changes after the negative value is propogated.

-GSAT-
I first start a loop for the number of tries. Then I create a randomly generated truth assignment for which I check for satisfiability. If this assignment proves true, I return it. If it doesnt I continue my flip loop. In this I find the make and break values from flipping all variables. From those I take the best version and continue the flip loop with that new formula.

-walkSAT-
I first start a loop for the number of tries. Then I create a randomly generated truth assignment for which I check for satisfiability. If this assignment proves true, I return it. If it doesnt I continue my flip loop. In this I find a random untried variable and try that. I create the new formula and use that on the next iteration of the loop. 

*********************************
-Learning Outcome-
From this project I have learned to implement SAT algorithms on cnf the cnf files given. In particular, I have gained experience with DPLL, GSAT, and walkSAT. I can use this newfound knowledge on any search algorithms or SAT algorithms I attempt in the future. 
*********************************

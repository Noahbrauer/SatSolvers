#include <iostream>
#include <string>
#include <ctype.h>
#include <iomanip>
#include "DPLL.h"
#include "GSAT.h"
#include "walkSAT.h"

using namespace std;


int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	//char fileName[] = "uf20-0156.cnf";
	readSATFile file;
	Clauses clauses;
	int ALG = -1;
	int fitness = 0;
	while (ALG != 0) {
		while (true) {
			cout << "Please enter ALG number\n1. DPLL\n2. GSAT\n3. walkSAT\n";
			cin >> ALG;
			if (ALG != 1 || ALG != 2 || ALG != 3) break;
			cout << "Invalid input... Please enter 1, 2, 3, or 0 to exit.\n";
			cout << ALG << '\n';
		}
		if (ALG == 1) {
			fitness = 0;
			clauses = file.getClauses(fileName);
			cout << "Number of Variables:\t" << file.nbvar << "\nNumber of Clauses:\t" << file.nbclause << '\n';
			DPLL solver1;
			//Run algorithm
			int ans = solver1.DPLLalg(clauses, fitness);
			if (ans == 0) {
				cout << "Unsatisfiable\n";
				Clauses::iterator it = clauses.begin();
				for (; it < clauses.end() - 1; ++it) {
					clauses.pop_back();
				}
				cout << "Fitness was: " << fitness << "\n";
			}
			else {
				cout << "Satisfiable\n";
				Clauses::iterator it = clauses.begin();
				for (; it < clauses.end() - 1; ++it) {
					clauses.pop_back();
				}
				cout << "Fitness was: " << fitness << "\n";
			}
		}
		else if (ALG == 2) {
			//Ask for tries and flips
			int maxtry, maxflip;
			cout << "Enter number of tries: \n";
			cin >> maxtry;
			cout << "Enter number of flips: \n";
			cin >> maxflip;
			for (int n = 0; n < 10; n++) {
				fitness = 0;
				clauses = file.getClauses(fileName);
				cout << "Number of Variables:\t" << file.nbvar << "\nNumber of Clauses:\t" << file.nbclause << '\n';
				GSAT solver2;
				vector<int> setVars;
				//Run algorithm
				int ans = solver2.GSATalg(clauses, fitness, file.nbvar, maxtry, maxflip, setVars);
				if (ans == 0) {
					cout << "Unsatisfiable\n";
					Clauses::iterator it = clauses.begin();
					for (; it < clauses.end() - 1; ++it) {
						clauses.pop_back();
					}
					cout << "Fitness was: " << fitness << "\n";
				}
				else {
					cout << "Satisfiable\n";
					Clauses::iterator it = clauses.begin();
					for (; it < clauses.end() - 1; ++it) {
						clauses.pop_back();
					}
					cout << "Fitness was: " << fitness << "\n";
				}
			}
		}
		else if (ALG == 3) {//Similar to GSAT but with random selection instead of optimal. Mostly same code
			int maxtry, maxflip;
			cout << "Enter number of tries: \n";
			cin >> maxtry;
			cout << "Enter number of flips: \n";
			cin >> maxflip;
			for (int n = 0; n < 10; n++) {
				fitness = 0;
				clauses = file.getClauses(fileName);
				cout << "Number of Variables:\t" << file.nbvar << "\nNumber of Clauses:\t" << file.nbclause << '\n';
				walkSAT solver2;
				vector<int> setVars;
				int ans = solver2.walkSATalg(clauses, fitness, file.nbvar, maxtry, maxflip, setVars);
				if (ans == 0) {
					cout << "Unsatisfiable\n";
					Clauses::iterator it = clauses.begin();
					for (; it < clauses.end() - 1; ++it) {
						clauses.pop_back();
					}
					cout << "Fitness was: " << fitness << "\n";
				}
				else {
					cout << "Satisfiable\n";
					Clauses::iterator it = clauses.begin();
					for (; it < clauses.end() - 1; ++it) {
						clauses.pop_back();
					}
					cout << "Fitness was: " << fitness << "\n";
				}
			}
		}
	}
	//system("PAUSE");
}

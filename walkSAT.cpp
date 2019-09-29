#include "walkSAT.h"

//Checking satisfiability of the formula
int walkSAT::checkSAT(Clauses walkSATcopy, int& fitness) {
	int retVal = 1;
	int tempfit = 0;

	Clauses::iterator it = walkSATcopy.begin();
	for (; it < walkSATcopy.end(); ++it) {
		int temp = 0;
		int soize = it->size();
		for (int i = 0; i < soize; i++) {
			temp = temp || (*it)[i];
		}
		if (temp == 1) tempfit++;
		retVal = retVal && temp;
	}
	if (tempfit > fitness) fitness = tempfit;
	return retVal;
}

//Changing value in formula to the opposite
void walkSAT::changeval(Clauses& walkSATcopy, bool boolean, int val) {
	Clauses::iterator it = walkSATcopy.begin();
	for (; it < walkSATcopy.end(); ++it) {
		int soize = it->size();
		for (int i = 0; i < soize; i++) {
			if ((*it)[i] == val) {
				(*it)[i] = boolean;
			}
			if ((*it)[i] == -val) {
				(*it)[i] = !boolean;
			}
		}
	}
}

//Generate the copied vector with boolean values instead
void walkSAT::genVar(Clauses& walkSATcopy, int nbvar, vector<int>& setVars) {
	srand(time(0));
	for (int i = 1; i <= nbvar; i++) {
		int randVar = rand() % 10;
		if (randVar > 5) {
			changeval(walkSATcopy, true, i);
			setVars.push_back(true);
			//cout << i << ' ' << true << '\n';
		}
		if (randVar <= 5) {
			changeval(walkSATcopy, false, i);
			setVars.push_back(false);
			//cout << i << ' ' << false << '\n';
		}
	}
}

//Algorithm for walksat
int walkSAT::walkSATalg(Clauses clauses, int& fitness, int nbvar, int  maxtry, int maxflip, vector<int>& setVars) {
	Clauses walkSATcopy = clauses;
	//Create unused variables vector
	//Start test
	for (int i = 0; i < maxtry; i++) {
		//Create random generated truth assignment
		genVar(walkSATcopy, nbvar, setVars);
		vector<int> untestedLiterals(nbvar);
		iota(begin(untestedLiterals), end(untestedLiterals), 1);
		for (int j = 0; j < maxflip; j++) {
			if (checkSAT(walkSATcopy, fitness)) return 1;
			srand(time(0));
			//Find random value to flip
			int randi = rand() % untestedLiterals.size();
			int randp = untestedLiterals[randi];
			untestedLiterals.erase(untestedLiterals.begin()+randi);

			//Alter temporary clauses to new
			Clauses::iterator it = clauses.begin();
			Clauses::iterator in = walkSATcopy.begin();
			for (; it < clauses.end(); it++, in++) {
				int soize = it->size();
				for (int i = 0; i < soize; i++) {
					if ((*it)[i] == randp) {
						(*in)[i] = !((*in)[i]);
					}
					if ((*in)[i] == -randp) {
						(*in)[i] = !((*in)[i]);
					}
				}
			}
		}
	}
	return 0;
}
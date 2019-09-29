#include "GSAT.h"

//Checking satisfiability of the formula
int GSAT::checkSAT(Clauses gsatcopy, int& fitness) {
	int retVal = 1;
	int tempfit=0;

	Clauses::iterator it = gsatcopy.begin();
	for (; it < gsatcopy.end(); ++it) {
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

//Function for finding clauses satisfied by change
int GSAT::Make(Clauses clauses, Clauses gsatcopy, int val) {
	int retVal = 0;
	int unSats = 0;
	int Sats = 0;
	int AunSats = 0;
	int ASats = 0;

	Clauses::iterator ik = gsatcopy.begin();
	for (; ik < gsatcopy.end(); ik++) {
		int temp = 0;
		int soize = ik->size();
		for (int i = 0; i < soize; i++) {
			temp = temp || (*ik)[i];
		}
		if (temp == 0) {
			unSats++;
		}
		else Sats++;
	}

	Clauses::iterator it = clauses.begin();
	Clauses::iterator in = gsatcopy.begin();
	for (; it < clauses.end(); it++, in++) {
		int soize = it->size();
		for (int i = 0; i < soize; i++) {
			if ((*it)[i] == val) {
				(*in)[i] = !((*in)[i]);
			}
			if ((*it)[i] == -val) {
				(*in)[i] = !((*in)[i]);
			}
		}
	}

	in = gsatcopy.begin();
	for (; in < gsatcopy.end(); in++) {
		int temp = 0;
		int soize = in->size();
		for (int i = 0; i < soize; i++) {
			temp = temp || (*in)[i];
		}
		if (temp == 0) {
			AunSats++;
		}
		else ASats++;
	}

	retVal = ASats - Sats;
	if (retVal < 0) return 0;
	return retVal;
}

//Function for finding clauses unsatisfied by change
int GSAT::Break(Clauses clauses, Clauses gsatcopy, int val) {
	int retVal = 0;
	int unSats = 0;
	int Sats = 0;
	int AunSats = 0;
	int ASats = 0;

	Clauses::iterator ik = gsatcopy.begin();
	for (; ik < gsatcopy.end(); ik++) {
		int temp = 0;
		int soize = ik->size();
		for (int i = 0; i < soize; i++) {
			temp = temp || (*ik)[i];
		}
		if (temp == 0) {
			unSats++;
		}
		else Sats++;
	}

	Clauses::iterator it = clauses.begin();
	Clauses::iterator in = gsatcopy.begin();
	for (; it < clauses.end(); it++, in++) {
		int soize = it->size();
		for (int i = 0; i < soize; i++) {
			if ((*it)[i] == val) {
				(*in)[i] = !((*in)[i]);
			}
			if ((*it)[i] == -val) {
				(*in)[i] = !((*in)[i]);
			}
		}
	}

	in = gsatcopy.begin();
	for (; in < gsatcopy.end(); in++) {
		int temp = 0;
		int soize = in->size();
		for (int i = 0; i < soize; i++) {
			temp = temp || (*in)[i];
		}
		if (temp == 0) {
			AunSats++;
		}
		else ASats++;
	}

	retVal = AunSats - unSats;
	if (retVal < 0) return 0;
	return retVal;
}

//Changing value in formula to the opposite
void GSAT::changeval(Clauses& gsatcopy, bool boolean, int val) {
	Clauses::iterator it = gsatcopy.begin();
	for (; it < gsatcopy.end(); ++it) {
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
void GSAT::genVar(Clauses& gsatcopy, int nbvar, vector<int>& setVars) {
	srand(time(0));
	for (int i = 1; i <= nbvar; i++) {
		int randVar = rand() % 10;
		if (randVar > 5) {
			changeval(gsatcopy, true, i);
			setVars.push_back(true);
			//cout << i << ' ' << true << '\n';
		}
		if (randVar <= 5) {
			changeval( gsatcopy, false, i);
			setVars.push_back(false);
			//cout << i << ' ' << false << '\n';
		}
	}
}

//Algorithm for GSAT
int GSAT::GSATalg(Clauses clauses, int& fitness, int nbvar, int  maxtry, int maxflip, vector<int>& setVars) {
	Clauses GSATcopy = clauses;
	for (int i = 0; i < maxtry; i++) {
		genVar(GSATcopy, nbvar, setVars);
		for (int j = 0; j < maxflip; j++) {
			vector<int> diff;
			vector<int> greatdiff;
			int greatestDiff = 0;
			if (checkSAT(GSATcopy, fitness)) return 1;
			//Start heuristic to find optimal change
			for (int k = 1; k < nbvar; k++) {
				int make = Make(clauses, GSATcopy, k);
				int broken = Break(clauses, GSATcopy, k);
				diff.push_back(make - broken);
				if (greatestDiff < diff[k-1]) greatestDiff = diff[k-1];
			}
			int soize = diff.size();
			for (int d = 0; d < soize; d++) {
				if (diff[d] == greatestDiff) greatdiff.push_back(d);
			}
			//Find random of best vars
			srand(time(0));
			int randi = rand() % greatdiff.size();
			int randp = diff[greatdiff[randi]];

			//Alter temporary clauses to new
			Clauses::iterator it = clauses.begin();
			Clauses::iterator in = GSATcopy.begin();
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
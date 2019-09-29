#pragma once
#include <random>
#include <ctime>
#include <list>
#include "readSATFile.h"


class GSAT {
public:

	int checkSAT(Clauses clauses, int& fitness);
	int Make(Clauses clauses, Clauses gsatcopy, int val);
	int Break(Clauses clauses, Clauses gsatcopy, int val);
	void changeval(Clauses & gsatcopy, bool boolean, int val);
	void genVar(Clauses& gsatcopy, int nbvar, vector<int>& setVars);
	int GSATalg(Clauses clauses, int& fitness, int nbvar, int maxtry, int maxflip, vector<int>& setVars);
};

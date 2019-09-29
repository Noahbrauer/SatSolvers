#pragma once
#include <random>
#include <ctime>
#include <list>
#include "readSATFile.h"


class walkSAT {
public:
	
	int checkSAT(Clauses clauses, int& fitness);
	void changeval(Clauses & gsatcopy, bool boolean, int val);
	void genVar(Clauses& gsatcopy, int nbvar, vector<int>& setVars);
	int walkSATalg(Clauses clauses, int& fitness, int nbvar, int maxtry, int maxflip, vector<int>& setVars);
};

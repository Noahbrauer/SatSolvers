#include "DPLL.h"

//Function for simplifying the clauses after after setting var to true
Clauses DPLL::unitPropagation(Clauses clauses, int lit, int& fitness) {
	int fittest = 0;
	int literalOps = -(lit);
	int soize = clauses.size();
	int soize2;
	for (int i = 0; i < soize; i++) {
		soize2 = clauses[i].size();
		for (int j = 0; j < soize2; j++) {
			if (clauses[i][j] == literalOps) {
				clauses[i].erase(clauses[i].begin() + j);
				soize2--;
			}
		}
	}

	soize = clauses.size();
	for (int i = 0; i < soize; i++) {
		soize2 = clauses[i].size();
		for (int j = 0; j < soize2; j++) {
			if (clauses[i][j] == lit) {
				clauses.erase(clauses.begin() + i);
				soize--;
				fittest++;
				break;
			}
		}
	}
	if (fittest > fitness) fitness = fittest;
	return clauses;
};

//Algorithm for dpll
int DPLL::DPLLalg(Clauses clauses, int& fitness)
{
	if (clauses.size() == 0) {
		return true;
	}
	int soize = clauses.size();
	for (int i = 0; i < soize; i++) {
		if (clauses[i].size() == 0) {
			return false;
		}
	}
	for (int i = 0; i < soize; i++) {
		if (clauses[i].size() == 1) {
			return DPLLalg(unitPropagation(clauses, clauses[i][0], fitness), fitness);
		}
	}

	int variable = clauses[0][0];
	if (DPLLalg(unitPropagation(clauses, variable, fitness), fitness)) {
		return true;
	}
	else {
		return DPLLalg(unitPropagation(clauses, -(variable), fitness), fitness);
	}
}

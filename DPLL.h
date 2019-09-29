#pragma once
#include "readSATFile.h"


class DPLL {
public:

	Clauses unitPropagation(Clauses clauses, int lit, int& fitness);
	int DPLLalg(Clauses clauses, int& fitness);
};

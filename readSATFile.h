#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>

using namespace std;
typedef std::vector<std::vector<int> > Clauses;

class readSATFile {
public:
	Clauses getClauses(char* fileName);
	int nbvar;
	int nbclause;
};
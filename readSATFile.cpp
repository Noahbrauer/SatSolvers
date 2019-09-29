#include "readSATFile.h"

using namespace std;

Clauses readSATFile::getClauses(char * fileName) {
	ifstream filein;
	string line;
	filein.open(fileName);
	Clauses clauses;

	if (filein.is_open()) {
		while (getline(filein, line)) {
			if (line[0] == 'c') continue;
			else {
				stringstream ss(line);
				vector<string> results((istream_iterator<string>(ss)), istream_iterator<string>());
				
				if (line[0] == '%') break;
				else if (line[0] == 'p') {
					nbvar = stoi(results[2]);
					nbclause = stoi(results[3]);
				}
				else {
					vector<int> clause;
					int size = results.size();
					for (int i = 0; i < size; i++) {
						if (stoi(results[i]) != 0) {
							clause.push_back(stoi(results[i]));
						}
					}
					clauses.push_back(clause);
				}
			}
		}
		filein.close();
	}
	return clauses;
}

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "StaticHash.h"
using namespace std;

class Parsing {
public:
	Parsing();
	~Parsing() {}
	
	void ParsingMegares(const string &filename, StaticHash &sh);
	void ParsingFASTQ(const string &filename, StaticHash &sh, const bool& reportMultipleHits, const bool& classifyReads);
	//void setFile(string filename);
	

	
};
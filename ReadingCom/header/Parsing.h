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
	
	void ParsingMegares(string filename, StaticHash &sh);
	void ParsingFASTQ(string filename, StaticHash &sh, bool& reportMultipleHits, bool& classiftReads);
	//void setFile(string filename);
	bool sortByVal(const pair<string, int>& a,
		const pair<string, int>& b)
	{
		return (a.second < b.second);
	}
	
	
};
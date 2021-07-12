#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Parsing {
public:
	Parsing();
	Parsing(string id, string seq, string fuc);
	void ParsingMegares(string filename);
	void ParsingFASTQ(string filename);
	void setFile(string filename);

public:
	string mid;
	string mseq;
	//string mfuc;
};
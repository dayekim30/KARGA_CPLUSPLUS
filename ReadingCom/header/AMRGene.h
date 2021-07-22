#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class AMRGene {

public:
	AMRGene();
	~AMRGene() {
	delete kmerStrand,
	kmerFreque,
	kmerMapped;
	}

	unordered_map<string, string> *kmerStrand;
	unordered_map<string, int> *kmerFreque;
	unordered_map<string, float> *kmerMapped;
	
	/*Hashmap();
	Hashmap(unordered_map<string, char> map);
	Hashmap setHashMap(string filename);*/


//public:
//	unordered_map<string, char> umap;
//
//private:
//	string trio;
//	string nuclo;

};
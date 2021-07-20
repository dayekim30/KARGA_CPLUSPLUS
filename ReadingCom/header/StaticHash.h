#pragma once
#include <unordered_map>
#include <vector>

#include "AMRGene.h"


class StaticHash {
public:
	unordered_map<string, vector<string>> kmerGeneMapping;
	unordered_map<string, AMRGene> geneKmerMapping;
public:
	StaticHash() {
		kmerGeneMapping = unordered_map<string, vector<string>>();
		geneKmerMapping = unordered_map<string, AMRGene>();
	}
	~StaticHash() {}
};
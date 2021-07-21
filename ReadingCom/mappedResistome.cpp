#include "header\mappedResistome.h"
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <future>




void mappedResistome::wirteCSV(StaticHash& sh)
{
	fstream fout;
	fout.open("KARGA_mappedResistome.csv", ios::out | ios::app);
	fout << "GeneIdx,PercentGeneCovered,AverageKMerDepth\n";
	vector<string> vec;
	for (auto at : sh.geneKmerMapping) {
		vec.push_back(at.first);
	}
	sort(vec.begin(), vec.end());

	for (string key : vec) {

		auto& at = sh.geneKmerMapping.at(key);
		int totalKmer = at.kmerStrand->size();
		double percCovered(0);
		double kmerDepth(0);

		for (auto ai : *at.kmerStrand) {
			string fk = ai.first;
			string rk = ai.second;
			if (at.kmerMapped->end() != at.kmerMapped->find(fk) || at.kmerMapped->end() != at.kmerMapped->find(rk)) {
				percCovered = percCovered + 1;
				double dd (0);
				if (at.kmerMapped->end() != at.kmerMapped->find(fk)) dd += (double)(at.kmerMapped->at(fk));
				if (at.kmerMapped->end() != at.kmerMapped->find(rk)) dd += (double)(at.kmerMapped->at(rk));
				if (at.kmerStrand->end() != at.kmerStrand->find(rk)) {
					dd = dd / ((double)(at.kmerFreque->at(fk)) + (double)at.kmerFreque->at(rk));
				}
				else {
					dd = dd / (double)(at.kmerFreque->at(fk));
				}

				kmerDepth = kmerDepth + dd;
			}	
		}
		percCovered = percCovered / (double)(totalKmer);
		kmerDepth = kmerDepth / (double)(totalKmer);
		if (percCovered > 0.001f) {
			fout << key << "," << 100 * percCovered << "%" << "," << kmerDepth << "\n";
		}
	}
	fout.close();
	cout << "Reads and resistome mapped in = " << " s\r\n";
}

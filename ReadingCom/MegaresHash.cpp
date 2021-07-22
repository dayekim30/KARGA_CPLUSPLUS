#include <vector>
#include <iostream>
#include <typeinfo>
#include <unordered_map>
#include <memory>
#include "header\MegaresHash.h"
#include "header\StaticHash.h"

using namespace std;

typedef unordered_map<string, float> geneHitsWeighted;
typedef unordered_map<string, int> geneHitsUnweigthed;


void MegaresHash::KmerFromSeq(const string &id, const string &seq, StaticHash &sh)
{	
	AMRGene amrgene = AMRGene();
	

	Sequence s = Sequence(seq);
	string fwd = s.forwardSequence();
	string rwd = s.reverseComplement();
	
	int k = 17;
	
	for (int i = 0; i < fwd.size()-k+1; i++) {
		
		string fk = fwd.substr(i, k);
		
		if (sh.kmerGeneMapping.end() == sh.kmerGeneMapping.find(fk)) {
			//cout << "is empty" << endl;
			vector<string> ai;
			ai.push_back(id);
			sh.kmerGeneMapping[fk] = ai;
		}
		else {
			sh.kmerGeneMapping.at(fk).push_back(id);							 
		}

		string rk = rwd.substr(rwd.size()-(i+k), k);			
		if (sh.kmerGeneMapping.end() == sh.kmerGeneMapping.find(rk)) {
			//cout << "is empty" << endl;
			vector<string> ai;
			ai.push_back(id);
			sh.kmerGeneMapping[rk] = ai;
		}
		else {
			sh.kmerGeneMapping.at(rk).push_back(id);
		}
		

		if (amrgene.kmerFreque->end() == amrgene.kmerFreque->find(fk)) {
			amrgene.kmerFreque->insert({ fk, 1 });
		
		}else {
			amrgene.kmerFreque->insert_or_assign( fk, amrgene.kmerFreque->at(fk) + 1 );
		}
		
		if (amrgene.kmerFreque->end() == amrgene.kmerFreque->find(rk)) {
			amrgene.kmerFreque->insert({ rk, 1 });
		
		}else {
			amrgene.kmerFreque->insert_or_assign(rk, amrgene.kmerFreque->at(rk) + 1);
		}

		if (amrgene.kmerStrand->end() == amrgene.kmerStrand->find(fk)) {
			amrgene.kmerStrand->insert({ fk, rk });
		}

	}
	sh.geneKmerMapping.insert_or_assign(id, amrgene);

}



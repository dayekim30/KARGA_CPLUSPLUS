#include <vector>
#include <iostream>
#include <typeinfo>
#include <unordered_map>
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
			amrgene.kmerFreque->insert_or_assign(fk, 1);
		
		}else {
			amrgene.kmerFreque->insert_or_assign(fk, amrgene.kmerFreque->at(fk) + 1);
		}
		
		if (amrgene.kmerFreque->end() == amrgene.kmerFreque->find(rk)) {
			amrgene.kmerFreque->insert_or_assign(rk, 1);
		
		}else {
			amrgene.kmerFreque->insert_or_assign(rk, amrgene.kmerFreque->at(rk) + 1);
		}

		if (amrgene.kmerStrand->end() == amrgene.kmerStrand->find(fk)) {
			amrgene.kmerStrand->insert_or_assign(fk, rk);
		}

	}
	sh.geneKmerMapping.insert_or_assign(id, amrgene);
	

}

//void MegaresHash::geneFromSeq(const string& id, const string& seq, const int& pvalue, StaticHash& sh, bool& reportMultipleHits, bool& classiftReads)
//{
//	Sequence s = Sequence(seq);
//	string fwd = s.forwardSequence();
//	string rwd = s.reverseComplement();
//
//	int k = 17;
//	vector<string> kmerhits;
//	geneHitsWeighted ghw;
//	geneHitsUnweigthed guw;
//
//	for (int i = 0; i < fwd.size() - k + 1; i++) {
//
//		string fk = fwd.substr(i, k);
//		if (sh.kmerGeneMapping.end() != sh.kmerGeneMapping.find(fk)) {
//			
//			kmerhits.push_back(fk);
//			auto ai = sh.kmerGeneMapping.at(fk);
//			// look for the sequence which hits the most in this read
//			for (int a = 0; a < ai.size(); a++) {
//				
//				string &key = ai[a];
//				float frac = 1 / (float)(ai.size());
//				
//				if (ghw.end() == ghw.find(key)) { ghw.insert_or_assign(key, frac); }
//				else { ghw.insert_or_assign(key, ghw.at(key) + frac); }
//
//				if (guw.end() == guw.find(key)) { guw.insert_or_assign(key, 1); }
//				else { guw.insert_or_assign(key, guw.at(key) + 1); }
//
//			}
//		}
//	}
//
//	if (kmerhits.size() > pvalue) {
//		
//		//If multiple hits is reqired (should be optional)
//		if(!reportMultipleHits){
//
//			//find the sequence whose hits is the largest. 
//			float maxfreq =0;
//			string maxGene="";
//			for (auto x : ghw) {
//				if (maxfreq < x.second) { maxfreq = x.second; maxGene = x.first; }
//			}
//			
//
//
//		}
//		
//	}
//
//}



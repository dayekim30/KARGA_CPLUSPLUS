#pragma once
#include "AMRGene.h"
#include "Sequence.h"
#include "StaticHash.h"

class MegaresHash {
public:
	//MegaresHash(StaticHash& sh);
	MegaresHash() {}
	~MegaresHash() {}
	void KmerFromSeq(const string& id, const string& seq, StaticHash &sh);
	void geneFromSeq(const string& id, const string& seq, const int &pvalue, StaticHash &sh, bool &reportMultipleHits, bool& classiftReads);

	

};


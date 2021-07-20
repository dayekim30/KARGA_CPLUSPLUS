#include "header/AMRGene.h"

using namespace std;

AMRGene::AMRGene()
{
	kmerStrand = new unordered_map<string, string>();
	kmerFreque = new unordered_map<string, int>();
	kmerMapped = new unordered_map<string, float>();

}

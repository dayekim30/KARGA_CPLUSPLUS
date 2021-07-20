// ReadingCom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <random>
#include <unordered_map>
#include <assert.h>
#include <cassert>
#include "header/RandomGenerator.h"
#include "header/Parsing.h"
#include "header/AMRGene.h"
#include "header/StaticHash.h"

using namespace std;
//random_device rd;
//mt19937 mesenne(rd());
//uniform_int_distribution<> dice(1, 4);


int main()
{

   /* cout << "Hello World!\n";
	int input;
	cin >> input;
	RanGen r = RanGen();

	cout<<"\n"<<r.stringGeratpr(input) << endl;

	cout << "\nthis is from main \nwrite anything to see";*/


	cout << "Please write the fasta file name -> ex) filename.fasta : " << endl;
	
	/*unordered_map<string, vector<string>> kmerGeneMapping = unordered_map<string, vector<string>>();
	unordered_map<string, AMRGene> geneKmerMapping = unordered_map<string, AMRGene>();*/
	static StaticHash sh = StaticHash();
	

	string filename;
	/*cin >> filename;
	cout << "in mian the StaticHash's address is: " << &sh << endl;
	Parsing p = Parsing();
	
	p.ParsingMegares(filename, sh);
	

	cout << "in main, lets see the result-bucketsize: " << sh.kmerGeneMapping.bucket_count()<< endl;
	*/
	Parsing p = Parsing();
	cout << "\nPlease write the fastq file name -> ex) filename.fastq : " << endl;
	cin >> filename;
	p.ParsingFASTQ(filename, sh);

	
	/*string outt;
	cin >> outt;

	cout << outt<<endl;
	if (outt.size() > 2 && outt[0] == '>') {
		cout << outt[0];
	}
	else {
		cout << " different: " << outt[0];
	}*/

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

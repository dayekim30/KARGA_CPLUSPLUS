// ReadingCom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <random>
#include <unordered_map>
#include <assert.h>
#include <cassert>
#include <chrono>
#include <mutex> 
#include "header/RandomGenerator.h"
#include "header/Parsing.h"
#include "header/AMRGene.h"
#include "header/StaticHash.h"
#include "header/mappedResistome.h"

using namespace std;
using namespace std::chrono;

//random_device rd;
//mt19937 mesenne(rd());
//uniform_int_distribution<> dice(1, 4);

std::mutex mtx;
int main()
{

	cout << "Hello World!\n";
	
	cout << "Please write the fasta file name -> ex) filename.fasta : " << endl;
	
	static StaticHash sh = StaticHash();
	
	string filename;
	cin >> filename;

	auto start = high_resolution_clock::now();
	
	Parsing p = Parsing();
	p.ParsingMegares(filename, sh);
	
	cout << "in main, lets see the result-bucketsize: " << sh.kmerGeneMapping.size()<< endl;
	
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	cout << "the time to read and gererate Mapped hash table from FASTA is " << duration.count() * 1e-6 << endl;
		
	mtx.lock();
	cout << "would you like to get a report of multiplehits? if yes -> 1, if not ->0" << endl;
	bool reportMultipleHits;
	cin >> reportMultipleHits;

	cout << "would you like to get a report of classifyting reads? if yes -> 1, if not ->0" << endl;
	bool classiftReads;
	cin >> classiftReads;
	start = high_resolution_clock::now();
	cout << "\nPlease write the fastq file name -> ex) filename.fastq : " << endl;
	cin >> filename;
	mtx.unlock();
	p.ParsingFASTQ(filename, sh, reportMultipleHits, classiftReads);
	
	stop = high_resolution_clock::now();

	duration = duration_cast<microseconds>(stop - start);
	cout << "the time to read and gererate Mapped hash table from FASTQ is " << duration.count() * 1e-6 << endl;
	
	mappedResistome mrt = mappedResistome();
	mrt.wirteCSV(sh);
	exit(0);
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

#include <vector>
#include <random>
#include <iostream>
#include "header/RandomGenerator.h"




RanGen::RanGen() {}

random_device rd;
mt19937 mesenne(rd());
uniform_int_distribution<> dice(1, 4);




//string stringGeratpr(const int avg) {
//	
//	//char ranArray[avg];
//	changeToString(dice(mesenne));
//	
//
//}

// s has a range between 1-4.
char RanGen::changeToString(short s)
{
	char a = ' ';

	switch (s)
	{
	case 1:
		a = 'A';
		break;
	case 2:
		a = 'C';
		break;
	case 3:
		a = 'G';
		break;
	case 4:
		a = 'T';
		break;

	default:
		a = '?';
		break;
	}
	return a;
}

string RanGen::stringGeratpr(int a)
{ 
	using namespace std;

	vector<char> array;
	string result = "";
	
	//cout << "for generates \t";
	
	for (int i = 0; i < a; i++) {
		array.push_back(changeToString(dice(mesenne)));
		result = result + array[i];
		//cout <<array[i];
	}
	
	return result;
}

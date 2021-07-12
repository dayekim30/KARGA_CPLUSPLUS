#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Hashmap {
public:
	Hashmap();
	Hashmap(unordered_map<string, char> map);
	Hashmap setHashMap(string filename);


public:
	unordered_map<string, char> umap;

private:
	string trio;
	string nuclo;

};
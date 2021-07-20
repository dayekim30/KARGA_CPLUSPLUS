#pragma once
#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

class Sequence {


public:
    Sequence();
    ~Sequence() {}
    Sequence(string seq);
    void print();
    
    string forwardSequence();
    string reverseComplement();



    Sequence operator~();

    static bool test();

public:
    string mStr;

};

#endif

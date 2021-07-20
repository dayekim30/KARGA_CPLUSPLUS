
#include "header/Sequence.h"

Sequence::Sequence() {
}

Sequence::Sequence(string seq) {
    mStr = seq;
}




void Sequence::print() {
    std::cerr << mStr;
}

string Sequence::forwardSequence() {
    string str(mStr.length(), 0);
    for (int c = 0; c < mStr.length(); c++) {
        char base = mStr[c];
        switch (base) {
        case 'A':
        case 'a':
            str[c] = 'A';
            break;
        case 'T':
        case 't':
            str[c] = 'T';
            break;
        case 'C':
        case 'c':
            str[c] = 'C';
            break;
        case 'G':
        case 'g':
            str[c] = 'G';
            break;
        default:
            str[c] = 'N';
        }
    }
    return str;
}



string Sequence::reverseComplement() {
    string str(mStr.length(), 0);
    for (int c = 0; c < mStr.length(); c++) {
        char base = mStr[c];
        switch (base) {
        case 'A':
        case 'a':
            str[mStr.length() - c - 1] = 'T';
            break;
        case 'T':
        case 't':
            str[mStr.length() - c - 1] = 'A';
            break;
        case 'C':
        case 'c':
            str[mStr.length() - c - 1] = 'G';
            break;
        case 'G':
        case 'g':
            str[mStr.length() - c - 1] = 'C';
            break;
        default:
            str[mStr.length() - c - 1] = 'N';
        }
    }
    return str;
}




Sequence Sequence::operator~() {
    return reverseComplement();
}

bool Sequence::test() {
    Sequence s("AAAATTTTCCCCGGGG");
    Sequence rc = ~s;
    if (s.mStr != "AAAATTTTCCCCGGGG") {
        cerr << "Failed in reverseComplement() expect AAAATTTTCCCCGGGG, but get " << s.mStr;
        return false;
    }
    if (rc.mStr != "CCCCGGGGAAAATTTT") {
        cerr << "Failed in reverseComplement() expect CCCCGGGGAAAATTTT, but get " << rc.mStr;
        return false;
    }
    return true;
}
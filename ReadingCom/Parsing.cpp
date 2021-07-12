#include "header/Parsing.h"
//#include "frames.h"
#include <string>
#include <future>
#include <stdlib.h>

using namespace std;
Parsing::Parsing() {}

Parsing::Parsing(string id, string seq, string fuc) {
    mid = id;
    mseq = seq;
    //mfuc = fuc;
}

void Parsing::ParsingMegares(string filename)
{
    fstream newfile;
    /*string id;
    string seq;*/
    newfile.open(filename, ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) {   //checking whether the file is open
        string tp;
        while ((getline(newfile, tp))) {
            if (tp[0] != '>') {
                cout << "this is not a FASTA file" << endl;
                exit(0);
            }
            mid = tp;
            mseq = "";
            do {
                getline(newfile, tp);
                if (tp != "" ) break;
                       
                mseq += tp;

            } while (tp[0] != '>');


        }
        
       

      



        newfile.close();

    }
}

void Parsing::ParsingFASTQ(string filename)
{
    
}

void Parsing::setFile(string filename) {
    fstream newfile;
    string id;
    string seq;
    string fuc;
   /* Hashmap h = Hashmap();
    Hashmap he = h.setHashMap("neclo.txt");*/
    //output!!
    fstream fout;
    fout.open("resut.csv", ios::out | ios::app);
    newfile.open(filename, ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) {   //checking whether the file is open
        string tp;
        int i = 0;
        int j = 0;
        while ((getline(newfile, tp))) {
            if (i == 0) {
                mid = tp;
            }

            else if (i == 1) {
                mseq = tp;
            }
            else if (i == 2) {
               // mfuc = tp;
            }
            i++;//print the data of the string
            j++;
            if (i == 4) {
                i = 0;
               // frames f = frames(he);
             /*   f.getAllframes(mseq);
                fout << mid << "," << mseq << ","
                    << f.bwdFirst << ","
                    << f.bwdSecond << ","
                    << f.bwdThird << ","
                    << f.fwdFirst << ","
                    << f.fwdSecond << ","
                    << f.fwdThird << "\n";*/
            }

        }
        cout << "done j: " << j << " line" << endl;
        //read data from file object and put it into string.

        fout.close();
        newfile.close(); //close the file object.

      /*  return Parsing(mid, mseq, mfuc);*/

    }
}
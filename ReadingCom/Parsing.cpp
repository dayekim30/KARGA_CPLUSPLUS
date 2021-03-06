#include "header/Parsing.h"
#include "header/MegaresHash.h"
#include "header/RandomGenerator.h"
#include "header/Sequence.h"
//#include "frames.h"
#include <iostream>
#include <string>
#include <future>
#include <stdlib.h>
#include <algorithm>
#include <memory>



using namespace std;
Parsing::Parsing() {}

void Parsing::ParsingMegares(const string &filename, StaticHash& sh)
{
    fstream newfile;
    string mid;
    string mseq;

    newfile.open(filename, ios::in); //open a file to perform read operation using file object

    cout << "Reading AMR gene database, creating k - mer mapping(k = 17)"<< endl;
        if (newfile.is_open()) {   //checking whether the file is open
            string tp;
            int  i = 0;
            int j = 0;
            while ((getline(newfile, tp))) {
                if (tp[0] != '>') { cout << "wrong fasta format" << endl; exit(0); }
                mid = tp;
                mseq = "";
                do {
                   
                    getline(newfile, tp);
                    
                    
                    //sequ = tp;
                    mseq = tp + mseq;
                    j++;
                    if (tp != "" || newfile.eof()) break;
                    //cout << " j is increasing" << endl;

                } while (tp[0] != '>');
               
               
                i++;
                MegaresHash mh = MegaresHash();
                mh.KmerFromSeq(mid, mseq,sh);

                            
               
               
                if (i % 1000 == 0) {
                    cout <<  i << "genes processed" << "\n";
                }
               
            }
            
            newfile.close();
            cout << "\nthe number of line is ->" << i << endl;
            cout << "the number of line without > is ->" << j << endl;

        }
  
}

typedef unordered_map<string, float> geneHitsWeighted;
typedef unordered_map<string, int> geneHitsUnweigthed;
bool sortByVal(const pair<string, int>& a,
    const pair<string, int>& b)
{
    return (a.second < b.second);
}
void Parsing::ParsingFASTQ(const string &filename, StaticHash &sh,const bool& reportMultipleHits,const bool& classifyReads)
{
    const int numT = 125000;
    const int k = 17;
    fstream newfile;
    string mid;
    string mseq;
    double avg = 0;
   
    newfile.open(filename, ios::in); //open a file to perform read operation using file object

    if (newfile.is_open()) {   //checking whether the file is open
        string tp;
        int i = 0;
       

        while ((getline(newfile, tp))) {

            //if (tp != "" || newfile.eof()) break;
            if (tp[0] == '@') {

                getline(newfile, tp);
                avg = avg + (double)tp.length();

                getline(newfile, tp);
                getline(newfile, tp);
            }
            else {
                cout << " this is wrong form of fastq file" << endl;

            }
            i++;
            //cout << "header is: \t" << mid << endl;
            //cout << "sequence is: \t" << mseq << endl;
        }
        cout << "the number of line is " << i << endl;
        avg = (int)((avg / (double)i) + 0.5f);
        cout << "the number of line is (in integer): " << "\t" << (int)avg << endl;

        newfile.close();
    }
        // random distribution starts

        int matchDist[numT];
        cout << " the random distribution starts" << endl;
        RanGen r = RanGen();
        for (int a = 0; a < numT; a++) {
            string random = r.stringGeratpr(avg);

            for (int b = 0; b < random.length()-k+1; b++) {
                string fk = random.substr(b, k);
                if (sh.kmerGeneMapping.end() != sh.kmerGeneMapping.find(fk)) {
                    matchDist[a] = matchDist[a] + 1;               
                }         
            }
            if (a % (numT / 5) == 0) cout << a << "..";
        }
        sort(matchDist, matchDist + numT);
        int pvalthres = matchDist[99 * numT / 100];
        cout << "\nthe pvalue is " << pvalthres << endl;

        // P value came out. 

        // fastq file analysis starts

       // newfile.open(filename, ios::in);
        fstream fout;
        fout.open("KARGA_mappedReads.csv", ios::out | ios::app); 
        fout << "ids, GeneProbability/KmersHitsOnGene/KmersHitsOnAllGenes/KmersTotal, GeneAnnotation"<< "\n";
        
        newfile.open(filename, ios::in);
        
        if (newfile.is_open()) {   //checking whether the file is open
          string tp;
          int i = 0;
          string mid;
          string mseq;
            while ((getline(newfile, tp))) {

                if (tp[0] == '@') {
                    mid = tp;
                    getline(newfile, tp);
                    mseq = tp;
                    getline(newfile, tp);
                    getline(newfile, tp);
                }
                else {
                    cout << " this is wrong form of fastq file" << endl;
                }

                // Chcke the length of the sequence is longer than K
                if (mseq.length() > k) {
                    Sequence s = Sequence(mseq);
                    string fwd = s.forwardSequence();
                    string rwd = s.reverseComplement();

                    vector<string> kmerhits;
                    geneHitsWeighted ghw;
                    geneHitsUnweigthed guw;

                    for (int i = 0; i < fwd.size() - k + 1; i++) {

                        string fk = fwd.substr(i, k);
                        if (sh.kmerGeneMapping.end() != sh.kmerGeneMapping.find(fk)) {

                            kmerhits.push_back(fk);
                            auto ai = sh.kmerGeneMapping.at(fk);
                            // look for the sequence which hits the most in this read
                            for (int a = 0; a < ai.size(); a++) {

                                string& key = ai[a];
                                float frac = 1 / (float)(ai.size());

                                if (ghw.end() == ghw.find(key)) { ghw.insert_or_assign(key, frac); }
                                else { ghw.insert_or_assign(key, ghw.at(key) + frac); }

                                if (guw.end() == guw.find(key)) { guw.insert_or_assign(key, 1); }
                                else { guw.insert_or_assign(key, guw.at(key) + 1); }

                            }
                        }
                    }

                    if (kmerhits.size() > pvalthres) {

                        //If multiple hits is reqired (should be optional)
                        if (!reportMultipleHits) {

                            //find the sequence whose hits is the largest. 
                            float maxfreq = 0;
                            string maxGene = "";
                            for (auto x : ghw) {
                                if (maxfreq < x.second) { maxfreq = x.second; maxGene = x.first; }
                            }
                            if (classifyReads) {
                            
                                float fr = (float)((int)(maxfreq * 100 + 0.5) / 100);
                                float fp = fr / kmerhits.size();
                                fout << mid << "," << fp << "/" << guw.at(maxGene) << "/" << kmerhits.size() << "/" << fwd.length() - k + 1 << "," << maxGene << "\n";                          
                            }
                            auto &genehit = sh.geneKmerMapping.at(maxGene);
                            for (auto kh : kmerhits) {
                                if (genehit.kmerFreque->end() != genehit.kmerFreque->find(kh)) {
                                    if (genehit.kmerMapped->end() == genehit.kmerMapped->find(kh)) {
                                        genehit.kmerMapped->insert_or_assign(kh, 1);
                                    }
                                    else {
                                        genehit.kmerMapped->insert_or_assign(kh, genehit.kmerMapped->at(kh)+ 1);
                                    }
                                }                            
                            }
                        }
                        if (reportMultipleHits) {
                            
                            vector<pair<string, float>> vec;
                            for (auto at : ghw) {
                                vec.push_back(make_pair(at.first, at.second));
                            }
                            sort(vec.begin(), vec.end(), sortByVal);

                            if (classifyReads) {
                                fout << mid;
                                float cumul = 0;
                                for (int a = 0; a < vec.size(); a++) {
                                    float fr = vec.at(a).second;
                                    float fp = (float)((int)(fr * 100 + 0.5) / 100);
                                    fr = fr / (float)kmerhits.size();
                                    cumul = cumul + fr;
                                    fout << "," << fr << "/" << guw.at(vec.at(a).first) << "/" << kmerhits.size() << "/" << fwd.length() - k + 1
                                        << "," << vec.at(a).first;
                                    if (a > 19 || cumul > 0.95f) break;
                                }
                                fout << "\n";
                            }
                            float cumul = 0;
                            
                            for (int b = 0; b < vec.size(); b++) {
                                
                                if (b <= 19 && cumul <= 0.95f) {
                                
                                    auto& genehits = sh.geneKmerMapping.at(vec.at(b).first);
                                    float fr = vec.at(b).second;
                                    fr = fr / (float)kmerhits.size();
                                    cumul = cumul + fr;
                                    fr = 1;
                                    for (auto kh : kmerhits) {
                                        if (genehits.kmerFreque->end() != genehits.kmerFreque->find(kh)) {
                                            if (genehits.kmerMapped->end() == genehits.kmerMapped->find(kh)) {
                                                genehits.kmerMapped->insert_or_assign(kh, fr);
                                            }
                                            else {
                                                genehits.kmerMapped->insert_or_assign(kh, genehits.kmerMapped->at(kh)+ fr);
                                            }
                                        }
                                    }
                                }
                                
                            }


                        }

                    }
                    else {
                        if (classifyReads) {
                            fout << mid << ", ? / ? / ? / ? , ?" << "\n";
                        }
                    }
                    
                }
                if (i % 10000 == 0) {
                    cout<<i << " reads processed; " <<"\r\n";
                }



              
                i++;
            }
           
          
           

            fout.close();
            newfile.close();
        }
        //close the file object.

      /*  return Parsing(mid, mseq, mfuc);*/              
}

//void Parsing::setFile(string filename) {
//    fstream newfile;
//    string id;
//    string seq;
//    string fuc;
//   /* Hashmap h = Hashmap();
//    Hashmap he = h.setHashMap("neclo.txt");*/
//    //output!!
//    fstream fout;
//    fout.open("resut.csv", ios::out | ios::app);
//    newfile.open(filename, ios::in); //open a file to perform read operation using file object
//    if (newfile.is_open()) {   //checking whether the file is open
//        string tp;
//        int i = 0;
//        int j = 0;
//        while ((getline(newfile, tp))) {
//            if (i == 0) {
//                mid = tp;
//            }
//
//            else if (i == 1) {
//                mseq = tp;
//            }
//            else if (i == 2) {
//               // mfuc = tp;
//            }
//            i++;//print the data of the string
//            j++;
//            if (i == 4) {
//                i = 0;
//               // frames f = frames(he);
//             /*   f.getAllframes(mseq);
//                fout << mid << "," << mseq << ","
//                    << f.bwdFirst << ","
//                    << f.bwdSecond << ","
//                    << f.bwdThird << ","
//                    << f.fwdFirst << ","
//                    << f.fwdSecond << ","
//                    << f.fwdThird << "\n";*/
//            }
//
//        }
//        cout << "done j: " << j << " line" << endl;
//        //read data from file object and put it into string.
//
//        fout.close();
//        newfile.close(); //close the file object.
//
//      /*  return Parsing(mid, mseq, mfuc);*/
//
//    }
//}
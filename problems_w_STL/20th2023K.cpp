#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;

int wordFreq(string* text_file){
    map<string, int> wordCount;
    string c;
    // Read the contents of the file input file and store them in map as wordCount["Bravo"=1], etc.
    ifstream fin(text_file);
    // or for (auto c:fin)
    while (fin >> c) {
        ++wordCount[c]->second;
    }
    fin.close();

    ifstream fin("words.txt");
    // or for (auto c:fin)
    while (fin >> c) {
        try{
            cout<< "Word "<< wordCount[c]->first << "is present " << wordCount[c]->second << " times" <<endl;
            throw c;
        }
        catch(string* c){
            cout<< "Word "<< c << " not present in words.txt"<<endl
            continue;
            }
    }
    fin.close();
}
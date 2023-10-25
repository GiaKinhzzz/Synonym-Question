#ifndef SEMANTICDESCRIPTOR_H_INCLUDED
#define SEMANTICDESCRIPTOR_H_INCLUDED

#include <map>
#include <iostream>
#include <cmath>
#include <fstream>
#include <chrono>
#include <vector>
#include <set>

using namespace std;
using namespace chrono;

class SemanticDescriptor
{
    private:

        string targetWord;
        map<string, int> contextWords;

    public:
        SemanticDescriptor(string _targetWord) : targetWord(_targetWord) {}
        string getTargetWord() {return targetWord;}
        void processContextWord(string s);
        int operator*(const SemanticDescriptor& desc);
        friend ostream& operator<<(ostream& os, const SemanticDescriptor& desc);
        friend istream& operator>>(istream& is, SemanticDescriptor& desc);
};

#endif // SEMANTICDESCRIPTOR_H_INCLUDED
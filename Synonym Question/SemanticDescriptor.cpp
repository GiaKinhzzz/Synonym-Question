#include "SemanticDescriptor.h"

//Each SemanticDescriptor has a target word and bundle of contextWord(word and count)

//Increment the count of the word "s" or add the word to the contextWord of target word
void SemanticDescriptor::processContextWord(string s)
{
    auto it = contextWords.find(s);
    if (it == contextWords.end()) contextWords.insert({s, 1}); //first time seeing the context word for this descriptor
    else it->second++;
}

int SemanticDescriptor::operator*(const SemanticDescriptor& desc)
{
    int sum = 0;
    for (auto iter = this->contextWords.begin(); iter != this->contextWords.end(); iter++) {
        auto descIter = desc.contextWords.find(iter->first);
        if (descIter != desc.contextWords.end()) {
            sum += iter->second * descIter->second;
        }
    }
    return sum;
}

//Print out the target word associated with frequency of context words
ostream& operator<<(ostream& os, const SemanticDescriptor& desc)
{
    os << desc.targetWord << " { ";
    for (auto word = desc.contextWords.begin(); word != desc.contextWords.end(); word++) {
        os << word->first << " " << word->second << " ";
    }
    os << "}" << endl << endl;
    return os;
}

//Read the descriptor file
istream& operator>>(istream& is, SemanticDescriptor& desc)
{
    desc.targetWord = "";
    desc.contextWords.clear();
    string targetWord;
    is >> targetWord;
    desc.targetWord = targetWord;
    char c;
    is >> c;
    if (c != '{')
    {
        is.unget();
        is.clear(ios::failbit);
        return is;
    }
    while (is)
    {
        is >> c;
        if (c == '}') return is;
        is.unget();
        string word;
        int count;
        is >> word >> count;
        desc.contextWords.insert({word, count}); 
    }
    return is;
}
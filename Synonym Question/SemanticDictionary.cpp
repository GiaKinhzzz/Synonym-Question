#include "SemanticDictionary.h"
//SemanticDictionary hold a list of all descriptors

//Separate the text into several sentences and return the list of sentences
vector<vector<string>> getSentenceLists(string text)
{
    vector<vector<string>> sentenceLists;
    vector<string> sentenceList;
    string word = "";

    for(size_t i = 0; i < text.size(); i++)
    {
        if (isalpha(text[i])) word += tolower(text[i]);
        else
        {
            if (word.size() > 0) 
            {
                if (!isStopWord(word)) sentenceList.push_back(word);
                word = "";
            }
            if ((text[i] == '?' || text[i] == '.' || text[i] == '!') && sentenceList.size() > 0) 
            {
                sentenceLists.push_back(sentenceList);
                sentenceList.clear();
            }
        }
    }

    if (word.size() > 0) 
    {
        if (!isStopWord(word)) sentenceList.push_back(word);
        word = "";
    }
    if (sentenceList.size() > 0) 
    {
        sentenceLists.push_back(sentenceList);
    }
    return sentenceLists;
}

//Print out each sentence in the sentence list
ostream& operator<<(ostream& os, const vector<vector<string>>& sentenceLists)
{
    os << "Sentence Lists: " << endl;
    os << "[" << endl;
    for (size_t i = 0; i < sentenceLists.size(); i++)
    {
        os << "[";
        for (size_t j = 0; j < sentenceLists[i].size(); j++)
        {
            os << sentenceLists[i][j] << " ";
        }
        os << " ]" << endl;
    }
    os << "]";
    return os;
}

//Update the descriptor of the targetWord with new sentence
void SemanticDictionary::processTargetWord(string targetWord, vector<string> sentenceList)
{
    auto it = semanticDescriptors.find(targetWord);
    if (it == semanticDescriptors.end()) {
        it = (semanticDescriptors.insert({targetWord, SemanticDescriptor(targetWord)})).first;
    }
    for (size_t j = 0; j < sentenceList.size(); j++)
    {
        if (sentenceList[j] != targetWord) it->second.processContextWord(sentenceList[j]);
    }
}

double SemanticDictionary::getSimilarity(string targetWord1, string targetWord2)
{
    auto iter1 = semanticDescriptors.find(targetWord1);
    auto iter2 = semanticDescriptors.find(targetWord2);
    if (iter1 == semanticDescriptors.end() || iter2 == semanticDescriptors.end()) throw runtime_error("Target word(s) unknown");
    SemanticDescriptor a = iter1->second;
    SemanticDescriptor b = iter2->second;
    return (a*b*1.0) / (sqrt(a*a) * sqrt(b*b));
}

string SemanticDictionary::mostSimilarWord(string word, vector<string> choices)
{
    double highest = getSimilarity(word, choices[0]);
    size_t index = 0;
    for(size_t i = 1; i < choices.size(); i++)
    {
        double temp = getSimilarity(word, choices[i]);
        if (highest < temp)
        {
            highest = temp;
            index = i;
        }
    }
    return choices[index];
}

ostream& operator<<(ostream& os, const SemanticDictionary& d)
{
    os << "Semantic Descriptors:" << endl;
    os << "{" << endl;
    for (auto it = d.semanticDescriptors.begin(); it != d.semanticDescriptors.end(); it++) {
        os << it->second << endl;
    }
    os << "}" << endl;
    return os;
}

istream& operator>>(istream& is, SemanticDictionary& d)
{
    d.semanticDescriptors.clear();
    SemanticDescriptor desc("");
    char c;
    do { is >> c; }
    while (c != '{');
    while (is >> desc)
    {
        d.semanticDescriptors.insert({desc.getTargetWord(), desc});
    }
    return is;
}

bool isStopWord(string s)
{
    return stopWords.find(s) != stopWords.end();
}

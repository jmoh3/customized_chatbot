#include "TfIdfVector.h"
#include <vector>
#include <string>
#include <map>
#include <math.h>
#include <iostream>
#include <sstream> 
#include "../Preprocessing/Message.h"

using std::vector;
using std::string;
using std::map;
using std::stringstream;
using std::getline;

TfIdfVector::TfIdfVector(vector<Message> messages) {


}

void TfIdfVector::init_word_count_maps(const vector<Message>& messages) {

}

map<string, int> TfIdfVector::message_to_word_map(const Message& message) const {
  string content = message.getContent();
  vector<string> splitMessage = split(content, cDelimiter);

  map<string, int> word_count_map;

  for (const string & word : splitMessage) {
    if (word_count_map.find(word) != word_count_map.end()) {
      word_count_map[word] += 1;
    } else {
      word_count_map[word] = 1;
    }
  }

  return word_count_map;
}

// code from: https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
vector<string> TfIdfVector::split(const string toSplit, const char delim) const {
  vector<string> splitString;

  stringstream check1(toSplit);

  string intermediate; 
      
  // Tokenizing w.r.t. space ' ' 
  while(getline(check1, intermediate, ' ')) { 
    splitString.push_back(intermediate); 
  }

  return splitString;
}

double TfIdfVector::calculateTfIdf(int termCt, int documentWordCt, int documentCt, int numDocs) {
  double termFreq = (double) termCt / (double) documentWordCt;
  double inverseDocumentFreq = log((double) numDocs / (double) documentCt);

  return termFreq * inverseDocumentFreq;
}
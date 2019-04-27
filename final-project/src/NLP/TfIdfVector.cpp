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
  init_word_count_maps(messages);

}

map<string, int> TfIdfVector::getCommonWordMap(map<string, map<string, int>> wordMap) {
  map<string, int> commonWords;

  for (auto wordCountIterator = wordMap.begin(); wordCountIterator != wordMap.end(); wordCountIterator++) {
    map<string, int> wordCountMap = wordCountIterator->second;
    for (auto wordIterator = wordCountMap.begin(); wordIterator != wordCountMap.end(); wordIterator++) {
      string currentWord = wordIterator->first;
      if (commonWords.find(currentWord) != commonWords.end()) {
        commonWords[currentWord] += 1;
      } else {
        commonWords[currentWord] = 1;
      }
    }
  }

  return commonWords;
}

void TfIdfVector::init_word_count_maps(vector<Message>& messages) {
  for (auto it = messages.begin(); it != messages.end(); it++) {
    map<string, int> word_count_map = message_to_word_map(*it);
    word_count_maps[it->getMessageId()] = word_count_map;
  }
}

map<string, int> TfIdfVector::message_to_word_map(Message& message) const {
  string content = message.getContent();
  vector<string> splitMessage = split(content, cDelimiter);
  message.setWordCount(splitMessage.size());

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

  stringstream stream(toSplit);
  string intermediate;
      
  while(getline(stream, intermediate, delim)) {
    splitString.push_back(intermediate); 
  }

  return splitString;
}

double TfIdfVector::calculateTfIdf(int termCt, int documentWordCt, int documentCt, int numDocs) {
  double termFreq = (double) termCt / (double) documentWordCt;
  double inverseDocumentFreq = log((double) numDocs / (double) documentCt);

  return termFreq * inverseDocumentFreq;
}
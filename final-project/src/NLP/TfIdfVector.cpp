#include "TfIdfVector.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "../Preprocessing/Message.h"

using std::vector;
using std::string;
using std::map;

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

vector<string> TfIdfVector::split(const string toSplit, const char delim) const {
  vector<string> splitString;

  int splitStart = 0;

  for (int i = 0; i < toSplit.length(); i++) {
    if (toSplit[i] == delim) {
      std::cout << "here: " << toSplit.substr(splitStart, i) << std::endl;
      splitString.push_back(toSplit.substr(splitStart, i));
      splitStart = i + 1;
      std::cout << splitStart << std::endl;
    }
  }
  
  if (splitStart != toSplit.length()) {
    splitString.push_back(toSplit.substr(splitStart, toSplit.length()));
  }

  return splitString;
}
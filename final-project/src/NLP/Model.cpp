#include "Model.h"
#include "TfIdfVector.h"
#include "../Preprocessing/Message.h"
#include "../Preprocessing/MessageParser.h"
#include <iostream>
#include <vector>
#include <map>
#include <utility>

using std::string;
using std::vector;
using std::map;
using std::pair;

Model::Model(vector<pair<vector<Message>, Message>> & pairs) {
  vector<Message> vec;
  map<string, Message *> idToMessage;

  for (auto pairIterator = pairs.begin(); pairIterator != pairs.end(); pairIterator++) {
    vector<Message> incomingMessages = pairIterator->first;
    Message response = pairIterator->second;

    for (auto messageIt = incomingMessages.begin(); messageIt != incomingMessages.end(); messageIt++) {
      vec.push_back(*messageIt);
      string messageId = messageIt->getMessageId();
      idToMessage[messageId] = &response;
    }
  }

  this->vectorizer = TfIdfVector(vec, 0, 100);

}

string Model::getResponse(string input) {
  return "";
}
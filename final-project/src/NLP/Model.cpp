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

Model::Model() {
  // does absolutely nothing
}

Model::Model(string messageFileName, string user) {
  this->user = user;
  MessageParser messages(messageFileName);

  vector<pair<vector<Message>, Message>> pairs = messages.getMessageResponsePairs(user);

  vector<Message> messageVector;
  map<string, string> idToMessage;

  for (auto pairIterator = pairs.begin(); pairIterator != pairs.end(); pairIterator++) {
    vector<Message> incomingMessages = pairIterator->first;
    Message response = pairIterator->second;

    for (auto messageIt = incomingMessages.begin(); messageIt != incomingMessages.end(); messageIt++) {
      messageVector.push_back(*messageIt);
      string messageId = messageIt->getMessageId();
      string responseContent = response.getContent();
      idToMessage[messageId] = responseContent;
    }
  }

  this->vectorizer = TfIdfVector(messageVector, kMinFrequency, kMaxFrequency);
  this->idToResponseMap = idToMessage;
}

Model::Model(Model & other) {
  this->idToResponseMap = other.idToResponseMap;
  this->vectorizer = other.vectorizer;
}

Model& Model::operator=(const Model & other) {
  this->idToResponseMap = other.idToResponseMap;
  this->vectorizer = other.vectorizer;
  
  return *this;
}

string Model::getResponse(const string input) {
  Message message(input);

  string id = vectorizer.getMostSimilarMessageId(message);

  auto findMessageIterator = idToResponseMap.find(id);

  if (findMessageIterator != idToResponseMap.end()) {
    string responseMessage = findMessageIterator->second;
    return responseMessage;
  } else {
    return kDefaultResponse;
  }
}

string Model::getUser() const {
  return user;
}

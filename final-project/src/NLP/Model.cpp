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

Model::Model(string messageFileName, string user) {
  MessageParser messages(messageFileName);

  vector<pair<vector<Message>, Message>> pairs = messages.getMessageResponsePairs(user);

  vector<Message> messageVector;
  map<string, Message *> idToMessage;

  for (auto pairIterator = pairs.begin(); pairIterator != pairs.end(); pairIterator++) {
    vector<Message> incomingMessages = pairIterator->first;
    Message response = pairIterator->second;

    for (auto messageIt = incomingMessages.begin(); messageIt != incomingMessages.end(); messageIt++) {
      messageVector.push_back(*messageIt);
      string messageId = messageIt->getMessageId();
      Message* heapResponse = new Message(response.getContent(), response.getSender(), response.getMessageId());
      idToMessage[messageId] = heapResponse;
    }
  }

  this->vectorizer = TfIdfVector(messageVector, 0, 100);
  this->idToResponseMap = idToMessage;
}

string Model::getResponse(const string input) {
  Message message(input);

  string id = vectorizer.getMostSimilarMessageId(message);
  std::cout << id << std::endl;

  auto findMessageIterator = idToResponseMap.find(id);

  if (findMessageIterator != idToResponseMap.end()) {
    Message* responseMessagePtr = findMessageIterator->second;
    string responseContent = responseMessagePtr->getContent();

    return responseContent;
  } else {
    return kDefaultResponse;
  }
}
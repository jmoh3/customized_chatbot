#pragma once

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

class Model {
  public:
    Model(vector<pair<vector<Message>, Message>> & pairs);
    string getResponse(string input);

  private:
    map<string, Message*> messageIdToResponseMap;
    TfIdfVector vectorizer;
    map<string, Message *> idToResponseMap;
}
#pragma once

#include "TfIdfVector.h"
#include "../Preprocessing/Message.h"
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
    Model(string messageFileName, string user);
    string getResponse(const string input);

  private:
    const string kDefaultResponse = "I'm sorry, I didn't understand that.";

    map<string, Message*> messageIdToResponseMap;
    TfIdfVector vectorizer;
    map<string, Message *> idToResponseMap;
};
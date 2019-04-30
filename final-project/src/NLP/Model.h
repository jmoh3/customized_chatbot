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
    Model();
    Model(Model & other);
    Model(string messageFileName, string user);
    ~Model();
  
    Model& operator=(const Model & other);

    string getResponse(const string input);

  private:
    const string kDefaultResponse = "I'm sorry, I didn't understand that.";

    TfIdfVector vectorizer;
    map<string, string> idToResponseMap;
};

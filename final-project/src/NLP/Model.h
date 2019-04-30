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
    /**
     * Default constructor. Should never be used, just to keep compiler from complaining.
     */
    Model();
  
    /**
     * Copy constructor.
     *
     * @param other model we are using to construct self.
     */
    Model(Model & other);
  
    /**
     * Regular constructor.
     *
     * @param messageFileName filename we are getting messages from.
     */
    Model(string messageFileName, string user);
  
    /**
     * Copy assignment operator.
     *
     * @param other model we are using to construct self.
     */
    Model& operator=(const Model & other);

    /**
     * Gets the model's response for a given message by finding the most similar message that's been sent to user.
     *
     * @param input input message.
     */
    string getResponse(const string input);
  
    /**
     * Gets the user whose responses the model is returning.
     */
    string getUser() const;

  private:
    /** Default response if no similar message is found. */
    const string kDefaultResponse = "I'm sorry, I didn't understand that.";

    /** TfIdf vectorizer we are using (contains tfidf vectors) */
    TfIdfVector vectorizer;
  
    /** Hashmap containing message ids to their string responses. */
    map<string, string> idToResponseMap;
  
    /** Name of user whose responses the model is returning. */
    string user;
};

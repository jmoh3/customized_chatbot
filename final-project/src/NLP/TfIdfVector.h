 /*
 * Some of these methods/ideas were taken from CS 225's lab_dict:
 * 
 * @author Zach Widder
 * @date Fall 2014
 */

#pragma once

#include <vector>
#include <string>
#include <map>
#include "../Preprocessing/Message.h"

using std::vector;
using std::string;
using std::map;

class TfIdfVector {

  public:
    /**
     * Basic constructor from a list of messages.
     * 
     * @param messages vector of Message objects.
     */
    TfIdfVector(vector<Message> messages);

  private:
    /**
     * #word_count_maps holds a map for each message. Each map maps a word in
     * that message to the number of times it has been seen in that message.
     */
    vector<map<string, unsigned int>> word_count_maps;

    /**
     * #word_frequencies maps a word to the number of messages that word appears in
     */
    std::map<std::string, unsigned int> word_frequencies;

    /**
     * Initializes #word_count_maps.
     * @param messages The vector of messages that will be used
     */
    void init_word_count_maps(const vector<Message>& messages);

    /**
     * Takes a message and transforms it to a vector of all words in that file.
     * @param message The name of the file that will fill the vector
     */
    vector<string> message_to_vector(const Message& message) const;

    unsigned int num_messages = 0;
};
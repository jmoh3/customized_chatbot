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

  // private:
    const char cDelimiter = ' ';
    /**
     * #word_count_maps holds a map for each message. Each map maps a word in
     * that message to the number of times it has been seen in that message.
     */
    map<string, map<string, unsigned int>> word_count_maps;

    /**
     * #word_frequencies maps a word to the number of messages that word appears in
     */
    map<string, unsigned int> word_frequencies;

    /**
     * Initializes #word_count_maps.
     * @param messages The vector of messages that will be used
     */
    void init_word_count_maps(const vector<Message>& messages);

    /**
     * Takes a message and transforms it to a vector of all words in that message.
     * @param message The message that will fill the vector
     */
    map<string, int> message_to_word_map(const Message& message) const;

    /**
     * String splitter helper function
     * @param toSplit input string to split.
     * @param delim delimiter to split on.
     */
    vector<string> split(const string toSplit, const char delim) const;

    /**
     * Helper function for calculation tfidf values.
     * 
     * @param termFreq the frequency of the term in the document.
     * @param documentWordCt number of words in document
     * @param documentFreq number of documents containing the word.
     * @param numDocs total number of documents.
     */
    double calculateTfIdf(int termCt, int documentWordCt, int documentCt, int numDocs);

    unsigned int num_messages = 0;
};
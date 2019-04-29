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

int main() {

    MessageParser messages("../../data/messages/inbox/jatinmathur_4qu8ioyqrq/message_1.json");

    vector<pair<vector<Message>, Message>> pairs = messages.getMessageResponsePairs("Jackie Oh");

    vector<Message> vec;
    map<string, Message *> idToMessage;

    for (auto it = pairs.begin(); it != pairs.end(); it++) {
        for (auto messageIt = it->first.begin(); messageIt != it->first.end(); messageIt++) {
            vec.push_back(*messageIt);
            string messageId = messageIt->getMessageId();
            idToMessage[messageId] = &(*messageIt);
        }
    }

    TfIdfVector vectorizer(vec, 0, 100);

    Message message("when are you coming?", "jackie", "123");

    string id = vectorizer.getMostSimilarMessageId(message);

    std::cout << id << std::endl;

    auto it = idToMessage.find(id);

    if (it != idToMessage.end()) {
        std::cout << it->second->getContent() << std::endl;
    }

    // std::cout << idToMessage[id].getContent() << std::endl;

    // map<string, sparseVector> vectors = vectorizer.getVectors();
    // int vectorLength = vectorizer.getVectorLength();

    // std::cout << "Number of messages: " << vectors.size() << std::endl;
    // std::cout << "Length of tfidf vectors: " << vectorLength << std::endl;

    // for (auto it = vectors.begin(); it != vectors.end(); it++) {
    //     sparseVector vec = it->second;
    //     for (int i = 0; i < vectorLength; i++) {
    //         if (vec.find(i) == vec.end()) {
    //             std::cout << "0 ";
    //         } else {
    //             std::cout << vec[i] << " ";
    //         }
    //     }

    //     std::cout << "\n";
    // }

    // sparseVector vec1 = {{0 , 1}, {1, 1}};
    // sparseVector vec2 = {{1 , 1}};

    // std::cout << vectorizer.cosineSimilarity(vec1, vec2) << std::endl;

    return 0;
}
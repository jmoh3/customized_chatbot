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

    MessageParser messages("../../data/messages/inbox/nanditaravikumar_ojm_ljprrg/message_1.json");

    vector<pair<vector<Message>, Message>> pairs = messages.getMessageResponsePairs("Jackie Oh");

    vector<Message> vec;

    for (auto it = pairs.begin(); it != pairs.end(); it++) {
        for (const Message & message : it->first) {
            vec.push_back(message);
        }
    }

    TfIdfVector vectorizer(vec, 0, 100);

    vector<sparseVector> vectors = vectorizer.getVectors();
    int vectorLength = vectorizer.getVectorLength();

    std::cout << vectors.size() << std::endl;
    std::cout << vectorLength << std::endl;

    for (auto it = vectors.begin(); it != vectors.end(); it++) {
        sparseVector vec = *it;
        for (int i = 0; i < vectorLength; i++) {
            if (vec.find(i) == vec.end()) {
                std::cout << "0 ";
            } else {
                std::cout << vec[i] << " ";
            }
        }

        std::cout << "\n";
    }

    return 0;
}
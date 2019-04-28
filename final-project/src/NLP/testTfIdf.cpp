#include "TfIdfVector.h"
#include "../Preprocessing/Message.h"
#include <iostream>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

int main() {
    Message message("hello my name is jackie", "jackie", "1234");
    Message message2("hello my friend today is a very nice day", "emily", "12345");

    std::cout << message.getContent() << ", " << message.getSender() << ", " << message.getMessageId() << std::endl;

    vector<Message> vec;
    vec.push_back(message);
    vec.push_back(message2);

    TfIdfVector vectorizer(vec);

    // map<string, int> split = vectorizer.message_to_word_map(message);

    // for (auto it = split.begin(); it != split.end(); it++) {
    //     std::cout << it->first << ", " << it->second << std::endl;
    // }

    vector<vector<double>> vectors = vectorizer.getVectors();

    std::cout << vectors.size() << std::endl;

    for (auto it = vectors.begin(); it != vectors.end(); it++) {
        for (auto secondIt = it->begin(); secondIt != it->end(); secondIt++) {
            std::cout << *secondIt << " ";
        }

        std::cout << "\n";
    }

    return 0;
}
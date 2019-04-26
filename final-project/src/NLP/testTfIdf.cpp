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

    std::cout << message.getContent() << ", " << message.getSender() << ", " << message.getMessageId() << std::endl;

    vector<Message> vec;

    TfIdfVector vectorizer(vec);

    map<string, int> split = vectorizer.message_to_word_map(message);

    for (auto it = split.begin(); it != split.end(); it++) {
        std::cout << it->first << ", " << it->second << std::endl;
    }

    return 0;
}
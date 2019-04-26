#include "MessageParser.h"

#include <vector>
#include <utility>

using std::string;
using std::vector;
using std::pair;

// clang++ -std=c++11 testMessageParser.cpp MessageParser.cpp Message.cpp -o parseMessages
// ./parseMessages
int main() {
  MessageParser messages("../../data/messages/inbox/jatinmathur_4qu8ioyqrq/message_1.json");

  vector<pair<vector<Message>, Message>> pairs = messages.getMessageResponsePairs("Jackie Oh");

  return 0;
}
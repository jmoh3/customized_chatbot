#pragma once

#include <string>
#include <vector>
#include "Message.h"
#include <utility>

class MessageParser {
  public:
    MessageParser(std::string filename);
    std::vector<Message> getMessages();
    std::vector<std::pair<std::vector<Message>, Message>> getMessageResponsePairs(std::string user);

  private:
    std::vector<Message> messages;
};
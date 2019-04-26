#pragma once

#include <string>
#include <vector>
#include "Message.h"

class MessageParser {
  public:
    MessageParser(std::string filename);
    std::vector<Message> getMessages();
  private:
    std::vector<Message> messages;
};
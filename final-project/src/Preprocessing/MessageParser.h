#pragma once

#include <string>
#include <vector>
#include "Message.h"
#include <utility>

class MessageParser {
  public:
    /**
     * Basic constructor.
     * @param filename filename for json we are constructing messages from.
     */
    MessageParser(std::string filename);
  
    /**
     * Gets vector of messages parsed from filename.
     */
    std::vector<Message> getMessages();
  
    /**
     * Gets vector in pairs of format (vector of messages addressed to user, user response).
     * @param user name of user whose messages are the responses.
     */
    std::vector<std::pair<std::vector<Message>, Message>> getMessageResponsePairs(std::string user);

  private:
    /** Vector of messages parsed from filename. */
    std::vector<Message> messages;
};

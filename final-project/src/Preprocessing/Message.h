#pragma once

#include <string>

using std::string;

class Message {

  public:
    Message(const string content, const string sender);
    string getContent();
    string getSender();
    string getMessageId();

  private:
    string content;
    string sender;
    string messageId;

};
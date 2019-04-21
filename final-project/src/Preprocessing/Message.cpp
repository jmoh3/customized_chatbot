#include "Message.h"

#include <string>

using std::string;

Message::Message(const string content, const string sender, const string id) {
  this->content = content;
  this->sender = sender;
  this->messageId = id;
}

string Message::getContent() {
  return content;
}

string Message::getSender() {
  return sender;
}

string Message::getMessageId() {
  return messageId;
}
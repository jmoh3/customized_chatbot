#include "Message.h"

#include <string>

using std::string;

Message::Message(const string content) {
  this->content = content;
}

Message::Message(const string content, const string sender, const string id) {
  this->content = content;
  this->sender = sender;
  this->messageId = id;
}

string Message::getContent() const {
  return content;
}

string Message::getSender() const {
  return sender;
}

string Message::getMessageId() const {
  return messageId;
}

void Message::setResponseId(string id) {
  responseId = id;
}

string Message::getResponseId() const {
  return responseId;
}

void Message::setWordCount(unsigned wordCt) {
  wordCount = wordCt;
}

unsigned Message::getWordCount() const {
  return wordCount;
}
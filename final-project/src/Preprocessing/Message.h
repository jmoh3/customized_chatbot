#pragma once

#include <string>

using std::string;

class Message {

  public:
    /**
     * A basic constructor.
     * @param content content of message.
     * @param sender sender of message.
     * @param id message id.
     */
    Message(const string content, const string sender, const string id);

    /**
     * Getter for message content.
     * 
     * @return content of message.
     */
    string getContent();

    /**
     * Getter for message sender.
     * 
     * @return sender.
     */
    string getSender();

    /**
     * Getter for message id.
     * 
     * @return message id.
     */
    string getMessageId();

  private:
    string content;
    string sender;
    string messageId;

};
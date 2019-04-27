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
    string getContent() const;

    /**
     * Getter for message sender.
     * 
     * @return sender.
     */
    string getSender() const;

    /**
     * Getter for message id.
     * 
     * @return message id.
     */
    string getMessageId() const;

    /**
     * Sets response id.
     * 
     */
    void setResponseId(string id);

    /**
     * Gets response id.
     * 
     * @return response id.
     */
    string getResponseId() const;

    /**
     * Set the word count of the message.
     */
    void setWordCount(unsigned wordCt);

    /**
     * Getter for word count.
     * 
     * @return word count.
     */
    unsigned getWordCount() const;

  private:
    string content;
    string sender;
    string messageId;
    string responseId;

    unsigned wordCount;

};
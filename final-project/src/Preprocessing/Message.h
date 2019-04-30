#pragma once

#include <string>

using std::string;

class Message {

  public:
    /**
     * 
     * @param content content of message.
     */
    Message(const string content);

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
    /** Content of message. */
    string content;
  
    /** Name of user who sent message. */
    string sender;
  
    /** ID of message (just the timestamp in milliseconds). */
    string messageId;
  
    /** ID of response to message. */
    string responseId;

    /** Word count of message. */
    unsigned wordCount;

};

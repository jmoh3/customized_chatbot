#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch/catch.hpp"
#include "../src/Preprocessing/MessageParser.h"
#include "../src/Preprocessing/Message.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

TEST_CASE( "Message getSender works" ) {
  Message message("Test message", "Jackie Oh", "1234");

  REQUIRE(message.getSender() == "Jackie Oh");
}

TEST_CASE( "Message getContent works" ) {
  Message message("Test message", "Jackie Oh", "1234");

  REQUIRE(message.getContent() == "Test message");
}

TEST_CASE( "Message getId works" ) {
  Message message("Test message", "Jackie Oh", "1234");

  REQUIRE(message.getMessageId() == "1234");
}

TEST_CASE( "Message set and getResponseId works" ) {
  Message message("Test message", "Jackie Oh", "1234");
  message.setResponseId("1235");

  REQUIRE(message.getResponseId() == "1235");
}

TEST_CASE( "MessageParser gets correct number of messages" ) {
  MessageParser parser("test_conversation.json");

  REQUIRE(parser.getMessages().size() == 2);
}

TEST_CASE( "MessageParser gets correct message content" ) {
  MessageParser parser("test_conversation.json");

  REQUIRE(parser.getMessages()[0].getSender() == "Jackie Oh");
  REQUIRE(parser.getMessages()[0].getContent() == "how was your day?");
  REQUIRE(parser.getMessages()[0].getMessageId() == "1556763185014");
}

TEST_CASE( "MessageParser gets correct message response pairs" ) {
  MessageParser parser("test_conversation.json");

  REQUIRE(parser.getMessageResponsePairs("Ellen Oh").size() == 1);
  vector<Message> prompts = parser.getMessageResponsePairs("Ellen Oh")[0].first;

  REQUIRE(prompts[0].getContent() == "how was your day?");

  Message response = parser.getMessageResponsePairs("Ellen Oh")[0].second;

  REQUIRE(response.getContent() == "It was pretty good! I made Emily's birthday cake!");
}
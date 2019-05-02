#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch/catch.hpp"
#include "../src/NLP/TfIdfVector.h"
#include "../src/Preprocessing/Message.h"

TEST_CASE( "TfIdfVectors have correct length" ) {
  Message message1("Test message", "Jackie Oh", "1234");
  Message message2("Another test message", "Jackie Oh", "1235");

  vector<Message> testMessages({message1, message2});
  TfIdfVector tfIdfVectorizer(testMessages, 0.0, 1.0);

  REQUIRE(tfIdfVectorizer.getVectorLength() == 3);
}

TEST_CASE( "TfIdfVectorizer gets correct most similar message" ) {
  Message message1("Test message", "Jackie Oh", "1234");
  Message message2("Another test message", "Jackie Oh", "1235");

  vector<Message> testMessages({message1, message2});
  TfIdfVector tfIdfVectorizer(testMessages, 0.0, 1.0);

  Message similarToMessage2("Another test message!", "Jackie Oh", "1235");

  REQUIRE(tfIdfVectorizer.getMostSimilarMessageId(similarToMessage2) == "1235");
}
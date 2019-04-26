#include "MessageParser.h"
#include "Message.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"

#include <iostream>

#include <fstream>
#include <sstream>

using rapidjson::Document;
using std::string;

MessageParser::MessageParser(std::string filename) {
  std::ifstream nameFileout;
  nameFileout.open(filename);

  std::string line;
  std::string json;

  while(std::getline(nameFileout, line)) {
    json += line;
  }

  char cstr[json.size() + 1];
	json.copy(cstr, json.size() + 1);
	cstr[json.size()] = '\0';

  Document d;
  d.Parse(cstr);

  rapidjson::Value& messageArray = d["messages"];
  int numMessages = messageArray.GetArray().Size();

  for (size_t i = numMessages - 1; i > 0; i--) {
    if (messageArray[i].HasMember("content")) {

      string content = messageArray[i]["content"].GetString();
      string sender = messageArray[i]["sender_name"].GetString();
      string id = std::to_string(messageArray[i]["timestamp_ms"].GetUint64());

      Message message(content, sender, id);
      messages.push_back(message);
    }
  }
}

std::vector<Message> MessageParser::getMessages() {
  return messages;
}
#include "Model.h"

#include "TfIdfVector.h"
#include "../Preprocessing/Message.h"
#include "../Preprocessing/MessageParser.h"
#include <iostream>
#include <vector>
#include <map>
#include <utility>

using std::string;
using std::vector;
using std::map;
using std::pair;

int main() {
    string filename = "../../data/messages/inbox/aidansan_6o61zdkx_g/message_1.json";
    string user = "Jackie Oh";

    Model model(filename, user);

    std::cout << model.getResponse("I can go to the meeting") << std::endl;

    return 0;
}
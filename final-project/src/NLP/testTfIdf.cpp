#include "Model.h"

#include "TfIdfVector.h"
#include "../Preprocessing/Message.h"
#include "../Preprocessing/MessageParser.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <utility>

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::getline;

int main() {
    string filename = "../../data/messages/filtered_threads/themegans_1dhgynipdq/message_1.json";

    string user;
    
    std::cout << "Enter the user:\n";

    getline(std::cin, user);

    Model model(filename, user);

    string input = "START";

    while (input != "quit") {
        getline(std::cin, input);
        std::cout << model.getResponse(input) << std::endl;
    }

    return 0;
}
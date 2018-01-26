#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include "Program.h"

typedef std::vector <std::string> stringsVector;

int main(int argc, char ** argv) {
    stringsVector commandsVector;
    std::string::size_type width = 0;

    do {
        static std::string tmp;
        tmp.clear();

        for (char c = 0; !std::cin.eof() && c != '\n'; c = std::cin.get()) {
            if (c == 0) {
                continue;
            }

            tmp.push_back(c);
        }

        if (tmp.size() > width) {
            width = tmp.size();
        }

        commandsVector.push_back(tmp);
    } while (!std::cin.eof());

    char * commands[commandsVector.size()];
    for (stringsVector::size_type i = 0; i < commandsVector.size(); ++i) {
        auto & tmp = commandsVector[i];

        while (tmp.size() < width) {
            tmp.push_back(' ');
        }

        commands[i] = strcpy(new char[width + 1], tmp.c_str());
    }

    Program program(commands, {width, commandsVector.size()});
    program.run();
}

/* MIT License

Copyright (c) 2018 Eridan Domoratskiy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

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

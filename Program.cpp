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

#include "Program.h"

void Program::run() {
    while (running) {
        step();
    }
}

void Program::step() {
    const auto cmd = static_cast <Command> (* currentCommand);

    if (cmd == CONST_C) {
        charMode = !charMode;

    } else if (charMode) {
        stack.push(* currentCommand);

    } else switch (cmd) {
    case DIR_RIGHT:
        direction = RIGHT;
        break;

    case DIR_DOWN:
        direction = DOWN;
        break;

    case DIR_LEFT:
        direction = LEFT;
        break;

    case DIR_UP:
        direction = UP;
        break;

    case DIR_IF_HOR:
        direction = (stack.pop() == 0) ? RIGHT : LEFT;
        break;

    case DIR_IF_VERT:
        direction = (stack.pop() == 0) ? DOWN : UP;
        break;

    case DIR_RAND:
        direction = static_cast <Direction> (rand() % 4);
        break;

    case NOP:
        break;

    case SKIP:
        ++currentCommand;
        break;

    case QUIT:
        running = false;
        break;

    case STACK_DUP:
        stack.duplicateTop();
        break;

    case STACK_SWAP:
        stack.swapTop();
        break;

    case STACK_DROP:
        stack.pop();
        break;

    case CMD_GET: {
        auto y = stack.pop(), x = stack.pop();
        stack.push(commands[y][x]);
        } break;

    case CMD_PUT: {
        auto y = stack.pop(),
             x = stack.pop(),
             cmd = stack.pop();

        commands[y][x] = static_cast <char> (cmd);

        } break;

    case CONST_0:
    case CONST_1:
    case CONST_2:
    case CONST_3:
    case CONST_4:
    case CONST_5:
    case CONST_6:
    case CONST_7:
    case CONST_8:
    case CONST_9:
        stack.push(cmd - CONST_0);
        break;

    case MATH_ADD:
        stack.push(stack.pop() + stack.pop());
        break;

    case MATH_SUB: {
        auto b = stack.pop();
        stack.push(stack.pop() - b);
        } break;

    case MATH_MUL:
        stack.push(stack.pop() * stack.pop());
        break;

    case MATH_DIV: {
        auto b = stack.pop();
        stack.push(stack.pop() / b);
        } break;

    case MATH_MOD: {
        auto b = stack.pop();
        stack.push(stack.pop() % b);
        } break;

    case LOGIC_NOT:
        stack.push((stack.pop() == 0) ? 1 : 0);
        break;

    case LOGIC_COMP:
        stack.push((stack.pop() > stack.pop()) ? 0 : 1);
        break;

    case IO_IN_NUM: {
        Stack::valueType a;
        cin >> a;

        if (!cin.good()) {
            throw std::string("Input is not good");
        }

        stack.push(a);
        } break;

    case IO_IN_CHAR: {
        char a = cin.get();

        if (!cin.good()) {
            throw std::string("Input is not good");
        }

        stack.push(a);
        } break;

    case IO_OUT_NUM:
        cout << stack.pop();
        break;

    case IO_OUT_CHAR:
        cout << static_cast <char> (stack.pop());
        break;

    default: {
        std::string err;

        err += "Unknown operator on line ";
        err += std::to_string(currentCommand.line + 1);
        err += ", column ";
        err += std::to_string(currentCommand.column + 1);

        throw err;
        }
    }

    ++currentCommand;
}

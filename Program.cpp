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
        stack.push(a);
        } break;

    case IO_IN_CHAR: {
        char a;
        cin >> a;
        stack.push(a);
        } break;

    case IO_OUT_NUM:
        cout << stack.pop();
        break;

    case IO_OUT_CHAR:
        cout << static_cast <char> (stack.pop());
        break;

    default:
        exit(-1);
    }

    ++currentCommand;
}

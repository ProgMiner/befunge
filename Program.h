#pragma once

#include <utility>
#include <iostream>

#include "Stack.h"

class Program {
public:
    typedef enum {
        DIR_RIGHT   = '>',
        DIR_DOWN    = 'v',
        DIR_LEFT    = '<',
        DIR_UP      = '^',
        DIR_IF_HOR  = '_',
        DIR_IF_VERT = '|',
        DIR_RAND    = '?',

        NOP  = ' ',
        SKIP = '#',
        QUIT = '@',

        STACK_DUP  = ':',
        STACK_SWAP = '\\',
        STACK_DROP = '$',

        CMD_GET = 'g',
        CMD_PUT = 'p',

        CONST_0 = '0',
        CONST_1 = '1',
        CONST_2 = '2',
        CONST_3 = '3',
        CONST_4 = '4',
        CONST_5 = '5',
        CONST_6 = '6',
        CONST_7 = '7',
        CONST_8 = '8',
        CONST_9 = '9',
        CONST_C = '"',

        MATH_ADD = '+',
        MATH_SUB = '-',
        MATH_MUL = '*',
        MATH_DIV = '/',
        MATH_MOD = '%',

        LOGIC_NOT  = '!',
        LOGIC_COMP = '`',

        IO_IN_NUM   = '&',
        IO_IN_CHAR  = '~',
        IO_OUT_NUM  = '.',
        IO_OUT_CHAR = ','
    } Command;

    typedef enum {
        RIGHT, DOWN, LEFT, UP
    } Direction;

    class Position {
    public:
        Program * program;
        long long line, column;

        explicit Position(Program * program);

        char & operator * ();
        Position & operator ++ ();
        Position & operator -- ();
        Position operator ++ (int);
        Position operator -- (int);
    };

    class Dimensions {
    public:
        typedef Stack::valueType valueType;

        valueType width, height;

        Dimensions(
                valueType width,
                valueType height
        ):
            width(width),
            height(height)
        {}

        Dimensions(std::pair <valueType, valueType> dimensions):
            width(dimensions.first),
            height(dimensions.second)
        {}
    };

    std::istream & cin = std::cin;
    std::ostream & cout = std::cout;

    explicit Program(
            char ** commands,
            Dimensions && dimensions
    ):
        commands(commands),
        dimensions(dimensions),
        currentCommand(this)
    {}

    explicit Program(
            char ** commands,
            const Dimensions & dimensions
    ):
        commands(commands),
        dimensions(dimensions),
        currentCommand(this)
    {}

    void run();
    void step();

private:
    bool running = true;
    bool charMode = false;
    Direction direction = RIGHT;
    Stack stack;

    char ** commands;
    Dimensions dimensions;
    Position currentCommand;
};

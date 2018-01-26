#include "Program.h"

Program::Position::Position(Program * program):
    program(program),
    line(0),
    column(0)
{}

char & Program::Position::operator * () {
    line += program->dimensions.height;
    column += program->dimensions.width;
    line %= program->dimensions.height;
    column %= program->dimensions.width;

    return program->commands[line][column];
}

Program::Position & Program::Position::operator ++ () {
    switch (program->direction) {
    case RIGHT:
        ++column;
        break;
    case DOWN:
        ++line;
        break;
    case LEFT:
        --column;
        break;
    case UP:
        --line;
        break;
    }

    return * this;
}

Program::Position & Program::Position::operator -- () {
    switch (program->direction) {
    case RIGHT:
        --column;
        break;
    case DOWN:
        --line;
        break;
    case LEFT:
        ++column;
        break;
    case UP:
        ++line;
        break;
    }

    return * this;
}

Program::Position Program::Position::operator ++ (int) {
    auto copy = * this;

    ++(* this);

    return copy;
}

Program::Position Program::Position::operator -- (int) {
    auto copy = * this;

    --(* this);

    return copy;
}


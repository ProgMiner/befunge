#pragma once

#include <stack>

class Stack {
public:
    typedef unsigned long valueType;

protected:
    typedef std::stack <valueType> stackType;

    stackType stack;

public:
    typedef typename stackType::reference reference;
    typedef typename stackType::const_reference constReference;

    Stack(): stack() {}

    reference & top();
    constReference & top() const;

    void push(const valueType & value);
    void push(valueType && value);

    reference && pop();

    void duplicateTop();

    void swapTop();

};

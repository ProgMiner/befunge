#include "Stack.h"

Stack::reference & Stack::top() {
    return stack.top();
}

Stack::constReference & Stack::top() const {
    return stack.top();
}

void Stack::push(const valueType & value) {
    stack.push(value);
}

void Stack::push(valueType && value) {
    stack.push(value);
}

Stack::reference && Stack::pop() {
    auto & ret = top();
    stack.pop();

    return ret;
}

void Stack::duplicateTop() {
    push(top());
}

void Stack::swapTop() {
    auto topOld = pop(), topNew = pop();
    push(std::move(topOld));
    push(std::move(topNew));
}


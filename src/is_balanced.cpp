#include "is_balanced.h"

void error(string msg, char c)  {
    cout << c << msg << endl;
}
bool is_balanced(string s) {
    std::stack<char> stack;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{' || c == '<') {
            stack.push(c);
        } else if (c == ')' || c == ']' || c == '}' || c == '>') {
            if (stack.empty()) {
                return false;
            } else if ((c == ')' && stack.top() == '(') ||
                       (c == ']' && stack.top() == '[') ||
                       (c == '}' && stack.top() == '{') ||
                       (c == '>' && stack.top() == '<')) {
                stack.pop();
            } else {
                return false;
            }
        }
    }
    return stack.empty();
}
void test_is_balanced() {
    std::string input;
    std::getline(std::cin, input);
    if (is_balanced(input)) {
        std::cout << "Balanced\n";
    } else {
        std::cout << "Not balanced\n";
    }
}

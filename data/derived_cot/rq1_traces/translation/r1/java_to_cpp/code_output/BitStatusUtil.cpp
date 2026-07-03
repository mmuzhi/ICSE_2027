#include <iostream>
#include <stdexcept>
#include <string>

void check(int arg) {
    if (arg < 0) {
        throw std::invalid_argument(std::to_string(arg) + " must be greater than or equal to 0");
    }
    if (arg % 2 != 0) {
        throw std::invalid_argument(std::to_string(arg) + " not even");
    }
}

template <typename... Args>
void check(int first, Args... rest) {
    check(first);
    check(rest...);
}

int add(int states, int stat) {
    check(states, stat);
    return states | stat;
}

bool has(int states, int stat) {
    check(states, stat);
    return (states & stat) == stat;
}

int remove(int states, int stat) {
    check(states, stat);
    if (has(states, stat)) {
        return states ^ stat;
    }
    return states;
}

int main() {
    std::cout << add(2, 4) << std::endl;
    std::cout << std::boolalpha << has(6, 2) << std::endl;
    std::cout << remove(6, 2) << std::endl;
    try {
        check(2, 3, 4);
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}
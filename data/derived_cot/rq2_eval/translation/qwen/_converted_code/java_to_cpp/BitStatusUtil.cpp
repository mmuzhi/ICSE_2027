#include <iostream>
#include <tuple>
#include <string>
#include <stdexcept>

namespace org::example {

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

template<typename... Args>
void check(Args... args) {
    auto f = [](auto arg) {
        if (arg < 0) {
            throw std::invalid_argument(std::to_string(arg) + " must be greater than or equal to 0");
        }
        if (arg % 2 != 0) {
            throw std::invalid_argument(std::to_string(arg) + " not even");
        }
    };
    std::apply(f, std::make_tuple(args...));
}

} // namespace org::example

int main() {
    std::cout << org::example::add(2, 4) << std::endl;
    std::cout << (org::example::has(6, 2) ? "true" : "false") << std::endl;
    std::cout << org::example::remove(6, 2) << std::endl;
    try {
        org::example::check(2, 3, 4);
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
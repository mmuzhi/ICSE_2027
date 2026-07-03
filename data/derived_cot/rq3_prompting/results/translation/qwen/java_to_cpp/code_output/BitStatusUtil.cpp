#include <iostream>
#include <stdexcept>
#include <string>

namespace org {
    namespace example {

        template<typename... Args>
        void check(Args... args) {
            auto checkOne = [](int value) {
                if (value < 0) {
                    throw std::invalid_argument(std::to_string(value) + " must be greater than or equal to 0");
                }
                if (value % 2 != 0) {
                    throw std::invalid_argument(std::to_string(value) + " not even");
                }
            };

            int values[] = { (int)args... };
            for (int i = 0; i < sizeof...(args); ++i) {
                checkOne(values[i]);
            }
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
            std::cout << (has(6, 2) ? "true" : "false") << std::endl;
            std::cout << remove(6, 2) << std::endl;

            try {
                check(2, 3, 4);
            } catch (const std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }

            return 0;
        }
    }
}
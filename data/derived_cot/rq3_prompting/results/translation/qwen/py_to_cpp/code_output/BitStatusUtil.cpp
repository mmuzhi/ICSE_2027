#include <stdexcept>
#include <string>

class BitStatusUtil {
public:
    static void check(int a, int b) {
        if (a < 0 || b < 0) {
            throw std::invalid_argument(std::to_string(a < 0 ? a : b) + " must be greater than or equal to 0");
        }
        if (a % 2 != 0 || b % 2 != 0) {
            throw std::invalid_argument(std::to_string(a % 2 != 0 ? a : b) + " not even");
        }
    }

    static int add(int states, int stat) {
        check(states, stat);
        return states | stat;
    }

    static bool has(int states, int stat) {
        check(states, stat);
        return (states & stat) == stat;
    }

    static int remove(int states, int stat) {
        check(states, stat);
        if (has(states, stat)) {
            return states ^ stat;
        }
        return states;
    }
};
#include <vector>
#include <stdexcept>
#include <utility>
#include <algorithm>

class AvgPartition {
private:
    std::vector<int> lst;
    int limit;

public:
    AvgPartition(const std::vector<int>& lst, int limit) {
        this->lst = lst;
        this->limit = limit;
    }

    std::pair<int, int> setNum() {
        if (limit <= 0) {
            throw std::runtime_error("AvgPartition: limit must be positive");
        }
        int base = lst.size() / limit;
        int remainder = lst.size() % limit;
        return std::make_pair(base, remainder);
    }

    std::vector<int> get(int index) {
        int base = 0;
        int remainder = 0;
        try {
            std::tie(base, remainder) = setNum();
        } catch (const std::exception& e) {
            return std::vector<int>();
        }

        int start = index * base + (index < remainder ? index : remainder);
        int end = start + base + (index < remainder ? 1 : 0);

        if (start < 0) {
            start = 0;
        }
        if (end > lst.size()) {
            end = lst.size();
        }

        if (start >= lst.size() || start >= end) {
            return std::vector<int>();
        }

        return std::vector<int>(lst.begin() + start, lst.begin() + end);
    }
};
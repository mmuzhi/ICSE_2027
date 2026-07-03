#include <vector>
#include <stdexcept>
#include <algorithm>

class AvgPartition {
private:
    std::vector<int> lst;
    int limit;

public:
    AvgPartition(const std::vector<int>& lst, int limit) : lst(lst), limit(limit) {}

    std::pair<int, int> setNum() {
        if (limit == 0) {
            throw std::invalid_argument("limit cannot be zero");
        }
        int size = lst.size() / limit;
        int remainder = lst.size() % limit;
        return std::make_pair(size, remainder);
    }

    std::vector<int> get(int index) {
        int size, remainder;
        std::pair<int, int> pr = setNum();
        size = pr.first;
        remainder = pr.second;

        if (index < 0 || index >= limit) {
            throw std::out_of_range("index out of range");
        }

        int start = index * size + std::min(index, remainder);
        int end = start + size;
        if (index + 1 <= remainder) {
            end++;
        }

        return std::vector<int>(lst.begin() + start, lst.begin() + end);
    }
};
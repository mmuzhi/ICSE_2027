#include <vector>
#include <utility>
#include <algorithm>

class AvgPartition {
public:
    AvgPartition(const std::vector<int>& lst, int limit)
        : lst(lst), limit(limit) {}

    std::pair<int, int> setNum() const {
        int size = lst.size() / limit;
        int remainder = lst.size() % limit;
        return {size, remainder};
    }

    std::vector<int> get(int index) const {
        auto [size, remainder] = setNum();
        int start = index * size + std::min(index, remainder);
        int end = start + size;
        if (index + 1 <= remainder) {
            end += 1;
        }
        return std::vector<int>(lst.begin() + start, lst.begin() + end);
    }

private:
    std::vector<int> lst;
    int limit;
};
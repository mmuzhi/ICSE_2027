#include <vector>
#include <algorithm>

class AvgPartition {
private:
    const std::vector<int>& lst;
    int limit;

public:
    AvgPartition(const std::vector<int>& lst, int limit) : lst(lst), limit(limit) {}

    std::vector<int> get(int index) {
        int n = lst.size();
        int size = n / limit;
        int remainder = n % limit;

        int start = index * size + std::min(index, remainder);
        int end = start + size;
        if (index < remainder) {
            end++;
        }

        start = std::min(start, n);
        end = std::min(end, n);

        return std::vector<int>(lst.begin() + start, lst.begin() + end);
    }
};
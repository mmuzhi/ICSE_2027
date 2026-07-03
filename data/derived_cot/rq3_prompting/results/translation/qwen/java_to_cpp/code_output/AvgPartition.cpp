#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

class AvgPartition {
private:
    std::vector<int> lst_;
    int limit_;

public:
    AvgPartition(std::vector<int> lst, int limit) : lst_(lst), limit_(limit) {}

    std::pair<int, int> setNum() {
        int size = lst_.size() / limit_;
        int remainder = lst_.size() % limit_;
        return std::make_pair(size, remainder);
    }

    std::vector<int> get(int index) {
        auto nums = setNum();
        int size = nums.first;
        int remainder = nums.second;

        int start;
        if (index < remainder) {
            start = index * size + index;
        } else {
            start = index * size + remainder;
        }

        int end = start + size;
        if (index < remainder) {
            end += 1;
        }

        if (start >= lst_.size() || end > lst_.size()) {
            throw std::out_of_range("Index out of bounds");
        }

        return std::vector<int>(lst_.begin() + start, lst_.begin() + end);
    }

    static void main() {
        std::vector<int> lst = {1, 2, 3, 4};
        AvgPartition a = AvgPartition(lst, 2);
        auto partition0 = a.get(0);
        auto partition1 = a.get(1);

        // Print the first partition
        std::cout << "[";
        for (size_t i = 0; i < partition0.size(); i++) {
            std::cout << partition0[i];
            if (i < partition0.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;

        // Print the second partition
        std::cout << "[";
        for (size_t i = 0; i < partition1.size(); i++) {
            std::cout << partition1[i];
            if (i < partition1.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

int main() {
    AvgPartition::main();
    return 0;
}
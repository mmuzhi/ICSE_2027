#include <vector>
#include <stdexcept>
#include <iostream>

class Tuple {
private:
    std::vector<int> list;
    int totalNum;

public:
    Tuple(std::vector<int> list, int totalNum) : list(std::move(list)), totalNum(totalNum) {}

    const std::vector<int>& getList() const { return list; }
    int getTotalNum() const { return totalNum; }
};

double mrr(const Tuple& data) {
    const std::vector<int>& subList = data.getList();
    int totalNum = data.getTotalNum();

    if (totalNum == 0) {
        return 0.0;
    }

    double mr = 0.0;
    for (int i = 0; i < subList.size(); i++) {
        if (subList[i] == 1) {
            mr = 1.0 / (i + 1);
            break;
        }
    }
    return mr;
}

double mrr(const std::vector<Tuple>& data) {
    if (data.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (const Tuple& tuple : data) {
        const std::vector<int>& subList = tuple.getList();
        int totalNum = tuple.getTotalNum();

        if (totalNum == 0) {
            sum += 0.0;
        } else {
            double mr = 0.0;
            for (int i = 0; i < subList.size(); i++) {
                if (subList[i] == 1) {
                    mr = 1.0 / (i + 1);
                    break;
                }
            }
            sum += mr;
        }
    }
    return sum / data.size();
}

double map(const Tuple& data) {
    const std::vector<int>& subList = data.getList();
    int totalNum = data.getTotalNum();

    if (totalNum == 0) {
        return 0.0;
    }

    double ap = 0.0;
    int count = 0;
    for (int i = 0; i < subList.size(); i++) {
        if (subList[i] == 1) {
            count++;
            ap += count / (i + 1.0);
        }
    }
    return ap / totalNum;
}

double map(const std::vector<Tuple>& data) {
    if (data.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (const Tuple& tuple : data) {
        const std::vector<int>& subList = tuple.getList();
        int totalNum = tuple.getTotalNum();

        if (totalNum == 0) {
            sum += 0.0;
        } else {
            double ap = 0.0;
            int count = 0;
            for (int i = 0; i < subList.size(); i++) {
                if (subList[i] == 1) {
                    count++;
                    ap += count / (i + 1.0);
                }
            }
            sum += ap / totalNum;
        }
    }
    return sum / data.size();
}
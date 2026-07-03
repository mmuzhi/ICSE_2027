#include <vector>
#include <stdexcept>
#include <any>
#include <iostream>

struct Tuple {
    std::vector<int> list;
    int totalNum;
};

double mrr(std::any data) {
    if (data.type() == typeid(Tuple)) {
        const Tuple& tuple = std::any_cast<const Tuple&>(data);
        if (tuple.totalNum == 0) {
            return 0.0;
        }

        double mr = 0.0;
        for (int i = 0; i < tuple.list.size(); i++) {
            if (tuple.list[i] == 1) {
                mr = 1.0 / (i + 1);
                break;
            }
        }
        return mr;
    } else if (data.type() == typeid(std::vector<Tuple>)) {
        const std::vector<Tuple>& tupleList = std::any_cast<const std::vector<Tuple>&>(data);
        if (tupleList.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        for (const auto& tuple : tupleList) {
            sum += mrr(tuple);
        }
        return sum / tupleList.size();
    } else {
        throw std::invalid_argument("the input must be a tuple or a list of tuple");
    }
}

double map(std::any data) {
    if (data.type() == typeid(Tuple)) {
        const Tuple& tuple = std::any_cast<const Tuple&>(data);
        if (tuple.totalNum == 0) {
            return 0.0;
        }

        double ap = 0.0;
        int count = 0;
        for (int i = 0; i < tuple.list.size(); i++) {
            if (tuple.list[i] == 1) {
                count++;
                ap += static_cast<double>(count) / (i + 1.0);
            }
        }
        return ap / tuple.totalNum;
    } else if (data.type() == typeid(std::vector<Tuple>)) {
        const std::vector<Tuple>& tupleList = std::any_cast<const std::vector<Tuple>&>(data);
        if (tupleList.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        for (const auto& tuple : tupleList) {
            sum += map(tuple);
        }
        return sum / tupleList.size();
    } else {
        throw std::invalid_argument("the input must be a tuple or a list of tuple");
    }
}
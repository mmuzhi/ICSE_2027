#include <vector>
#include <tuple>
#include <cmath>
#include <numeric>
#include <stdexcept>

namespace MetricsCalculator {

double compute_mrr(const std::vector<int>& sub_list, int total_num) {
    if (total_num == 0) {
        return 0.0;
    }
    for (size_t i = 0; i < sub_list.size(); ++i) {
        if (sub_list[i] == 1) {
            return 1.0 / (i+1);
        }
    }
    return 0.0;
}

double compute_map(const std::vector<int>& sub_list, int total_num) {
    if (total_num == 0) {
        return 0.0;
    }
    int current_count = 1;
    double sum = 0.0;
    for (size_t i = 0; i < sub_list.size(); ++i) {
        if (sub_list[i] == 1) {
            sum += current_count * (1.0 / (i+1));
            current_count++;
        }
    }
    return sum / total_num;
}

std::pair<double, std::vector<double>> mrr(const std::tuple<std::vector<int>, int>& data) {
    auto sub_list = std::get<0>(data);
    int total_num = std::get<1>(data);
    double mr = compute_mrr(sub_list, total_num);
    return {mr, {mr}};
}

std::pair<double, std::vector<double>> mrr(const std::vector<std::tuple<std::vector<int>, int>>& data) {
    if (data.empty()) {
        return {0.0, {}};
    }
    std::vector<double> results;
    for (const auto& item : data) {
        auto sub_list = std::get<0>(item);
        int total_num = std::get<1>(item);
        results.push_back(compute_mrr(sub_list, total_num));
    }
    double mean = std::accumulate(results.begin(), results.end(), 0.0) / results.size();
    return {mean, results};
}

std::pair<double, std::vector<double>> map(const std::tuple<std::vector<int>, int>& data) {
    auto sub_list = std::get<0>(data);
    int total_num = std::get<1>(data);
    double ap = compute_map(sub_list, total_num);
    return {ap, {ap}};
}

std::pair<double, std::vector<double>> map(const std::vector<std::tuple<std::vector<int>, int>>& data) {
    if (data.empty()) {
        return {0.0, {}};
    }
    std::vector<double> results;
    for (const auto& item : data) {
        auto sub_list = std::get<0>(item);
        int total_num = std::get<1>(item);
        results.push_back(compute_map(sub_list, total_num));
    }
    double mean = std::accumulate(results.begin(), results.end(), 0.0) / results.size();
    return {mean, results};
}

} // namespace MetricsCalculator
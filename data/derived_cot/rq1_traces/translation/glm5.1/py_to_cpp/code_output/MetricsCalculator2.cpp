#include <vector>
#include <utility>
#include <numeric>

class MetricsCalculator2 {
public:
    using DataPoint = std::pair<std::vector<int>, int>;
    using ResultType = std::pair<double, std::vector<double>>;

    MetricsCalculator2() = default;

    static ResultType mrr(const DataPoint& data) {
        const auto& [sub_list, total_num] = data;
        if (total_num == 0) {
            return {0.0, {0.0}};
        }
        double mr = 0.0;
        for (size_t i = 0; i < sub_list.size(); ++i) {
            double val = static_cast<double>(sub_list[i]) / static_cast<double>(i + 1);
            if (val > 0.0) {
                mr = val;
                break;
            }
        }
        return {mr, {mr}};
    }

    static ResultType mrr(const std::vector<DataPoint>& data) {
        if (data.empty()) {
            return {0.0, {0.0}};
        }
        std::vector<double> separate_result;
        for (const auto& [sub_list, total_num] : data) {
            double mr = 0.0;
            if (total_num != 0) {
                for (size_t i = 0; i < sub_list.size(); ++i) {
                    double val = static_cast<double>(sub_list[i]) / static_cast<double>(i + 1);
                    if (val > 0.0) {
                        mr = val;
                        break;
                    }
                }
            }
            separate_result.push_back(mr);
        }
        double mean = std::accumulate(separate_result.begin(), separate_result.end(), 0.0)
                      / static_cast<double>(separate_result.size());
        return {mean, separate_result};
    }

    static ResultType map(const DataPoint& data) {
        const auto& [sub_list, total_num] = data;
        if (total_num == 0) {
            return {0.0, {0.0}};
        }
        std::vector<double> right_ranking_list;
        right_ranking_list.reserve(sub_list.size());
        int count = 1;
        for (int t : sub_list) {
            if (t == 0) {
                right_ranking_list.push_back(0.0);
            } else {
                right_ranking_list.push_back(static_cast<double>(count));
                ++count;
            }
        }
        double ap = 0.0;
        for (size_t i = 0; i < right_ranking_list.size(); ++i) {
            ap += right_ranking_list[i] / static_cast<double>(i + 1);
        }
        ap /= static_cast<double>(total_num);
        return {ap, {ap}};
    }

    static ResultType map(const std::vector<DataPoint>& data) {
        if (data.empty()) {
            return {0.0, {0.0}};
        }
        std::vector<double> separate_result;
        for (const auto& [sub_list, total_num] : data) {
            double ap = 0.0;
            if (total_num != 0) {
                std::vector<double> right_ranking_list;
                right_ranking_list.reserve(sub_list.size());
                int count = 1;
                for (int t : sub_list) {
                    if (t == 0) {
                        right_ranking_list.push_back(0.0);
                    } else {
                        right_ranking_list.push_back(static_cast<double>(count));
                        ++count;
                    }
                }
                for (size_t i = 0; i < right_ranking_list.size(); ++i) {
                    ap += right_ranking_list[i] / static_cast<double>(i + 1);
                }
                ap /= static_cast<double>(total_num);
            }
            separate_result.push_back(ap);
        }
        double mean = std::accumulate(separate_result.begin(), separate_result.end(), 0.0)
                      / static_cast<double>(separate_result.size());
        return {mean, separate_result};
    }
};
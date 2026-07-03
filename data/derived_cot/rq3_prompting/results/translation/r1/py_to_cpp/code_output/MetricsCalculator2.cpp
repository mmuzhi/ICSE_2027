#include <vector>
#include <utility>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <cstddef>

class MetricsCalculator2 {
public:
    // ----- MRR -----
    static std::pair<double, std::vector<double>> mrr(
        const std::pair<std::vector<int>, int>& data) 
    {
        const auto& sub_list = data.first;
        int total_num = data.second;

        if (total_num == 0) {
            return {0.0, {0.0}};
        }

        double mr = 0.0;
        for (size_t i = 0; i < sub_list.size(); ++i) {
            if (sub_list[i] > 0) {
                mr = 1.0 / (i + 1);
                break;
            }
        }
        return {mr, {mr}};
    }

    static std::pair<double, std::vector<double>> mrr(
        const std::vector<std::pair<std::vector<int>, int>>& data) 
    {
        if (data.empty()) {
            return {0.0, {0.0}};
        }

        std::vector<double> separate;
        separate.reserve(data.size());

        for (const auto& item : data) {
            const auto& sub_list = item.first;
            int total_num = item.second;

            double mr = 0.0;
            if (total_num != 0) {
                for (size_t i = 0; i < sub_list.size(); ++i) {
                    if (sub_list[i] > 0) {
                        mr = 1.0 / (i + 1);
                        break;
                    }
                }
            }
            separate.push_back(mr);
        }

        double mean = std::accumulate(separate.begin(), separate.end(), 0.0) 
                      / separate.size();
        return {mean, std::move(separate)};
    }

    // ----- MAP -----
    static std::pair<double, std::vector<double>> map(
        const std::pair<std::vector<int>, int>& data) 
    {
        const auto& sub_list = data.first;
        int total_num = data.second;

        if (total_num == 0) {
            return {0.0, {0.0}};
        }

        double sum_ap = 0.0;
        int count = 1;
        for (size_t i = 0; i < sub_list.size(); ++i) {
            if (sub_list[i] > 0) {
                sum_ap += static_cast<double>(count) / (i + 1);
                ++count;
            }
        }
        double ap = sum_ap / total_num;
        return {ap, {ap}};
    }

    static std::pair<double, std::vector<double>> map(
        const std::vector<std::pair<std::vector<int>, int>>& data) 
    {
        if (data.empty()) {
            return {0.0, {0.0}};
        }

        std::vector<double> separate;
        separate.reserve(data.size());

        for (const auto& item : data) {
            const auto& sub_list = item.first;
            int total_num = item.second;

            double ap = 0.0;
            if (total_num != 0) {
                double sum_ap = 0.0;
                int count = 1;
                for (size_t i = 0; i < sub_list.size(); ++i) {
                    if (sub_list[i] > 0) {
                        sum_ap += static_cast<double>(count) / (i + 1);
                        ++count;
                    }
                }
                ap = sum_ap / total_num;
            }
            separate.push_back(ap);
        }

        double mean = std::accumulate(separate.begin(), separate.end(), 0.0) 
                      / separate.size();
        return {mean, std::move(separate)};
    }
};
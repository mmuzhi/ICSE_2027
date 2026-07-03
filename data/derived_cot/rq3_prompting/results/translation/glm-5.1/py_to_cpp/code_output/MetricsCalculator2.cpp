#include <vector>
#include <utility>
#include <numeric>
#include <stdexcept>

class MetricsCalculator2 {
public:
    MetricsCalculator2() {}

    static std::pair<double, std::vector<double>> mrr(const std::pair<std::vector<int>, int>& data) {
        const auto& sub_list = data.first;
        int total_num = data.second;

        if (total_num == 0) {
            return {0.0, {0.0}};
        }

        double mr = 0.0;
        for (size_t i = 0; i < sub_list.size(); ++i) {
            if (sub_list[i] != 0) {
                mr = 1.0 / (i + 1);
                break;
            }
        }
        return {mr, {mr}};
    }

    static std::pair<double, std::vector<double>> mrr(const std::vector<std::pair<std::vector<int>, int>>& data) {
        if (data.empty()) {
            return {0.0, {0.0}};
        }

        std::vector<double> separate_result;
        for (const auto& item : data) {
            const auto& sub_list = item.first;
            int total_num = item.second;

            double mr = 0.0;
            if (total_num != 0) {
                for (size_t i = 0; i < sub_list.size(); ++i) {
                    if (sub_list[i] != 0) {
                        mr = 1.0 / (i + 1);
                        break;
                    }
                }
            }
            separate_result.push_back(mr);
        }

        double mean = std::accumulate(separate_result.begin(), separate_result.end(), 0.0) / static_cast<double>(separate_result.size());
        return {mean, separate_result};
    }

    static std::pair<double, std::vector<double>> map(const std::pair<std::vector<int>, int>& data) {
        const auto& sub_list = data.first;
        int total_num = data.second;

        if (total_num == 0) {
            return {0.0, {0.0}};
        }

        std::vector<double> right_ranking_list;
        int count = 1;
        for (int t : sub_list) {
            if (t == 0) {
                right_ranking_list.push_back(0);
            } else {
                right_ranking_list.push_back(count);
                count++;
            }
        }

        double ap = 0.0;
        for (size_t i = 0; i < sub_list.size(); ++i) {
            ap += right_ranking_list[i] / (i + 1.0);
        }
        ap /= total_num;

        return {ap, {ap}};
    }

    static std::pair<double, std::vector<double>> map(const std::vector<std::pair<std::vector<int>, int>>& data) {
        if (data.empty()) {
            return {0.0, {0.0}};
        }

        std::vector<double> separate_result;
        for (const auto& item : data) {
            const auto& sub_list = item.first;
            int total_num = item.second;

            double ap = 0.0;
            if (total_num != 0) {
                std::vector<double> right_ranking_list;
                int count = 1;
                for (int t : sub_list) {
                    if (t == 0) {
                        right_ranking_list.push_back(0);
                    } else {
                        right_ranking_list.push_back(count);
                        count++;
                    }
                }

                for (size_t i = 0; i < sub_list.size(); ++i) {
                    ap += right_ranking_list[i] / (i + 1.0);
                }
                ap /= total_num;
            }
            separate_result.push_back(ap);
        }

        double mean = std::accumulate(separate_result.begin(), separate_result.end(), 0.0) / static_cast<double>(separate_result.size());
        return {mean, separate_result};
    }
};
#include <vector>
#include <utility>
#include <iostream>
#include <cmath>

class MetricsCalculator2 {
public:
    static std::pair<double, std::vector<double>> calculateMRR(const std::pair<std::vector<int>, int>& data) {
        int total_num = data.second;
        if (total_num == 0) {
            return std::make_pair(0.0, std::vector<double>{0.0});
        }

        const std::vector<int>& sub_list = data.first;
        int n = sub_list.size();
        std::vector<double> ranking_array(n);
        for (int i = 0; i < n; i++) {
            ranking_array[i] = 1.0 / (i + 1);
        }

        double mr = 0.0;
        for (int i = 0; i < n; i++) {
            if (sub_list[i] == 1) {
                mr = ranking_array[i];
                break;
            }
        }

        return std::make_pair(mr, std::vector<double>{mr});
    }

    static std::pair<double, std::vector<double>> calculateMRR(const std::vector<std::pair<std::vector<int>, int>>& data) {
        std::vector<double> separate_result;
        for (const auto& example : data) {
            auto [mr, _] = calculateMRR(example);
            separate_result.push_back(mr);
        }

        if (separate_result.empty()) {
            return std::make_pair(0.0, std::vector<double>{0.0});
        }

        double sum = 0.0;
        for (double val : separate_result) {
            sum += val;
        }
        double mean = sum / separate_result.size();

        return std::make_pair(mean, separate_result);
    }

    static std::pair<double, std::vector<double>> calculateMAP(const std::pair<std::vector<int>, int>& data) {
        int total_num = data.second;
        if (total_num == 0) {
            return std::make_pair(0.0, std::vector<double>{0.0});
        }

        const std::vector<int>& sub_list = data.first;
        int n = sub_list.size();
        std::vector<double> ranking_array(n);
        for (int i = 0; i < n; i++) {
            ranking_array[i] = 1.0 / (i + 1);
        }

        int count = 1;
        std::vector<double> right_ranking_list(n, 0.0);
        for (int i = 0; i < n; i++) {
            if (sub_list[i] == 1) {
                right_ranking_list[i] = count;
                count++;
            }
        }

        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            sum += right_ranking_list[i] * ranking_array[i];
        }

        double ap = sum / total_num;
        return std::make_pair(ap, std::vector<double>{ap});
    }

    static std::pair<double, std::vector<double>> calculateMAP(const std::vector<std::pair<std::vector<int>, int>>& data) {
        std::vector<double> separate_result;
        for (const auto& example : data) {
            auto [ap, _] = calculateMAP(example);
            separate_result.push_back(ap);
        }

        if (separate_result.empty()) {
            return std::make_pair(0.0, std::vector<double>{0.0});
        }

        double sum = 0.0;
        for (double val : separate_result) {
            sum += val;
        }
        double mean = sum / separate_result.size();

        return std::make_pair(mean, separate_result);
    }
};
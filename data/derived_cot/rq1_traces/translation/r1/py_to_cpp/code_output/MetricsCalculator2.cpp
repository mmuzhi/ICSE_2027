#include <vector>
#include <utility>
#include <iostream>
using namespace std;

class MetricsCalculator2 {
private:
    static double compute_mrr(const vector<int>& sub_list, int total_num) {
        if (total_num == 0) {
            return 0.0;
        }
        for (int i = 0; i < sub_list.size(); i++) {
            if (sub_list[i] == 1) {
                return 1.0 / (i + 1);
            }
        }
        return 0.0;
    }

    static double compute_map(const vector<int>& sub_list, int total_num) {
        if (total_num == 0) {
            return 0.0;
        }
        double sum = 0.0;
        int count = 1;
        for (int i = 0; i < sub_list.size(); i++) {
            if (sub_list[i] == 1) {
                sum += count * (1.0 / (i + 1));
                count++;
            }
        }
        return sum / total_num;
    }

public:
    static pair<double, vector<double>> mrr(const pair<vector<int>, int>& single_data) {
        vector<pair<vector<int>, int>> dataList;
        dataList.push_back(single_data);
        return mrr(dataList);
    }

    static pair<double, vector<double>> mrr(const vector<pair<vector<int>, int>>& data) {
        if (data.empty()) {
            return make_pair(0.0, vector<double>{0.0});
        }
        vector<double> separate_results;
        for (const auto& item : data) {
            separate_results.push_back(compute_mrr(item.first, item.second));
        }
        double mean = 0.0;
        for (double val : separate_results) {
            mean += val;
        }
        mean /= separate_results.size();
        return make_pair(mean, separate_results);
    }

    static pair<double, vector<double>> map(const pair<vector<int>, int>& single_data) {
        vector<pair<vector<int>, int>> dataList;
        dataList.push_back(single_data);
        return map(dataList);
    }

    static pair<double, vector<double>> map(const vector<pair<vector<int>, int>>& data) {
        if (data.empty()) {
            return make_pair(0.0, vector<double>{0.0});
        }
        vector<double> separate_results;
        for (const auto& item : data) {
            separate_results.push_back(compute_map(item.first, item.second));
        }
        double mean = 0.0;
        for (double val : separate_results) {
            mean += val;
        }
        mean /= separate_results.size();
        return make_pair(mean, separate_results);
    }
};
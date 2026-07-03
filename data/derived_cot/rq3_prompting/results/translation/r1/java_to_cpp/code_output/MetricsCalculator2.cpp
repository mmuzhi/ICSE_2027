#include <vector>
#include <stdexcept>
#include <variant>
#include <numeric>

class MetricsCalculator2 {
public:
    struct Tuple {
        std::vector<int> list;
        int totalNum;

        Tuple(std::vector<int> list, int totalNum)
            : list(std::move(list)), totalNum(totalNum) {}

        const std::vector<int>& getList() const { return list; }
        int getTotalNum() const { return totalNum; }
    };

    static double mrr(const std::variant<Tuple, std::vector<Tuple>>& data) {
        if (std::holds_alternative<Tuple>(data)) {
            const Tuple& tuple = std::get<Tuple>(data);
            const std::vector<int>& subList = tuple.getList();
            int totalNum = tuple.getTotalNum();

            if (totalNum == 0) {
                return 0.0;
            }

            double mr = 0.0;
            for (size_t i = 0; i < subList.size(); ++i) {
                if (subList[i] == 1) {
                    mr = 1.0 / (i + 1);
                    break;
                }
            }
            return mr;
        } else if (std::holds_alternative<std::vector<Tuple>>(data)) {
            const std::vector<Tuple>& tupleList = std::get<std::vector<Tuple>>(data);
            std::vector<double> separateResult;

            for (const Tuple& tuple : tupleList) {
                const std::vector<int>& subList = tuple.getList();
                int totalNum = tuple.getTotalNum();

                if (totalNum == 0) {
                    separateResult.push_back(0.0);
                } else {
                    double mr = 0.0;
                    for (size_t i = 0; i < subList.size(); ++i) {
                        if (subList[i] == 1) {
                            mr = 1.0 / (i + 1);
                            break;
                        }
                    }
                    separateResult.push_back(mr);
                }
            }

            if (separateResult.empty()) {
                return 0.0;
            }
            double sum = std::accumulate(separateResult.begin(), separateResult.end(), 0.0);
            return sum / separateResult.size();
        } else {
            throw std::invalid_argument(
                "the input must be a tuple([0,...,1,...],int) or a iteration of list of tuple");
        }
    }

    static double map(const std::variant<Tuple, std::vector<Tuple>>& data) {
        if (std::holds_alternative<Tuple>(data)) {
            const Tuple& tuple = std::get<Tuple>(data);
            const std::vector<int>& subList = tuple.getList();
            int totalNum = tuple.getTotalNum();

            if (totalNum == 0) {
                return 0.0;
            }

            double ap = 0.0;
            int count = 0;
            for (size_t i = 0; i < subList.size(); ++i) {
                if (subList[i] == 1) {
                    count++;
                    ap += count / (i + 1.0);
                }
            }
            return ap / totalNum;
        } else if (std::holds_alternative<std::vector<Tuple>>(data)) {
            const std::vector<Tuple>& tupleList = std::get<std::vector<Tuple>>(data);
            std::vector<double> separateResult;

            for (const Tuple& tuple : tupleList) {
                const std::vector<int>& subList = tuple.getList();
                int totalNum = tuple.getTotalNum();

                if (totalNum == 0) {
                    separateResult.push_back(0.0);
                } else {
                    double ap = 0.0;
                    int count = 0;
                    for (size_t i = 0; i < subList.size(); ++i) {
                        if (subList[i] == 1) {
                            count++;
                            ap += count / (i + 1.0);
                        }
                    }
                    separateResult.push_back(ap / totalNum);
                }
            }

            if (separateResult.empty()) {
                return 0.0;
            }
            double sum = std::accumulate(separateResult.begin(), separateResult.end(), 0.0);
            return sum / separateResult.size();
        } else {
            throw std::invalid_argument(
                "the input must be a tuple([0,...,1,...],int) or a iteration of list of tuple");
        }
    }
};
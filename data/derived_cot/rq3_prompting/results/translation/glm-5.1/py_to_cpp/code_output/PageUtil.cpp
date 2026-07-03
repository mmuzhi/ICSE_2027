#include <vector>
#include <string>
#include <optional>
#include <sstream>
#include <type_traits>
#include <algorithm>
#include <stdexcept>

template<typename T>
std::string item_to_string(const T& item) {
    if constexpr (std::is_same_v<T, std::string>) {
        return item;
    } else if constexpr (std::is_arithmetic_v<T>) {
        return std::to_string(item);
    } else {
        std::ostringstream oss;
        oss << item;
        return oss.str();
    }
}

template<typename T>
struct PageInfo {
    int current_page = 0;
    int per_page = 0;
    int total_pages = 0;
    int total_items = 0;
    bool has_previous = false;
    bool has_next = false;
    std::vector<T> data;
};

template<typename T>
struct SearchInfo {
    std::string keyword;
    int total_results = 0;
    int total_pages = 0;
    std::vector<T> results;
};

template<typename T>
class PageUtil {
private:
    std::vector<T> data_;
    int page_size_;
    int total_items_;
    int total_pages_;

public:
    PageUtil(std::vector<T> data, int page_size)
        : data_(std::move(data)), page_size_(page_size), total_items_(0), total_pages_(0) {
        if (page_size_ <= 0) {
            throw std::invalid_argument("page_size must be positive");
        }
        total_items_ = static_cast<int>(data_.size());
        total_pages_ = (total_items_ + page_size_ - 1) / page_size_;
    }

    std::vector<T> get_page(int page_number) const {
        if (page_number < 1 || page_number > total_pages_) {
            return {};
        }
        int start_index = (page_number - 1) * page_size_;
        int end_index = std::min(start_index + page_size_, total_items_);
        return std::vector<T>(data_.begin() + start_index, data_.begin() + end_index);
    }

    std::optional<PageInfo<T>> get_page_info(int page_number) const {
        if (page_number < 1 || page_number > total_pages_) {
            return std::nullopt;
        }
        int start_index = (page_number - 1) * page_size_;
        int end_index = std::min(start_index + page_size_, total_items_);
        std::vector<T> page_data(data_.begin() + start_index, data_.begin() + end_index);

        PageInfo<T> info;
        info.current_page = page_number;
        info.per_page = page_size_;
        info.total_pages = total_pages_;
        info.total_items = total_items_;
        info.has_previous = page_number > 1;
        info.has_next = page_number < total_pages_;
        info.data = std::move(page_data);
        return info;
    }

    SearchInfo<T> search(const std::string& keyword) const {
        std::vector<T> results;
        for (const auto& item : data_) {
            if (item_to_string(item).find(keyword) != std::string::npos) {
                results.push_back(item);
            }
        }
        int num_results = static_cast<int>(results.size());
        int num_pages = (num_results + page_size_ - 1) / page_size_;

        SearchInfo<T> info;
        info.keyword = keyword;
        info.total_results = num_results;
        info.total_pages = num_pages;
        info.results = std::move(results);
        return info;
    }
};
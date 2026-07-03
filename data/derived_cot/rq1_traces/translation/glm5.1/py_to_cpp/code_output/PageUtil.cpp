#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <optional>

template <typename T>
class PageUtil {
public:
    struct PageInfo {
        int current_page;
        int per_page;
        int total_pages;
        int total_items;
        bool has_previous;
        bool has_next;
        std::vector<T> data;
    };

    struct SearchInfo {
        std::string keyword;
        int total_results;
        int total_pages;
        std::vector<T> results;
    };

private:
    std::vector<T> data_;
    int page_size_;
    int total_items_;
    int total_pages_;

    static std::string item_to_string(const T& item) {
        std::ostringstream oss;
        oss << item;
        return oss.str();
    }

public:
    PageUtil(const std::vector<T>& data, int page_size)
        : data_(data), page_size_(page_size),
          total_items_(static_cast<int>(data.size())),
          total_pages_(data.empty() ? 0 : (total_items_ + page_size_ - 1) / page_size_) {}

    std::vector<T> get_page(int page_number) {
        if (page_number < 1 || page_number > total_pages_) {
            return {};
        }
        int start_index = (page_number - 1) * page_size_;
        int end_index = std::min(start_index + page_size_, total_items_);
        return std::vector<T>(data_.begin() + start_index, data_.begin() + end_index);
    }

    std::optional<PageInfo> get_page_info(int page_number) {
        if (page_number < 1 || page_number > total_pages_) {
            return std::nullopt;
        }
        int start_index = (page_number - 1) * page_size_;
        int end_index = std::min(start_index + page_size_, total_items_);
        std::vector<T> page_data(data_.begin() + start_index, data_.begin() + end_index);

        return PageInfo{
            page_number,
            page_size_,
            total_pages_,
            total_items_,
            page_number > 1,
            page_number < total_pages_,
            std::move(page_data)
        };
    }

    SearchInfo search(const std::string& keyword) {
        std::vector<T> results;
        for (const auto& item : data_) {
            if (item_to_string(item).find(keyword) != std::string::npos) {
                results.push_back(item);
            }
        }
        int num_results = static_cast<int>(results.size());
        int num_pages = (num_results == 0) ? 0 : (num_results + page_size_ - 1) / page_size_;

        return SearchInfo{
            keyword,
            num_results,
            num_pages,
            std::move(results)
        };
    }
};
#include <vector>
#include <string>
#include <algorithm>
#include <sstream> // for to_string fallback if needed, but we'll use std::to_string with int

struct PageInfo {
    int current_page;
    int per_page;
    int total_pages;
    int total_items;
    bool has_previous;
    bool has_next;
    std::vector<int> data;
};

struct SearchInfo {
    std::string keyword;
    int total_results;
    int total_pages;
    std::vector<int> results;
};

class PageUtil {
private:
    std::vector<int> data;
    int page_size;
    int total_items;
    int total_pages;

public:
    PageUtil(const std::vector<int>& data, int page_size)
        : data(data), page_size(page_size) {
        total_items = static_cast<int>(data.size());
        total_pages = (total_items + page_size - 1) / page_size;
    }

    std::vector<int> get_page(int page_number) const {
        if (page_number < 1 || page_number > total_pages) {
            return {};
        }
        int start = (page_number - 1) * page_size;
        int end = std::min(start + page_size, total_items);
        return std::vector<int>(data.begin() + start, data.begin() + end);
    }

    PageInfo get_page_info(int page_number) const {
        if (page_number < 1 || page_number > total_pages) {
            return {}; // empty PageInfo
        }
        int start = (page_number - 1) * page_size;
        int end = std::min(start + page_size, total_items);
        std::vector<int> page_data(data.begin() + start, data.begin() + end);

        PageInfo info;
        info.current_page = page_number;
        info.per_page = page_size;
        info.total_pages = total_pages;
        info.total_items = total_items;
        info.has_previous = page_number > 1;
        info.has_next = page_number < total_pages;
        info.data = std::move(page_data);
        return info;
    }

    SearchInfo search(const std::string& keyword) const {
        std::vector<int> results;
        for (int item : data) {
            if (std::to_string(item).find(keyword) != std::string::npos) {
                results.push_back(item);
            }
        }
        int num_results = static_cast<int>(results.size());
        int num_pages = (num_results + page_size - 1) / page_size;

        SearchInfo info;
        info.keyword = keyword;
        info.total_results = num_results;
        info.total_pages = num_pages;
        info.results = std::move(results);
        return info;
    }
};
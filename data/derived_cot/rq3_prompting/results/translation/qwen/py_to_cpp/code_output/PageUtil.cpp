#include <vector>
#include <string>
#include <algorithm>

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
    PageUtil(const std::vector<int>& data, int page_size) {
        this->data = data;
        this->page_size = page_size;
        this->total_items = data.size();
        this->total_pages = (total_items + page_size - 1) / page_size;
    }

    std::vector<int> get_page(int page_number) {
        if (page_number < 1 || page_number > total_pages) {
            return {};
        }
        int start_index = (page_number - 1) * page_size;
        int end_index = start_index + page_size;
        if (end_index > total_items) {
            end_index = total_items;
        }
        std::vector<int> page_data(data.begin() + start_index, data.begin() + end_index);
        return page_data;
    }

    PageInfo get_page_info(int page_number) {
        if (page_number < 1 || page_number > total_pages) {
            return {};
        }
        int start_index = (page_number - 1) * page_size;
        int end_index = start_index + page_size;
        if (end_index > total_items) {
            end_index = total_items;
        }
        std::vector<int> page_data(data.begin() + start_index, data.begin() + end_index);

        PageInfo info = {
            page_number,
            page_size,
            total_pages,
            total_items,
            page_number > 1,
            page_number < total_pages,
            page_data
        };
        return info;
    }

    SearchInfo search(const std::string& keyword) {
        std::vector<int> results;
        for (int item : data) {
            if (std::to_string(item).find(keyword) != std::string::npos) {
                results.push_back(item);
            }
        }
        int num_results = results.size();
        int num_pages = (num_results + page_size - 1) / page_size;

        SearchInfo info = {
            keyword,
            num_results,
            num_pages,
            results
        };
        return info;
    }
};
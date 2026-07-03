#include <vector>
#include <map>
#include <variant>
#include <sstream>
#include <algorithm>
#include <string>

template <typename T>
class PageUtil {
public:
    using ValueType = std::variant<int, bool, std::string, std::vector<T>>;

private:
    std::vector<T> data;
    int page_size;
    int total_items;
    int total_pages;

public:
    PageUtil(const std::vector<T>& data, int page_size)
        : data(data), page_size(page_size), total_items(static_cast<int>(data.size())),
          total_pages((total_items + page_size - 1) / page_size) {}

    std::vector<T> get_page(int page_number) const {
        if (page_number < 1 || page_number > total_pages) {
            return std::vector<T>();
        }
        int start_index = (page_number - 1) * page_size;
        int end_index = std::min(start_index + page_size, total_items);
        return std::vector<T>(data.begin() + start_index, data.begin() + end_index);
    }

    std::map<std::string, ValueType> get_page_info(int page_number) const {
        std::map<std::string, ValueType> page_info;
        if (page_number < 1 || page_number > total_pages) {
            return page_info;
        }

        int start_index = (page_number - 1) * page_size;
        int end_index = std::min(start_index + page_size, total_items);
        std::vector<T> page_data(data.begin() + start_index, data.begin() + end_index);

        page_info["current_page"] = page_number;
        page_info["per_page"] = page_size;
        page_info["total_pages"] = total_pages;
        page_info["total_items"] = total_items;
        page_info["has_previous"] = (page_number > 1);
        page_info["has_next"] = (page_number < total_pages);
        page_info["data"] = page_data;

        return page_info;
    }

    std::map<std::string, ValueType> search(const std::string& keyword) const {
        std::vector<T> results;
        for (const T& item : data) {
            std::ostringstream oss;
            oss << item;
            if (oss.str().find(keyword) != std::string::npos) {
                results.push_back(item);
            }
        }

        int num_results = static_cast<int>(results.size());
        int num_pages = (num_results + page_size - 1) / page_size;

        std::map<std::string, ValueType> search_info;
        search_info["keyword"] = keyword;
        search_info["total_results"] = num_results;
        search_info["total_pages"] = num_pages;
        search_info["results"] = results;

        return search_info;
    }
};
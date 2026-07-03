#include <vector>
#include <map>
#include <string>
#include <sstream>

class PageUtil {
private:
    std::vector<int> data;
    int page_size;
    int total_items;
    int total_pages;

public:
    PageUtil(const std::vector<int>& data, int page_size) : 
        data(data), 
        page_size(page_size), 
        total_items(data.size()),
        total_pages((total_items + page_size - 1) / page_size) {}

    std::vector<int> get_page(int page_number) {
        if (page_number < 1 || page_number > total_pages) {
            return std::vector<int>();
        }
        int start_index = (page_number - 1) * page_size;
        int end_index = start_index + page_size;
        if (end_index > total_items) {
            end_index = total_items;
        }
        return std::vector<int>(data.begin() + start_index, data.begin() + end_index);
    }

    std::map<std::string, std::string> get_page_info(int page_number) {
        if (page_number < 1 || page_number > total_pages) {
            return std::map<std::string, std::string>();
        }
        int start_index = (page_number - 1) * page_size;
        int end_index = start_index + page_size;
        if (end_index > total_items) {
            end_index = total_items;
        }
        std::vector<int> page_data(data.begin() + start_index, data.begin() + end_index);

        std::map<std::string, std::string> page_info;
        page_info["current_page"] = std::to_string(page_number);
        page_info["per_page"] = std::to_string(page_size);
        page_info["total_pages"] = std::to_string(total_pages);
        page_info["total_items"] = std::to_string(total_items);
        page_info["has_previous"] = (page_number > 1) ? "True" : "False";
        page_info["has_next"] = (page_number < total_pages) ? "True" : "False";

        std::stringstream ss;
        ss << "[";
        for (int i = 0; i < page_data.size(); i++) {
            if (i > 0) {
                ss << ", ";
            }
            ss << page_data[i];
        }
        ss << "]";
        page_info["data"] = ss.str();

        return page_info;
    }

    std::map<std::string, std::string> search(const std::string& keyword) {
        std::vector<int> results;
        for (int item : data) {
            if (std::to_string(item).find(keyword) != std::string::npos) {
                results.push_back(item);
            }
        }
        int num_results = results.size();
        int num_pages = (num_results + page_size - 1) / page_size;

        std::map<std::string, std::string> search_info;
        search_info["keyword"] = keyword;
        search_info["total_results"] = std::to_string(num_results);
        search_info["total_pages"] = std::to_string(num_pages);

        std::stringstream ss;
        ss << "[";
        for (int i = 0; i < results.size(); i++) {
            if (i > 0) {
                ss << ", ";
            }
            ss << results[i];
        }
        ss << "]";
        search_info["results"] = ss.str();

        return search_info;
    }
};
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class UrlPath {
private:
    std::vector<std::string> segments;
    bool with_end_tag;

    static std::string fix_path(const std::string& path) {
        if (path.empty()) {
            return "";
        }

        size_t start = 0;
        while (start < path.size() && path[start] == '/') {
            start++;
        }

        size_t end = path.size() - 1;
        while (end > start && path[end] == '/') {
            end--;
        }

        if (start > end) {
            return "";
        }

        return path.substr(start, end - start + 1);
    }

public:
    UrlPath() : segments(), with_end_tag(false) {}

    void add(const std::string& segment) {
        segments.push_back(fix_path(segment));
    }

    void parse(const std::string& path, const std::string& charset) {
        if (path.empty()) {
            return;
        }

        bool had_end_tag = false;
        if (!path.empty() && path.back() == '/') {
            had_end_tag = true;
        }

        std::string fixed_path = fix_path(path);
        segments.clear();

        if (fixed_path.empty()) {
            this->with_end_tag = had_end_tag;
            return;
        }

        std::istringstream iss(fixed_path);
        std::string seg;
        while (std::getline(iss, seg, '/')) {
            std::string decoded_seg = seg;
            // Percent decoding is not directly available in standard C++, so we'll use a placeholder
            // In practice, you would implement percent decoding here
            segments.push_back(decoded_seg);
        }

        this->with_end_tag = had_end_tag;
    }

    // Static method for fixing paths remains unchanged
};
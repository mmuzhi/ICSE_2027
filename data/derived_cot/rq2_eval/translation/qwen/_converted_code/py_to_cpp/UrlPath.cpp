#include <vector>
#include <string>
#include <cctype>
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

    static std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0, end = 0;
        while ((end = s.find(delimiter, start)) != std::string::npos) {
            tokens.push_back(s.substr(start, end - start));
            start = end + 1;
        }
        tokens.push_back(s.substr(start));
        return tokens;
    }

    static std::string unquote(const std::string& s, const std::string& encoding) {
        std::string result;
        result.reserve(s.size());
        for (size_t i = 0; i < s.size(); ) {
            if (s[i] == '%') {
                if (i + 2 >= s.size()) {
                    result += s[i];
                    i++;
                    continue;
                }
                unsigned char value = 0;
                if (std::isxdigit(static_cast<unsigned char>(s[i+1])) && std::isxdigit(static_cast<unsigned char>(s[i+2]))) {
                    value = (s[i+1] == 'x' ? 16 : 10);
                    unsigned char high = std::isdigit(static_cast<unsigned char>(s[i+1])) ? s[i+1] - '0' : std::toupper(s[i+1]) - 'A' + 10;
                    unsigned char low = std::isdigit(static_cast<unsigned char>(s[i+2])) ? s[i+2] - '0' : std::toupper(s[i+2]) - 'A' + 10;
                    value = high * 16 + low;
                    result += value;
                    i += 3;
                    continue;
                }
            }
            result += s[i];
            i++;
        }
        return result;
    }

public:
    UrlPath() : segments(), with_end_tag(false) {}

    void add(const std::string& segment) {
        segments.push_back(fix_path(segment));
    }

    void parse(const std::string& path, const std::string& charset) {
        if (!path.empty()) {
            if (path.back() == '/') {
                with_end_tag = true;
            }
            std::string fixed_path = fix_path(path);
            if (!fixed_path.empty()) {
                std::vector<std::string> split_path = split(fixed_path, '/');
                for (const std::string& seg : split_path) {
                    segments.push_back(unquote(seg, charset));
                }
            }
        }
    }

    static std::string fix_path_static(const std::string& path) {
        return fix_path(path);
    }
};
#include <vector>
#include <string>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>

class UrlPath {
private:
    std::vector<std::string> segments;
    bool withEndTag;

    static std::string urlDecode(const std::string& str, const std::string& charset) {
        std::string result;
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '+') {
                result += ' ';
            } else if (str[i] == '%') {
                if (i + 2 >= str.length()) {
                    throw std::invalid_argument("Incomplete percent encoding");
                }
                std::string hexStr = str.substr(i + 1, 2);
                if (!std::isxdigit(hexStr[0]) || !std::isxdigit(hexStr[1])) {
                    throw std::invalid_argument("Invalid hex digits in percent encoding");
                }
                unsigned char byte = static_cast<unsigned char>(std::stoul(hexStr, nullptr, 16));
                result += static_cast<char>(byte);
                i += 2;
            } else {
                result += str[i];
            }
        }
        return result;
    }

public:
    UrlPath() : segments(), withEndTag(false) {}

    void add(const std::string& segment) {
        segments.push_back(fixPath(segment));
    }

    void parse(const std::string& path, const std::string& charset) {
        if (path.empty()) {
            return;
        }

        if (path.back() == '/') {
            withEndTag = true;
        }

        std::string fixed = fix_path(path);
        if (fixed.empty()) {
            return;
        }

        std::vector<std::string> parts;
        size_t start = 0;
        while (start < fixed.length()) {
            size_t end = fixed.find('/', start);
            if (end == std::string::npos) {
                parts.push_back(fixed.substr(start));
                break;
            } else {
                parts.push_back(fixed.substr(start, end - start));
                start = end + 1;
            }
        }

        for (const std::string& part : parts) {
            try {
                std::string decodedSeg = urlDecode(part, charset);
                segments.push_back(decodedSeg);
            } catch (const std::exception& e) {
                std::cerr << "Exception: " << e.what() << std::endl;
            }
        }
    }

    static std::string fix_path(std::string path) {
        if (path.empty()) {
            return "";
        }

        size_t start_index = path.find_first_not_of(" \t\n\r");
        size_t end_index = path.find_last_not_of(" \t\n\r");
        if (start_index == std::string::npos) {
            return "";
        }
        path = path.substr(start_index, end_index - start_index + 1);

        start_index = path.find_first_not_of('/');
        if (start_index == std::string::npos) {
            return "";
        }

        end_index = path.find_last_not_of('/');
        if (end_index == std::string::npos) {
            return path.substr(start_index);
        }
        return path.substr(start_index, end_index - start_index + 1);
    }

    std::vector<std::string> getSegments() const {
        return segments;
    }

    bool with_end_tag() const {
        return withEndTag;
    }
};
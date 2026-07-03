#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <exception>
#include <cctype>
#include <cstdlib>
#include <algorithm>

class UrlPath {
private:
    std::vector<std::string> segments;
    bool withEndTag;

    std::string fix_path(const std::string& path) {
        if (path.empty()) {
            return "";
        }

        size_t start_index = path.find_first_not_of(" \t\n\r\f\v");
        size_t end_index = path.find_last_not_of(" \t\n\r\f\v");
        if (start_index == std::string::npos) {
            return "";
        }

        std::string trimmed = path.substr(start_index, end_index - start_index + 1);
        std::regex pattern("^/+|/+$");
        trimmed = std::regex_replace(trimmed, pattern, "");
        return trimmed;
    }

    std::string decode(const std::string& seg, const std::string& charset) {
        std::string temp = seg;
        size_t pos = 0;
        while ((pos = temp.find('+', pos)) != std::string::npos) {
            temp.replace(pos, 1, "%20");
            pos += 3;
        }

        std::string result;
        for (size_t i = 0; i < temp.size(); ) {
            if (temp[i] == '%') {
                if (i + 2 < temp.size()) {
                    std::string hex = std::string("") + temp[i+1] + temp[i+2];
                    try {
                        int value = std::stoi(hex, nullptr, 16);
                        if (value >= 0 && value <= 255) {
                            result += static_cast<char>(value);
                            i += 3;
                        } else {
                            result += '%';
                            i += 1;
                        }
                    } catch (...) {
                        result += '%';
                        i += 1;
                    }
                } else {
                    result += '%';
                    i += 1;
                }
            } else {
                result += temp[i];
                i += 1;
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
        if (!path.empty()) {
            if (!path.empty() && path.back() == '/') {
                withEndTag = true;
            }

            std::string fixed_path = fix_path(path);
            if (!fixed_path.empty()) {
                std::vector<std::string> segments;
                std::sregex_token_iterator iter(fixed_path.begin(), fixed_path.end(), "/", 0);
                std::sregex_token_iterator end;
                for (std::smatch match; iter != end; ++iter) {
                    if (iter->str().empty()) continue;
                    std::string seg = *iter;
                    try {
                        std::string decodedSeg = decode(seg, charset);
                        segments.push_back(decodedSeg);
                    } catch (...) {
                        std::cerr << "Error decoding segment: " << seg << std::endl;
                    }
                }
                this->segments = segments;
            }
        }
    }

    std::vector<std::string> getSegments() const {
        return segments;
    }

    bool with_end_tag() const {
        return withEndTag;
    }
};
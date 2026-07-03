#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <iomanip>

class UrlPath {
private:
    std::vector<std::string> segments;
    bool with_end_tag;

    static std::string percent_decode(const std::string& input) {
        std::string output;
        for (size_t i = 0; i < input.length(); ++i) {
            if (input[i] == '%') {
                if (i + 2 < input.length()) {
                    char hex1 = input[i+1];
                    char hex2 = input[i+2];
                    if (std::isxdigit(hex1) && std::isxdigit(hex2)) {
                        std::string hexStr = std::string(1, hex1) + hex2;
                        int byte_value;
                        std::istringstream hexStream(hexStr);
                        hexStream >> std::hex >> byte_value;
                        output += static_cast<char>(byte_value);
                        i += 2;
                    } else {
                        output += input[i];
                    }
                } else {
                    output += input[i];
                }
            } else {
                output += input[i];
            }
        }
        return output;
    }

    static std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    UrlPath() : with_end_tag(false) {}

    void add(const std::string& segment) {
        std::string fixed = fix_path(segment);
        segments.push_back(fixed);
    }

    void parse(const std::string& path, const std::string& charset) {
        if (!path.empty() && path.back() == '/') {
            with_end_tag = true;
        }

        std::string fixed = fix_path(path);
        if (fixed.empty()) {
            return;
        }

        std::string lower_charset = charset;
        std::transform(lower_charset.begin(), lower_charset.end(), lower_charset.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        if (lower_charset != "utf-8") {
            throw std::runtime_error("Unsupported charset: only UTF-8 is supported");
        }

        std::vector<std::string> parts = split(fixed, '/');
        for (const std::string& seg : parts) {
            std::string decoded_seg = percent_decode(seg);
            segments.push_back(decoded_seg);
        }
    }

    static std::string fix_path(const std::string& path) {
        if (path.empty()) {
            return "";
        }
        size_t start = path.find_first_not_of('/');
        if (start == std::string::npos) {
            return "";
        }
        size_t end = path.find_last_not_of('/');
        return path.substr(start, end - start + 1);
    }
};
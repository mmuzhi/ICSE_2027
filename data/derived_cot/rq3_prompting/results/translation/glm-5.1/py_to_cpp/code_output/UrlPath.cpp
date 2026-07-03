#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <cstdlib>

class UrlPath {
public:
    std::vector<std::string> segments;
    bool with_end_tag;

    UrlPath() : segments(), with_end_tag(false) {}

    void add(const std::string& segment) {
        segments.push_back(fix_path(segment));
    }

    void parse(const std::string& path, const std::string& charset) {
        if (!path.empty()) {
            if (path.back() == '/') {
                with_end_tag = true;
            }

            std::string fixed = fix_path(path);
            if (!fixed.empty()) {
                std::vector<std::string> parts = split_string(fixed, '/');
                for (const auto& seg : parts) {
                    std::string decoded_seg = url_decode(seg, charset);
                    segments.push_back(decoded_seg);
                }
            }
        }
    }

    static std::string fix_path(const std::string& path) {
        if (path.empty()) {
            return "";
        }

        size_t start = 0;
        size_t end = path.size();

        while (start < end && path[start] == '/') {
            start++;
        }
        while (end > start && path[end - 1] == '/') {
            end--;
        }

        return path.substr(start, end - start);
    }

private:
    static std::vector<std::string> split_string(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static std::string url_decode(const std::string& s, const std::string& /*charset*/) {
        std::string result;
        result.reserve(s.size());
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '%' && i + 2 < s.size() &&
                std::isxdigit(static_cast<unsigned char>(s[i + 1])) &&
                std::isxdigit(static_cast<unsigned char>(s[i + 2]))) {
                char hex[3] = {s[i + 1], s[i + 2], '\0'};
                char decoded = static_cast<char>(std::strtol(hex, nullptr, 16));
                result += decoded;
                i += 2;
            } else {
                result += s[i];
            }
        }
        // For full charset fidelity (e.g. latin-1 → UTF-8), iconv would be needed.
        // For UTF-8 and ASCII-compatible encodings, the raw decoded bytes are correct.
        return result;
    }
};
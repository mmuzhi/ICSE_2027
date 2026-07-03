#include <string>
#include <vector>
#include <sstream>
#include <cstdlib> // for strtol

class UrlPath {
public:
    std::vector<std::string> segments;
    bool with_end_tag;

    UrlPath() : with_end_tag(false) {}

    void add(const std::string& segment) {
        segments.push_back(fix_path(segment));
    }

    void parse(const std::string& path, const std::string& charset) {
        if (path.empty()) return;
        if (path.back() == '/') {
            with_end_tag = true;
        }
        std::string fixed = fix_path(path);
        if (fixed.empty()) return;

        std::istringstream ss(fixed);
        std::string seg;
        while (std::getline(ss, seg, '/')) {
            std::string decoded = url_decode(seg);
            segments.push_back(decoded);
        }
    }

    static std::string fix_path(const std::string& path) {
        if (path.empty()) return "";
        size_t start = 0;
        while (start < path.size() && path[start] == '/') ++start;
        size_t end = path.size();
        while (end > start && path[end - 1] == '/') --end;
        if (start >= end) return "";
        return path.substr(start, end - start);
    }

private:
    static std::string url_decode(const std::string& encoded) {
        std::string decoded;
        for (size_t i = 0; i < encoded.size(); ++i) {
            if (encoded[i] == '%' && i + 2 < encoded.size()) {
                char hex[3] = { encoded[i + 1], encoded[i + 2], '\0' };
                char* end;
                long value = std::strtol(hex, &end, 16);
                if (*end == '\0') {
                    decoded += static_cast<char>(value);
                    i += 2;
                    continue;
                }
            }
            decoded += encoded[i];
        }
        return decoded;
    }
};
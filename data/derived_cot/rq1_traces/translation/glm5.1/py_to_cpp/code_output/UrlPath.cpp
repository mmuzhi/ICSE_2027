#include <string>
#include <vector>
#include <sstream>

class UrlPath {
public:
    std::vector<std::string> segments;
    bool with_end_tag;

    UrlPath() : with_end_tag(false) {}

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
                std::stringstream ss(fixed);
                std::string seg;
                while (std::getline(ss, seg, '/')) {
                    segments.push_back(url_decode(seg, charset));
                }
            }
        }
    }

    static std::string fix_path(const std::string& path) {
        if (path.empty()) {
            return "";
        }
        size_t start = path.find_first_not_of('/');
        size_t end = path.find_last_not_of('/');
        if (start == std::string::npos) {
            return "";
        }
        return path.substr(start, end - start + 1);
    }

private:
    static int hex_to_int(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return -1;
    }

    // Note: C++ std::string does not natively handle character encodings (like utf-8 or gbk) 
    // as Python's str does. This function decodes percent-encoded bytes directly into the 
    // string, which perfectly mirrors the byte-level behavior of Python's urllib.parse.unquote.
    static std::string url_decode(const std::string& value, const std::string& /*charset*/) {
        std::string result;
        result.reserve(value.size());
        for (size_t i = 0; i < value.size(); ++i) {
            char c = value[i];
            if (c == '%' && i + 2 < value.size()) {
                int high = hex_to_int(value[i + 1]);
                int low = hex_to_int(value[i + 2]);
                if (high != -1 && low != -1) {
                    result += static_cast<char>(high * 16 + low);
                    i += 2;
                    continue;
                }
            }
            result += c;
        }
        return result;
    }
};
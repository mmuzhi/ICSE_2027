#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <regex>
#include <iostream>
#include <stdexcept>

class UrlPath {
private:
    std::vector<std::string> segments;
    bool withEndTag;

    // Helper: URL-decode a percent-encoded string (UTF-8 only).
    static std::string urlDecode(const std::string& encoded, const std::string& charset) {
        if (charset != "UTF-8") {
            throw std::runtime_error("Unsupported encoding: " + charset);
        }
        std::string result;
        for (size_t i = 0; i < encoded.size(); ++i) {
            if (encoded[i] == '%' && i + 2 < encoded.size()) {
                int high = std::stoi(encoded.substr(i + 1, 2), nullptr, 16);
                result += static_cast<char>(high);
                i += 2;
            } else {
                result += encoded[i];
            }
        }
        return result;
    }

public:
    UrlPath() : withEndTag(false) {}

    void add(const std::string& segment) {
        segments.push_back(fixPath(segment));
    }

    void parse(const std::string& path, const std::string& charset) {
        if (path.empty()) return;
        std::string p = path;
        if (p.back() == '/') {
            withEndTag = true;
        }
        p = fixPath(p);
        if (p.empty()) return;

        // Split on '/'
        std::string seg;
        for (char ch : p) {
            if (ch == '/') {
                try {
                    segments.push_back(urlDecode(seg, charset));
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                seg.clear();
            } else {
                seg += ch;
            }
        }
        // Last segment
        try {
            segments.push_back(urlDecode(seg, charset));
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    static std::string fixPath(const std::string& path) {
        if (path.empty()) return "";

        // Strip leading/trailing whitespace
        std::string s = path;
        auto notSpace = [](unsigned char ch) { return !std::isspace(ch); };
        auto left = std::find_if(s.begin(), s.end(), notSpace);
        auto right = std::find_if(s.rbegin(), s.rend(), notSpace).base();
        s = (left < right) ? std::string(left, right) : "";

        // Remove leading and trailing slashes
        s = std::regex_replace(s, std::regex("^/+|/+$"), "");
        return s;
    }

    const std::vector<std::string>& getSegments() const {
        return segments;
    }

    bool isWithEndTag() const {
        return withEndTag;
    }
};
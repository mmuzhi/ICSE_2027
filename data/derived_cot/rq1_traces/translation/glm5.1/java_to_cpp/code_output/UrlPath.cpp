#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <exception>

class UrlPath {
private:
    std::vector<std::string> segments;
    bool withEndTag;

    // Helper for URL decoding
    static std::string urlDecode(const std::string& str, const std::string& charset) {
        // Note: The charset parameter is ignored here. C++ standard library does not 
        // provide built-in charset conversion. Bytes are decoded directly into the string.
        (void)charset;

        std::string result;
        result.reserve(str.size());
        for (size_t i = 0; i < str.size(); ++i) {
            if (str[i] == '%') {
                if (i + 2 < str.size()) {
                    std::string hex = str.substr(i + 1, 2);
                    try {
                        int val = std::stoi(hex, nullptr, 16);
                        result += static_cast<char>(val);
                        i += 2;
                    } catch (const std::exception&) {
                        throw std::invalid_argument("Invalid URL encoding: " + hex);
                    }
                } else {
                    throw std::invalid_argument("Invalid URL encoding");
                }
            } else if (str[i] == '+') {
                result += ' ';
            } else {
                result += str[i];
            }
        }
        return result;
    }

    // Helper for splitting strings
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
    UrlPath() : withEndTag(false) {}

    void add(const std::string& segment) {
        segments.push_back(fixPath(segment));
    }

    void parse(const std::string& path, const std::string& charset) {
        if (!path.empty()) {
            if (path.back() == '/') {
                withEndTag = true;
            }

            std::string fixedPath = fixPath(path);
            if (!fixedPath.empty()) {
                std::vector<std::string> splitPath = split(fixedPath, '/');
                for (const std::string& seg : splitPath) {
                    try {
                        std::string decodedSeg = urlDecode(seg, charset);
                        segments.push_back(decodedSeg);
                    } catch (const std::exception& e) {
                        std::cerr << e.what() << std::endl;
                    }
                }
            }
        }
    }

    static std::string fixPath(const std::string& path) {
        if (path.empty()) {
            return "";
        }

        // Equivalent to String.strip()
        size_t start = path.find_first_not_of(" \t\n\r\f\v");
        if (start == std::string::npos) {
            return "";
        }
        size_t end = path.find_last_not_of(" \t\n\r\f\v");
        std::string segmentStr = path.substr(start, end - start + 1);

        // Equivalent to replaceAll("^/+|/+$", "")
        size_t first_non_slash = segmentStr.find_first_not_of('/');
        if (first_non_slash == std::string::npos) {
            return ""; // String consists entirely of slashes
        }
        size_t last_non_slash = segmentStr.find_last_not_of('/');
        segmentStr = segmentStr.substr(first_non_slash, last_non_slash - first_non_slash + 1);

        return segmentStr;
    }

    // Returns a mutable reference to match Java's List<> mutability behavior
    std::vector<std::string>& getSegments() {
        return segments;
    }

    bool isWithEndTag() const {
        return withEndTag;
    }
};
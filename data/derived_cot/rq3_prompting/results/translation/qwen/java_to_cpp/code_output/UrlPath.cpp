#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <locale>
#include <sstream>

class UrlPath {
private:
    std::vector<std::string> segments;
    bool withEndTag;

    // Helper function to trim whitespace from a string
    static std::string trim(const std::string& str) {
        if (str.empty()) return str;
        auto start = str.find_first_not_of(" \t\n\r\f\v");
        auto end = str.find_last_not_of(" \t\n\r\f\v");
        if (start == std::string::npos) return "";
        return str.substr(start, end - start + 1);
    }

    // Helper function to check if a character is a hex digit
    static bool isHex(char c) {
        return (c >= '0' && c <= '9') ||
               (c >= 'A' && c <= 'F') ||
               (c >= 'a' && c <= 'f');
    }

    // Static method to fix the path by removing leading/trailing slashes and whitespace
    static std::string fixPath(const std::string& path) {
        if (path.empty()) {
            return "";
        }

        std::string trimmed = trim(path);
        if (trimmed.empty()) {
            return "";
        }

        // Remove leading slashes
        size_t start = 0;
        while (start < trimmed.size() && trimmed[start] == '/') {
            start++;
        }

        // Remove trailing slashes
        size_t end = trimmed.size() - 1;
        while (end > start && trimmed[end] == '/') {
            end--;
        }

        if (start >= trimmed.size()) {
            return "";
        }

        return trimmed.substr(start, end - start + 1);
    }

public:
    UrlPath() : segments(), withEndTag(false) {}

    // Add a segment to the path after fixing it
    void add(const std::string& segment) {
        segments.push_back(fixPath(segment));
    }

    // Parse a URL path string with the given charset
    void parse(const std::string& path, const std::string& charset) {
        if (path.empty()) {
            return;
        }

        // Check if the path ends with a '/'
        if (!path.empty() && path.back() == '/') {
            withEndTag = true;
        }

        std::string fixedPath = fixPath(path);
        if (fixedPath.empty()) {
            return;
        }

        // Split the fixedPath by '/'
        std::istringstream iss(fixedPath);
        std::string segment;
        while (std::getline(iss, segment, '/')) {
            if (segment.empty()) {
                continue;
            }

            try {
                // URL decode the segment using the specified charset
                auto decoded = URLDecode(segment, charset);
                segments.push_back(decoded);
            } catch (const std::exception& e) {
                // Print the exception and continue processing
                std::cerr << "URLDecode error: " << e.what() << std::endl;
            }
        }
    }

    // Get the list of segments
    std::vector<std::string> getSegments() const {
        return segments;
    }

    // Check if the path ends with a '/'
    bool isWithEndTag() const {
        return withEndTag;
    }
};

// Helper function to URL decode a string using the specified charset
std::string URLDecode(const std::string& str, const std::string& charset) {
    if (str.empty()) {
        return str;
    }

    // Convert the string to bytes using the specified charset
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::wstring wideStr = converter.from_bytes(str);
    std::vector<char> bytes;
    bytes.reserve(str.size());

    // Iterate over the string and decode percent-encoded sequences
    for (size_t i = 0; i < str.size(); ) {
        if (str[i] == '%' && i + 2 < str.size()) {
            char high = str[i+1];
            char low = str[i+2];
            if (isHex(high) && isHex(low)) {
                std::string hexStr = std::string(1, high) + std::string(1, low);
                int value = std::stoi(hexStr, nullptr, 16);
                bytes.push_back(static_cast<char>(value));
                i += 3;
                continue;
            }
        }
        bytes.push_back(str[i]);
        i++;
    }

    // Convert the bytes back to a string using the specified charset
    return converter.to_bytes(std::string(bytes.begin(), bytes.end()));
}
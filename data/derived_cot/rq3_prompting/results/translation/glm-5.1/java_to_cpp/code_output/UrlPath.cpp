#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cctype>
#include <stdexcept>

class UrlPath {
private:
    std::vector<std::string> segments;
    bool withEndTag;

    static std::string urlDecode(const std::string& str, const std::string& charset) {
        (void)charset; // charset is ignored as standard C++ does not have built-in charset conversion
        std::string result;
        result.reserve(str.size());
        for (size_t i = 0; i < str.size(); ++i) {
            if (str[i] == '+') {
                result += ' ';
            } else if (str[i] == '%') {
                if (i + 2 < str.size() && 
                    std::isxdigit(static_cast<unsigned char>(str[i + 1])) && 
                    std::isxdigit(static_cast<unsigned char>(str[i + 2]))) {
                    std::string hexStr = str.substr(i + 1, 2);
                    int hex;
                    std::istringstream iss(hexStr);
                    iss >> std::hex >> hex;
                    result += static_cast<char>(hex);
                    i += 2;
                } else {
                    throw std::runtime_error("Illegal hex characters in escape (%) pattern");
                }
            } else {
                result += str[i];
            }
        }
        return result;
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

        std::string res = path;
        // strip whitespace
        res.erase(res.begin(), std::find_if(res.begin(), res.end(), [](unsigned char ch) { return !std::isspace(ch); }));
        res.erase(std::find_if(res.rbegin(), res.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), res.end());

        // replaceAll("^/+|/+$", "")
        res.erase(res.begin(), std::find_if(res.begin(), res.end(), [](char ch) { return ch != '/'; }));
        res.erase(std::find_if(res.rbegin(), res.rend(), [](char ch) { return ch != '/'; }).base(), res.end());

        return res;
    }

    std::vector<std::string> getSegments() const {
        return segments;
    }

    bool isWithEndTag() const {
        return withEndTag;
    }
};
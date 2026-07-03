#include <optional>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

class URLHandler {
private:
    std::string url;

    static std::vector<std::string> split_java_style(const std::string& s, char delim) {
        std::vector<std::string> tokens;
        if (s.empty()) {
            return tokens;
        }
        size_t start = 0;
        size_t end = s.find(delim);
        while (end != std::string::npos) {
            tokens.push_back(s.substr(start, end - start));
            start = end + 1;
            end = s.find(delim, start);
        }
        tokens.push_back(s.substr(start));

        while (!tokens.empty() && tokens.back().empty()) {
            tokens.pop_back();
        }
        return tokens;
    }

public:
    URLHandler(const std::string& url) : url(url) {}

    std::optional<std::string> getScheme() const {
        size_t pos = url.find("://");
        if (pos != std::string::npos) {
            return url.substr(0, pos);
        }
        return std::nullopt;
    }

    std::optional<std::string> getHost() const {
        size_t schemeEnd = url.find("://");
        if (schemeEnd == std::string::npos) {
            return std::nullopt;
        }
        std::string withoutScheme = url.substr(schemeEnd + 3);
        size_t hostEnd = withoutScheme.find('/');
        if (hostEnd != std::string::npos) {
            return withoutScheme.substr(0, hostEnd);
        } else {
            return withoutScheme;
        }
    }

    std::optional<std::string> getPath() const {
        size_t schemeEnd = url.find("://");
        if (schemeEnd == std::string::npos) {
            return std::nullopt;
        }
        std::string withoutScheme = url.substr(schemeEnd + 3);
        size_t hostEnd = withoutScheme.find('/');
        if (hostEnd != std::string::npos) {
            return withoutScheme.substr(hostEnd);
        }
        return std::nullopt;
    }

    std::optional<std::unordered_map<std::string, std::string>> getQueryParams() const {
        size_t queryStart = url.find('?');
        if (queryStart == std::string::npos) {
            return std::nullopt;
        }

        size_t fragmentStart = url.find('#');
        std::string queryString;
        if (fragmentStart != std::string::npos) {
            if (fragmentStart < queryStart + 1) {
                throw std::out_of_range("String index out of range: fragmentStart < queryStart+1");
            }
            queryString = url.substr(queryStart + 1, fragmentStart - queryStart - 1);
        } else {
            queryString = url.substr(queryStart + 1);
        }

        std::unordered_map<std::string, std::string> params;
        if (!queryString.empty()) {
            std::vector<std::string> paramPairs = split_java_style(queryString, '&');
            for (const std::string& pair : paramPairs) {
                std::vector<std::string> keyValue = split_java_style(pair, '=');
                if (keyValue.size() == 2) {
                    params[keyValue[0]] = keyValue[1];
                }
            }
        }
        return params;
    }

    std::optional<std::string> getFragment() const {
        size_t fragmentStart = url.find('#');
        if (fragmentStart != std::string::npos) {
            return url.substr(fragmentStart + 1);
        }
        return std::nullopt;
    }
};
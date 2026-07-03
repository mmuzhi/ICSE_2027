#include <string>
#include <unordered_map>
#include <optional>
#include <vector>
#include <stdexcept>

class URLHandler {
private:
    std::string url;

    // Mimics Java's String.split(regex) for a single character delimiter.
    // Leading empty strings are kept, consecutive delimiters produce empty strings,
    // trailing empty strings are removed. For an empty input string, returns [""].
    static std::vector<std::string> splitJava(const std::string& s, char delim) {
        std::vector<std::string> result;
        size_t start = 0;
        for (size_t i = 0; i <= s.size(); ++i) {
            if (i == s.size() || s[i] == delim) {
                result.push_back(s.substr(start, i - start));
                start = i + 1;
            }
        }
        // Remove trailing empty strings, but keep at least one element.
        while (result.size() > 1 && result.back().empty()) {
            result.pop_back();
        }
        return result;
    }

public:
    URLHandler(const std::string& url) : url(url) {}

    std::optional<std::string> getScheme() const {
        size_t schemeEnd = url.find("://");
        if (schemeEnd != std::string::npos) {
            return url.substr(0, schemeEnd);
        }
        return std::nullopt;
    }

    std::optional<std::string> getHost() const {
        size_t schemeEnd = url.find("://");
        if (schemeEnd == std::string::npos) {
            return std::nullopt;
        }
        std::string urlWithoutScheme = url.substr(schemeEnd + 3);
        size_t hostEnd = urlWithoutScheme.find('/');
        if (hostEnd != std::string::npos) {
            return urlWithoutScheme.substr(0, hostEnd);
        }
        return urlWithoutScheme;
    }

    std::optional<std::string> getPath() const {
        size_t schemeEnd = url.find("://");
        if (schemeEnd == std::string::npos) {
            return std::nullopt;
        }
        std::string urlWithoutScheme = url.substr(schemeEnd + 3);
        size_t hostEnd = urlWithoutScheme.find('/');
        if (hostEnd != std::string::npos) {
            return urlWithoutScheme.substr(hostEnd);
        }
        return std::nullopt;
    }

    std::optional<std::unordered_map<std::string, std::string>> getQueryParams() const {
        size_t queryStart = url.find('?');
        size_t fragmentStart = url.find('#');
        if (queryStart == std::string::npos) {
            return std::nullopt;
        }
        size_t endPos = (fragmentStart != std::string::npos) ? fragmentStart : url.length();
        // The length passed to substr may be negative if fragmentStart is before queryStart.
        // This will throw std::out_of_range, matching Java's StringIndexOutOfBoundsException.
        std::string queryString = url.substr(queryStart + 1, endPos - queryStart - 1);
        std::unordered_map<std::string, std::string> params;
        if (!queryString.empty()) {
            std::vector<std::string> paramPairs = splitJava(queryString, '&');
            for (const auto& pair : paramPairs) {
                std::vector<std::string> keyValue = splitJava(pair, '=');
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
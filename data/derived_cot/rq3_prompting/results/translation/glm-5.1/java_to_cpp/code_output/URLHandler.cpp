#pragma once

#include <string>
#include <optional>
#include <unordered_map>
#include <vector>

class URLHandler {
private:
    std::string url;

    static std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end;
        while ((end = s.find(delimiter, start)) != std::string::npos) {
            tokens.push_back(s.substr(start, end - start));
            start = end + delimiter.length();
        }
        tokens.push_back(s.substr(start));
        while (!tokens.empty() && tokens.back().empty()) {
            tokens.pop_back();
        }
        return tokens;
    }

public:
    URLHandler(const std::string& url) : url(url) {}

    std::optional<std::string> getScheme() {
        size_t schemeEnd = url.find("://");
        if (schemeEnd != std::string::npos) {
            return url.substr(0, schemeEnd);
        }
        return std::nullopt;
    }

    std::optional<std::string> getHost() {
        size_t schemeEnd = url.find("://");
        if (schemeEnd != std::string::npos) {
            std::string urlWithoutScheme = url.substr(schemeEnd + 3);
            size_t hostEnd = urlWithoutScheme.find("/");
            if (hostEnd != std::string::npos) {
                return urlWithoutScheme.substr(0, hostEnd);
            }
            return urlWithoutScheme;
        }
        return std::nullopt;
    }

    std::optional<std::string> getPath() {
        size_t schemeEnd = url.find("://");
        if (schemeEnd != std::string::npos) {
            std::string urlWithoutScheme = url.substr(schemeEnd + 3);
            size_t hostEnd = urlWithoutScheme.find("/");
            if (hostEnd != std::string::npos) {
                return urlWithoutScheme.substr(hostEnd);
            }
        }
        return std::nullopt;
    }

    std::optional<std::unordered_map<std::string, std::string>> getQueryParams() {
        size_t queryStart = url.find("?");
        size_t fragmentStart = url.find("#");
        if (queryStart != std::string::npos) {
            std::string queryString = url.substr(
                queryStart + 1,
                fragmentStart != std::string::npos
                    ? fragmentStart - queryStart - 1
                    : std::string::npos
            );
            std::unordered_map<std::string, std::string> params;
            if (!queryString.empty()) {
                std::vector<std::string> paramPairs = split(queryString, "&");
                for (const std::string& pair : paramPairs) {
                    std::vector<std::string> keyValue = split(pair, "=");
                    if (keyValue.size() == 2) {
                        params[keyValue[0]] = keyValue[1];
                    }
                }
            }
            return params;
        }
        return std::nullopt;
    }

    std::optional<std::string> getFragment() {
        size_t fragmentStart = url.find("#");
        if (fragmentStart != std::string::npos) {
            return url.substr(fragmentStart + 1);
        }
        return std::nullopt;
    }
};
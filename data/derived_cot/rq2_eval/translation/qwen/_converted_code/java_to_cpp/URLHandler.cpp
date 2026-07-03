#include <string>
#include <map>
#include <optional>
#include <sstream>
#include <vector>
#include <algorithm>

class URLHandler {
private:
    std::string url;

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
            size_t hostEnd = urlWithoutScheme.find('/');
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
            size_t hostEnd = urlWithoutScheme.find('/');
            if (hostEnd != std::string::npos) {
                return urlWithoutScheme.substr(hostEnd);
            }
        }
        return std::nullopt;
    }

    std::optional<std::map<std::string, std::string>> getQueryParams() {
        size_t queryStart = url.find('?');
        size_t fragmentStart = url.find('#');
        if (queryStart != std::string::npos) {
            std::string queryString;
            if (fragmentStart != std::string::npos) {
                queryString = url.substr(queryStart + 1, fragmentStart - (queryStart + 1));
            } else {
                queryString = url.substr(queryStart + 1);
            }

            if (!queryString.empty()) {
                std::map<std::string, std::string> params;
                std::istringstream ss(queryString);
                std::string pair;
                while (std::getline(ss, pair, '&')) {
                    size_t equalPos = pair.find('=');
                    if (equalPos != std::string::npos) {
                        std::string key = pair.substr(0, equalPos);
                        std::string value = pair.substr(equalPos + 1);
                        params[key] = value;
                    }
                }
                return params;
            }
        }
        return std::nullopt;
    }

    std::optional<std::string> getFragment() {
        size_t fragmentStart = url.find('#');
        if (fragmentStart != std::string::npos) {
            return url.substr(fragmentStart + 1);
        }
        return std::nullopt;
    }
};
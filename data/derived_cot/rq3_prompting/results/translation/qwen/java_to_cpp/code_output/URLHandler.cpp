#include <string>
#include <unordered_map>
#include <optional>
#include <vector>

class URLHandler {
private:
    std::string url;

public:
    URLHandler(const std::string& url) : url(url) {}

    std::optional<std::string> getScheme() {
        auto schemeEnd = url.find("://");
        if (schemeEnd != std::string::npos) {
            return url.substr(0, schemeEnd);
        }
        return std::nullopt;
    }

    std::optional<std::string> getHost() {
        auto schemeEnd = url.find("://");
        if (schemeEnd != std::string::npos) {
            auto urlWithoutScheme = url.substr(schemeEnd + 3);
            auto hostEnd = urlWithoutScheme.find('/');
            if (hostEnd != std::string::npos) {
                return urlWithoutScheme.substr(0, hostEnd);
            }
            return urlWithoutScheme;
        }
        return std::nullopt;
    }

    std::optional<std::string> getPath() {
        auto schemeEnd = url.find("://");
        if (schemeEnd != std::string::npos) {
            auto urlWithoutScheme = url.substr(schemeEnd + 3);
            auto hostEnd = urlWithoutScheme.find('/');
            if (hostEnd != std::string::npos) {
                return urlWithoutScheme.substr(hostEnd);
            }
        }
        return std::nullopt;
    }

    std::optional<std::unordered_map<std::string, std::string>> getQueryParams() {
        auto queryStart = url.find('?');
        auto fragmentStart = url.find('#');
        if (queryStart != std::string::npos) {
            auto queryEnd = (fragmentStart != std::string::npos) ? fragmentStart : url.length();
            auto queryString = url.substr(queryStart + 1, queryEnd - (queryStart + 1));

            std::unordered_map<std::string, std::string> params;
            if (!queryString.empty()) {
                std::vector<std::string> paramPairs;
                auto start = 0;
                auto pos = 0;
                while ((pos = queryString.find('&', start)) != std::string::npos) {
                    paramPairs.push_back(queryString.substr(start, pos - start));
                    start = pos + 1;
                }
                paramPairs.push_back(queryString.substr(start));

                for (auto& pair : paramPairs) {
                    auto eqPos = pair.find('=');
                    if (eqPos != std::string::npos) {
                        std::string key = pair.substr(0, eqPos);
                        std::string value = pair.substr(eqPos + 1);
                        params[key] = value;
                    }
                }
            }
            return params;
        }
        return std::nullopt;
    }

    std::optional<std::string> getFragment() {
        auto fragmentStart = url.find('#');
        if (fragmentStart != std::string::npos) {
            return url.substr(fragmentStart + 1);
        }
        return std::nullopt;
    }
};
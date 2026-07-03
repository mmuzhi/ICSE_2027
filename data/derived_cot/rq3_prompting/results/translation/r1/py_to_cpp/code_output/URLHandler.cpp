#include <string>
#include <optional>
#include <map>
#include <vector>
#include <sstream>

class URLHandler {
private:
    std::string url;

public:
    URLHandler(const std::string& url) : url(url) {}

    std::optional<std::string> get_scheme() const {
        size_t scheme_end = url.find("://");
        if (scheme_end != std::string::npos) {
            return url.substr(0, scheme_end);
        }
        return std::nullopt;
    }

    std::optional<std::string> get_host() const {
        size_t scheme_end = url.find("://");
        if (scheme_end == std::string::npos) {
            return std::nullopt;
        }
        std::string without_scheme = url.substr(scheme_end + 3);
        size_t host_end = without_scheme.find('/');
        if (host_end != std::string::npos) {
            return without_scheme.substr(0, host_end);
        }
        return without_scheme;
    }

    std::optional<std::string> get_path() const {
        size_t scheme_end = url.find("://");
        if (scheme_end == std::string::npos) {
            return std::nullopt;
        }
        std::string without_scheme = url.substr(scheme_end + 3);
        size_t host_end = without_scheme.find('/');
        if (host_end != std::string::npos) {
            return without_scheme.substr(host_end);
        }
        return std::nullopt;
    }

    std::optional<std::map<std::string, std::string>> get_query_params() const {
        size_t query_start = url.find('?');
        size_t fragment_start = url.find('#');
        if (query_start == std::string::npos) {
            return std::nullopt;
        }
        std::string query_string;
        if (fragment_start != std::string::npos) {
            query_string = url.substr(query_start + 1, fragment_start - query_start - 1);
        } else {
            query_string = url.substr(query_start + 1);
        }
        std::map<std::string, std::string> params;
        if (!query_string.empty()) {
            std::vector<std::string> pairs;
            std::stringstream ss(query_string);
            std::string item;
            while (std::getline(ss, item, '&')) {
                size_t eq = item.find('=');
                if (eq != std::string::npos) {
                    std::string key = item.substr(0, eq);
                    std::string value = item.substr(eq + 1);
                    params[key] = value;
                }
            }
        }
        return params;
    }

    std::optional<std::string> get_fragment() const {
        size_t fragment_start = url.find('#');
        if (fragment_start != std::string::npos) {
            return url.substr(fragment_start + 1);
        }
        return std::nullopt;
    }
};
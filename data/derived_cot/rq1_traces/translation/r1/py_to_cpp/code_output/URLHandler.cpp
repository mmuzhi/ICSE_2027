#include <optional>
#include <string>
#include <map>
#include <vector>
#include <sstream>

class URLHandler {
private:
    std::string url;

    static std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::istringstream iss(s);
        std::string token;
        while (std::getline(iss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    URLHandler(const std::string& url) : url(url) {}

    std::optional<std::string> get_scheme() {
        size_t scheme_end = url.find("://");
        if (scheme_end != std::string::npos) {
            return url.substr(0, scheme_end);
        }
        return std::nullopt;
    }

    std::optional<std::string> get_host() {
        size_t scheme_end = url.find("://");
        if (scheme_end != std::string::npos) {
            std::string url_without_scheme = url.substr(scheme_end + 3);
            size_t host_end = url_without_scheme.find('/');
            if (host_end != std::string::npos) {
                return url_without_scheme.substr(0, host_end);
            } else {
                return url_without_scheme;
            }
        }
        return std::nullopt;
    }

    std::optional<std::string> get_path() {
        size_t scheme_end = url.find("://");
        if (scheme_end != std::string::npos) {
            std::string url_without_scheme = url.substr(scheme_end + 3);
            size_t host_end = url_without_scheme.find('/');
            if (host_end != std::string::npos) {
                return url_without_scheme.substr(host_end);
            }
        }
        return std::nullopt;
    }

    std::optional<std::map<std::string, std::string>> get_query_params() {
        size_t query_start = url.find('?');
        if (query_start == std::string::npos) {
            return std::nullopt;
        }

        size_t fragment_start = url.find('#', query_start + 1);
        std::string query_string;
        if (fragment_start != std::string::npos) {
            query_string = url.substr(query_start + 1, fragment_start - query_start - 1);
        } else {
            query_string = url.substr(query_start + 1);
        }

        std::vector<std::string> param_pairs = split(query_string, '&');
        std::map<std::string, std::string> params;

        for (const auto& pair : param_pairs) {
            std::vector<std::string> key_value = split(pair, '=');
            if (key_value.size() == 2) {
                params[key_value[0]] = key_value[1];
            }
        }

        return params;
    }

    std::optional<std::string> get_fragment() {
        size_t fragment_start = url.find('#');
        if (fragment_start != std::string::npos) {
            return url.substr(fragment_start + 1);
        }
        return std::nullopt;
    }
};
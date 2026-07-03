#include <string>
#include <optional>
#include <map>
#include <vector>
#include <cctype>

class URLHandler {
private:
    std::string url;

    size_t find(const std::string& sub) const {
        return url.find(sub);
    }

    std::string substr(size_t start, size_t len = std::string::npos) const {
        return url.substr(start, len);
    }

    bool starts_with(const std::string& prefix) const {
        if (prefix.length() > url.length()) return false;
        return url.substr(0, prefix.length()) == prefix;
    }

public:
    URLHandler(const std::string& url) : url(url) {}

    std::optional<std::string> get_scheme() const {
        size_t scheme_end = find("://");
        if (scheme_end != std::string::npos) {
            return substr(0, scheme_end);
        }
        return std::nullopt;
    }

    std::optional<std::string> get_host() const {
        size_t scheme_end = find("://");
        if (scheme_end != std::string::npos) {
            std::string without_scheme = substr(scheme_end + 3);
            size_t host_end = without_scheme.find('/');
            if (host_end != std::string::npos) {
                return without_scheme.substr(0, host_end);
            }
            return without_scheme;
        }
        return std::nullopt;
    }

    std::optional<std::string> get_path() const {
        size_t scheme_end = find("://");
        if (scheme_end != std::string::npos) {
            std::string without_scheme = substr(scheme_end + 3);
            size_t host_end = without_scheme.find('/');
            if (host_end != std::string::npos) {
                return without_scheme.substr(host_end);
            }
        }
        return std::nullopt;
    }

    std::optional<std::map<std::string, std::string>> get_query_params() const {
        size_t query_start = find('?');
        if (query_start == std::string::npos) {
            return std::nullopt;
        }

        size_t fragment_start = find('#');
        std::string query_string = substr(query_start + 1, (fragment_start != std::string::npos) ? fragment_start - (query_start + 1) : std::string::npos);

        if (query_string.empty()) {
            return std::nullopt;
        }

        std::map<std::string, std::string> params;
        std::vector<std::string> param_pairs;
        size_t start = 0;
        size_t end = 0;

        while ((end = query_string.find('&', start)) != std::string::npos) {
            param_pairs.push_back(query_string.substr(start, end - start));
            start = end + 1;
        }
        param_pairs.push_back(query_string.substr(start));

        for (const auto& pair : param_pairs) {
            size_t eq_pos = pair.find('=');
            if (eq_pos != std::string::npos) {
                std::string key = pair.substr(0, eq_pos);
                std::string value = pair.substr(eq_pos + 1);
                params[key] = value;
            }
        }

        return params;
    }

    std::optional<std::string> get_fragment() const {
        size_t fragment_start = find('#');
        if (fragment_start != std::string::npos) {
            return substr(fragment_start + 1);
        }
        return std::nullopt;
    }
};
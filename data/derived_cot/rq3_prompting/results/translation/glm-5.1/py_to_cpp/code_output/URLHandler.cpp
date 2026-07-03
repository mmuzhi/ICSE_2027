#include <string>
#include <unordered_map>
#include <optional>
#include <vector>

class URLHandler {
private:
    std::string url;

    static std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end;
        while ((end = s.find(delim, start)) != std::string::npos) {
            tokens.push_back(s.substr(start, end - start));
            start = end + 1;
        }
        tokens.push_back(s.substr(start));
        return tokens;
    }

public:
    URLHandler(const std::string& url) : url(url) {}

    std::optional<std::string> get_scheme() const {
        size_t pos = url.find("://");
        if (pos != std::string::npos) {
            return url.substr(0, pos);
        }
        return std::nullopt;
    }

    std::optional<std::string> get_host() const {
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

    std::optional<std::string> get_path() const {
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

    std::optional<std::unordered_map<std::string, std::string>> get_query_params() const {
        size_t query_start = url.find('?');
        if (query_start != std::string::npos) {
            size_t fragment_start = url.find('#');
            size_t start = query_start + 1;
            size_t length;
            if (fragment_start != std::string::npos) {
                if (fragment_start > query_start) {
                    length = fragment_start - start;
                } else {
                    length = 0;
                }
            } else {
                length = url.length() - start;
            }
            std::string query_string = url.substr(start, length);
            std::unordered_map<std::string, std::string> params;
            if (!query_string.empty()) {
                std::vector<std::string> pairs = split(query_string, '&');
                for (const auto& pair : pairs) {
                    std::vector<std::string> kv = split(pair, '=');
                    if (kv.size() == 2) {
                        params[kv[0]] = kv[1];
                    }
                }
            }
            return params;
        }
        return std::nullopt;
    }

    std::optional<std::string> get_fragment() const {
        size_t fragment_start = url.find('#');
        if (fragment_start != std::string::npos) {
            return url.substr(fragment_start + 1);
        }
        return std::nullopt;
    }
};
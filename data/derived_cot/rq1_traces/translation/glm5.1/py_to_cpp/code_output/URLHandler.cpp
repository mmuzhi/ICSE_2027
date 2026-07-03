#include <string>
#include <optional>
#include <map>

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
        if (scheme_end != std::string::npos) {
            std::string url_without_scheme = url.substr(scheme_end + 3);
            size_t host_end = url_without_scheme.find("/");
            if (host_end != std::string::npos) {
                return url_without_scheme.substr(0, host_end);
            }
            return url_without_scheme;
        }
        return std::nullopt;
    }

    std::optional<std::string> get_path() const {
        size_t scheme_end = url.find("://");
        if (scheme_end != std::string::npos) {
            std::string url_without_scheme = url.substr(scheme_end + 3);
            size_t host_end = url_without_scheme.find("/");
            if (host_end != std::string::npos) {
                return url_without_scheme.substr(host_end);
            }
        }
        return std::nullopt;
    }

    std::optional<std::map<std::string, std::string>> get_query_params() const {
        size_t query_start = url.find("?");
        size_t fragment_start = url.find("#");
        if (query_start != std::string::npos) {
            std::string query_string;
            if (fragment_start != std::string::npos) {
                if (fragment_start > query_start + 1) {
                    query_string = url.substr(query_start + 1, fragment_start - query_start - 1);
                }
            } else {
                // Replicate Python behavior: url[query_start+1:-1] where -1 means len-1, excluding last char
                size_t end_pos = url.size() - 1;
                if (end_pos > query_start) {
                    query_string = url.substr(query_start + 1, end_pos - query_start - 1);
                }
            }
            std::map<std::string, std::string> params;
            if (!query_string.empty()) {
                size_t pos = 0;
                while (pos <= query_string.size()) {
                    size_t next_amp = query_string.find("&", pos);
                    std::string pair;
                    if (next_amp != std::string::npos) {
                        pair = query_string.substr(pos, next_amp - pos);
                        pos = next_amp + 1;
                    } else {
                        pair = query_string.substr(pos);
                        pos = query_string.size() + 1;
                    }
                    size_t eq_pos = pair.find("=");
                    if (eq_pos != std::string::npos) {
                        // Python split("=") must yield exactly 2 elements (exactly one "=")
                        if (pair.find("=", eq_pos + 1) == std::string::npos) {
                            params[pair.substr(0, eq_pos)] = pair.substr(eq_pos + 1);
                        }
                    }
                }
            }
            return params;
        }
        return std::nullopt;
    }

    std::optional<std::string> get_fragment() const {
        size_t fragment_start = url.find("#");
        if (fragment_start != std::string::npos) {
            return url.substr(fragment_start + 1);
        }
        return std::nullopt;
    }
};
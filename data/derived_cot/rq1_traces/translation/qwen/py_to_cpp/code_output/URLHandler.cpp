#include <string>
#include <map>
#include <vector>
#include <algorithm>

class URLHandler {
private:
    std::string url;

public:
    URLHandler(const std::string& url) : url(url) {}

    std::string get_scheme() const {
        size_t scheme_end = url.find("://");
        if (scheme_end != std::string::npos) {
            return url.substr(0, scheme_end);
        }
        return std::string();
    }

    std::string get_host() const {
        size_t scheme_end = url.find("://");
        if (scheme_end != std::string::npos) {
            std::string url_without_scheme = url.substr(scheme_end + 3);
            size_t host_end = url_without_scheme.find('/');
            if (host_end != std::string::npos) {
                return url_without_scheme.substr(0, host_end);
            }
            return url_without_scheme;
        }
        return std::string();
    }

    std::string get_path() const {
        size_t scheme_end = url.find("://");
        if (scheme_end != std::string::npos) {
            std::string url_without_scheme = url.substr(scheme_end + 3);
            size_t host_end = url_without_scheme.find('/');
            if (host_end != std::string::npos) {
                return url_without_scheme.substr(host_end);
            }
        }
        return std::string();
    }

    std::map<std::string, std::string> get_query_params() const {
        size_t query_start = url.find('?');
        size_t fragment_start = url.find('#');
        if (query_start != std::string::npos) {
            std::string query_string = url.substr(query_start + 1, 
                (fragment_start == std::string::npos ? -1 : fragment_start - (query_start + 1)));
            std::map<std::string, std::string> params;
            if (!query_string.empty()) {
                std::vector<std::string> param_pairs;
                size_t start = 0;
                size_t pos = 0;
                while ((pos = query_string.find('&', start)) != std::string::npos) {
                    param_pairs.push_back(query_string.substr(start, pos - start));
                    start = pos + 1;
                }
                param_pairs.push_back(query_string.substr(start));

                for (const auto& pair : param_pairs) {
                    size_t eq_pos = pair.find('=');
                    if (eq_pos != std::string::npos) {
                        std::string key = pair.substr(0, eq_pos);
                        std::string value = pair.substr(eq_pos + 1);
                        params[key] = value;
                    } else {
                        params[pair] = "";
                    }
                }
            }
            return params;
        }
        return std::map<std::string, std::string>();
    }

    std::string get_fragment() const {
        size_t fragment_start = url.find('#');
        if (fragment_start != std::string::npos) {
            return url.substr(fragment_start + 1);
        }
        return std::string();
    }
};
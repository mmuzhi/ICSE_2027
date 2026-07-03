#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <optional>
#include <iterator>

class CookiesUtil {
private:
    std::string cookiesFile;
    std::optional<std::map<std::string, std::string>> cookies;

    // Escape a string for JSON (only " and \)
    static std::string escapeJSONString(const std::string& s) {
        std::string out;
        out.reserve(s.size() + 2);
        for (char ch : s) {
            switch (ch) {
                case '"':  out += "\\\""; break;
                case '\\': out += "\\\\"; break;
                default:   out += ch;
            }
        }
        return out;
    }

    // Build a JSON object string from a map
    static std::string buildJSON(const std::map<std::string, std::string>& m) {
        std::string json = "{";
        bool first = true;
        for (const auto& pair : m) {
            if (!first) json += ",";
            json += "\"" + escapeJSONString(pair.first) + "\":\"" + escapeJSONString(pair.second) + "\"";
            first = false;
        }
        json += "}";
        return json;
    }

    // Parse a simple JSON object (assumes string keys/values, no nesting)
    static std::map<std::string, std::string> parseJSON(const std::string& content) {
        std::map<std::string, std::string> result;
        size_t i = 0;
        auto skipWS = [&]() {
            while (i < content.size() && (content[i] == ' ' || content[i] == '\t' || content[i] == '\n' || content[i] == '\r'))
                i++;
        };
        skipWS();
        if (i >= content.size() || content[i] != '{') return result;
        i++; // skip '{'
        while (i < content.size()) {
            skipWS();
            if (i >= content.size() || content[i] == '}') break;
            // key
            if (content[i] != '"') return result;
            i++;
            std::string key;
            while (i < content.size() && content[i] != '"') {
                if (content[i] == '\\' && i + 1 < content.size()) {
                    i++;
                    if (content[i] == '"') key += '"';
                    else if (content[i] == '\\') key += '\\';
                    else key += content[i];
                } else {
                    key += content[i];
                }
                i++;
            }
            if (i >= content.size() || content[i] != '"') return result;
            i++;
            skipWS();
            if (i >= content.size() || content[i] != ':') return result;
            i++;
            skipWS();
            // value
            if (i >= content.size() || content[i] != '"') return result;
            i++;
            std::string value;
            while (i < content.size() && content[i] != '"') {
                if (content[i] == '\\' && i + 1 < content.size()) {
                    i++;
                    if (content[i] == '"') value += '"';
                    else if (content[i] == '\\') value += '\\';
                    else value += content[i];
                } else {
                    value += content[i];
                }
                i++;
            }
            if (i >= content.size() || content[i] != '"') return result;
            i++;
            skipWS();
            result[key] = value;
            // comma or end
            if (i < content.size() && content[i] == ',') {
                i++;
                skipWS();
            } else if (i < content.size() && content[i] == '}') {
                break;
            } else {
                return result; // error
            }
        }
        skipWS();
        if (i < content.size() && content[i] == '}') i++;
        return result;
    }

public:
    CookiesUtil(const std::string& cookiesFile) : cookiesFile(cookiesFile), cookies(std::nullopt) {}

    void getCookies(const std::map<std::string, std::map<std::string, std::string>>& response) {
        auto it = response.find("cookies");
        if (it != response.end()) {
            cookies = it->second;
        } else {
            cookies = std::nullopt;
        }
        _saveCookies();
    }

    std::map<std::string, std::string> loadCookies() {
        std::ifstream file(cookiesFile);
        if (!file.is_open()) {
            return std::map<std::string, std::string>();
        }
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return parseJSON(content);
    }

    bool _saveCookies() {
        std::ofstream file(cookiesFile);
        if (!file.is_open()) {
            return false;
        }
        std::string json;
        if (cookies) {
            json = buildJSON(*cookies);
        } else {
            json = "{}";
        }
        file << json;
        file.flush();
        file.close();
        return true;
    }

    void setCookies(std::map<std::string, std::string>& request) {
        if (!cookies) {
            request["cookies"] = "";
            return;
        }
        std::stringstream ss;
        bool first = true;
        for (const auto& pair : *cookies) {
            if (!first) ss << "; ";
            ss << pair.first << "=" << pair.second;
            first = false;
        }
        request["cookies"] = ss.str();
    }
};
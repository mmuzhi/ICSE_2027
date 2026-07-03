#include <fstream>
#include <map>
#include <string>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CookiesUtil {
private:
    std::string cookiesFile;
    std::unordered_map<std::string, std::string> cookies;

public:
    CookiesUtil(const std::string& cookiesFile) : cookiesFile(cookiesFile) {}

    void getCookies(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>* response) {
        auto it = response->find("cookies");
        std::unordered_map<std::string, std::string> cookiesData;
        if (it != response->end()) {
            cookiesData = *it->second;
        }
        cookies = std::move(cookiesData);
        _saveCookies();
    }

    std::unordered_map<std::string, std::string> loadCookies() {
        try {
            std::ifstream reader(cookiesFile);
            if (!reader.is_open()) {
                return {};
            }
            json jsonObject = json::parse(reader);
            std::unordered_map<std::string, std::string> cookiesData;
            for (auto& item : jsonObject.items()) {
                cookiesData[item.key] = item.value.get<std::string>();
            }
            return cookiesData;
        } catch (...) {
            return {};
        }
    }

    bool _saveCookies() {
        try {
            json jsonObject;
            for (const auto& kv : cookies) {
                jsonObject[kv.first] = kv.second;
            }
            std::ofstream file(cookiesFile);
            if (!file.is_open()) {
                return false;
            }
            file << jsonObject.dump(4);
            file.flush();
            return true;
        } catch (...) {
            return false;
        }
    }

    void setCookies(std::unordered_map<std::string, std::string>* request) {
        std::string cookiesString;
        for (const auto& kv : cookies) {
            if (!cookiesString.empty()) {
                cookiesString += "; ";
            }
            cookiesString += kv.first + "=" + kv.second;
        }
        request->insert({"cookies", cookiesString});
    }
};
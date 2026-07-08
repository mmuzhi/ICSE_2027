#include <string>
#include <fstream>
#include <filesystem>
#include <optional>
#include <exception>
#include <nlohmann/json.hpp>

class JSONProcessor {
public:
    // nlohmann::ordered_json preserves insertion order, matching Java's LinkedHashMap behavior from Gson.
    // nlohmann::json (default) sorts keys alphabetically.
    using JsonObject = nlohmann::ordered_json;

    std::optional<JsonObject> readJson(const std::string& filePath) {
        try {
            if (!std::filesystem::exists(filePath)) {
                return std::nullopt;
            }
            
            std::ifstream file(filePath);
            if (!file.is_open()) {
                return std::nullopt;
            }

            JsonObject data = JsonObject::parse(file);
            
            // Gson's fromJson with Map.class expects a JSON object; it throws if the JSON is an array or primitive.
            if (!data.is_object()) {
                return std::nullopt;
            }
            
            return data;
        } catch (const std::exception& e) {
            // Catches parsing errors, filesystem errors, or IO errors
            return std::nullopt;
        }
    }

    bool writeJson(const JsonObject& data, const std::string& filePath) {
        try {
            std::ofstream file(filePath);
            if (!file.is_open()) {
                return false;
            }
            
            // new Gson().toJson() outputs minified JSON by default, matching dump()
            file << data.dump();
            
            // Check for stream write failures to match Java's IOException catch block
            if (!file.good()) {
                return false;
            }
            
            return true;
        } catch (const std::exception& e) {
            return false;
        }
    }

    bool processJson(const std::string& filePath, const std::string& removeKey) {
        auto dataOpt = readJson(filePath);
        if (!dataOpt.has_value()) {
            return false;
        }
        
        JsonObject data = std::move(*dataOpt);
        
        if (data.contains(removeKey)) {
            data.erase(removeKey);
            return writeJson(data, filePath);
        } else {
            return false;
        }
    }
};
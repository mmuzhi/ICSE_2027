#include <iostream>
#include <map>
#include <string>
#include <any>
#include <vector>
#include <optional>
#include <stdexcept>
#include <locale>
#include <date/timestamp.hpp>

namespace {

struct JwtToken {
    std::string jwt;
    std::string name;
    int level;
    std::string address;
};

bool isStartWith(const std::string& requestUri) {
    const std::vector<std::string> prefixes = {"/api", "/login"};
    for (const auto& prefix : prefixes) {
        if (requestUri.starts_with(prefix)) {
            return true;
        }
    }
    return false;
}

std::optional<JwtToken> parseJwtToken(const std::string& jwt) {
    auto parts = std::string_view(jwt).split('.');
    if (parts.size() != 3) {
        return std::nullopt;
    }
    auto header = parts[1];
    header.remove_prefix(header.find('=') - header.begin() + 1);
    header.remove_suffix(header.size() - header.find('=') - 1);
    std::string encodedHeader(header.substr(0, header.find('=')));
    std::string decodedHeader;
    for (char c : encodedHeader) {
        if (c == '-') decodedHeader += '+';
        else if (c == '_') decodedHeader += '/';
        else if (c > 126) continue;
        else decodedHeader += c;
    }
    decodedHeader = std::string(decodedHeader.begin(), decodedHeader.end());
    decodedHeader = Base64::decode(decodedHeader);
    // Parse decodedHeader as JSON to extract user info
    // This is a simplified version; actual implementation would parse JSON
    auto userParts = decodedHeader.split(',');
    if (userParts.size() < 4) {
        return std::nullopt;
    }
    auto name = userParts[0].substr(1);
    auto levelStr = userParts[1].substr(1, userParts[1].find('}') - userParts[1].substr(1).find(':') - 1);
    auto address = userParts[3].substr(1, userParts[3].find('}') - userParts[3].substr(1).find(':') - 1);
    try {
        int level = std::stoi(levelStr);
        return JwtToken{jwt, name, level, address};
    } catch (...) {
        return std::nullopt;
    }
}

} // anonymous namespace

class AccessGatewayFilter {
public:
    bool filter(std::map<std::string, std::any> request) {
        if (auto uri = any_cast_if<std::string>(&request["path"]); uri) {
            if (isStartWith(*uri)) {
                return true;
            }
        }

        try {
            auto headers = any_cast_if<std::map<std::string, std::any>>(&request["headers"]);
            if (!headers) return false;
            auto authHeader = any_cast_if<std::map<std::string, std::any>>(&headers["Authorization"]);
            if (!authHeader) return false;
            auto token = any_cast_if<std::map<std::string, std::any>>(&authHeader["user"]);
            if (!token) return false;
            auto jwt = any_cast_if<std::string>(&token["jwt"]);
            if (!jwt) return false;

            auto user = parseJwtToken(*jwt);
            if (!user) return false;

            if (user->level > 2) {
                setCurrentUserInfoAndLog(*user);
                return true;
            }
        } catch (...) {
            return false;
        }
        return false;
    }

    void setCurrentUserInfoAndLog(const JwtToken& user) {
        std::string host = user.address;
        std::string message = user.name + host + std::string{std::date::format_date(std::date::year_month_day{std::chrono::system_clock::now().time_zone}, user.address)};
        std::cout << message << std::endl;
    }
};

// Base64 decoding is not implemented in the code snippet. In a real scenario, you would need to implement or include a Base64 decoder.
// This is a placeholder for Base64::decode.
std::string Base64::decode(const std::string& encoded) {
    // Implementation of Base64 decoding would go here.
    return encoded; // Placeholder
}
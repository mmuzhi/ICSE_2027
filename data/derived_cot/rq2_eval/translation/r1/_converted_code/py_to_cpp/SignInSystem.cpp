#include <vector>
#include <string>
#include <unordered_map>

class SignInSystem {
private:
    std::vector<std::string> insertion_order;
    std::unordered_map<std::string, bool> users_map;

public:
    SignInSystem() = default;

    bool add_user(const std::string& username) {
        if (users_map.find(username) != users_map.end()) {
            return false;
        }
        insertion_order.push_back(username);
        users_map[username] = false;
        return true;
    }

    bool sign_in(const std::string& username) {
        auto it = users_map.find(username);
        if (it == users_map.end()) {
            return false;
        }
        it->second = true;
        return true;
    }

    bool check_sign_in(const std::string& username) const {
        auto it = users_map.find(username);
        if (it == users_map.end()) {
            return false;
        }
        return it->second;
    }

    bool all_signed_in() const {
        for (const auto& username : insertion_order) {
            if (!users_map.at(username)) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> all_not_signed_in() const {
        std::vector<std::string> result;
        for (const auto& username : insertion_order) {
            if (!users_map.at(username)) {
                result.push_back(username);
            }
        }
        return result;
    }
};
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

class SignInSystem {
private:
    std::unordered_map<std::string, bool> users;
    std::vector<std::string> insertion_order;

public:
    SignInSystem() = default;

    bool add_user(const std::string& username) {
        if (users.count(username)) {
            return false;
        }
        users[username] = false;
        insertion_order.push_back(username);
        return true;
    }

    bool sign_in(const std::string& username) {
        auto it = users.find(username);
        if (it == users.end()) {
            return false;
        }
        it->second = true;
        return true;
    }

    bool check_sign_in(const std::string& username) {
        auto it = users.find(username);
        if (it == users.end()) {
            return false;
        }
        return it->second;
    }

    bool all_signed_in() {
        return std::all_of(users.begin(), users.end(), [](const auto& pair) {
            return pair.second;
        });
    }

    std::vector<std::string> all_not_signed_in() {
        std::vector<std::string> not_signed_in_users;
        for (const auto& username : insertion_order) {
            if (!users[username]) {
                not_signed_in_users.push_back(username);
            }
        }
        return not_signed_in_users;
    }
};
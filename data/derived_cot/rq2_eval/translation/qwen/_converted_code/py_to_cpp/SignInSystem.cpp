#include <unordered_map>
#include <vector>
#include <string>

class SignInSystem {
private:
    std::unordered_map<std::string, bool> users;

public:
    SignInSystem() = default;

    bool add_user(const std::string& username) {
        if (users.find(username) != users.end()) {
            return false;
        }
        users[username] = false;
        return true;
    }

    bool sign_in(const std::string& username) {
        if (users.find(username) == users.end()) {
            return false;
        }
        users[username] = true;
        return true;
    }

    bool check_sign_in(const std::string& username) const {
        if (users.find(username) == users.end()) {
            return false;
        }
        return users.at(username);
    }

    bool all_signed_in() const {
        for (const auto& entry : users) {
            if (!entry.second) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> all_not_signed_in() const {
        std::vector<std::string> not_signed_in;
        for (const auto& entry : users) {
            if (!entry.second) {
                not_signed_in.push_back(entry.first);
            }
        }
        return not_signed_in;
    }
};
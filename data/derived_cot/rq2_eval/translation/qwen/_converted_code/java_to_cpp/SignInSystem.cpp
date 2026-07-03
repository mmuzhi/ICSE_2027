#include <unordered_map>
#include <vector>
#include <string>

class SignInSystem {
private:
    std::unordered_map<std::string, bool> users;

public:
    SignInSystem() = default;

    bool add_user(const std::string& username) {
        auto it = users.find(username);
        if (it != users.end()) {
            return false;
        }
        users[username] = false;
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

    bool check_sign_in(const std::string& username) const {
        auto it = users.find(username);
        if (it == users.end()) {
            return false;
        }
        return it->second;
    }

    bool all_signed_in() const {
        for (const auto& entry : users) {
            if (!entry.second) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> allNotSignedIn() const {
        std::vector<std::string> notSignedInUsers;
        for (const auto& entry : users) {
            if (!entry.second) {
                notSignedInUsers.push_back(entry.first);
            }
        }
        return notSignedInUsers;
    }
};
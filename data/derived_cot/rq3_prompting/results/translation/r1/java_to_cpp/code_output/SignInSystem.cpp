#include <unordered_map>
#include <string>
#include <vector>

class SignInSystem {
private:
    std::unordered_map<std::string, bool> users;

public:
    SignInSystem() = default;

    bool addUser(const std::string& username) {
        if (users.find(username) != users.end()) {
            return false;
        }
        users[username] = false;
        return true;
    }

    bool signIn(const std::string& username) {
        auto it = users.find(username);
        if (it == users.end()) {
            return false;
        }
        it->second = true;
        return true;
    }

    bool checkSignIn(const std::string& username) {
        auto it = users.find(username);
        if (it == users.end()) {
            return false;
        }
        return it->second;
    }

    bool allSignedIn() {
        for (const auto& entry : users) {
            if (!entry.second) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> allNotSignedIn() {
        std::vector<std::string> result;
        for (const auto& entry : users) {
            if (!entry.second) {
                result.push_back(entry.first);
            }
        }
        return result;
    }
};
#include <vector>
#include <unordered_map>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

struct Message {
    std::string sender;
    std::string receiver;
    std::string message;
    std::string timestamp;
};

class Chat {
public:
    void add_user(const std::string& username) {
        if (users.find(username) != users.end()) {
            return; // False behavior by not adding
        }
        users[username] = std::vector<Message>();
    }

    bool is_user_present(const std::string& username) const {
        return users.find(username) != users.end();
    }

    void remove_user(const std::string& username) {
        auto it = users.find(username);
        if (it != users.end()) {
            users.erase(it);
        }
    }

    bool send_message(const std::string& sender, const std::string& receiver, const std::string& message) {
        if (!is_user_present(sender) || !is_user_present(receiver)) {
            return false;
        }

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm buf = *std::localtime(&in_time_t);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &buf);
        std::string timestamp(buffer);

        Message msg = {sender, receiver, message, timestamp};
        users[sender].push_back(msg);
        users[receiver].push_back(msg);
        return true;
    }

    std::vector<Message> get_messages(const std::string& username) const {
        if (!is_user_present(username)) {
            return {};
        }
        return users.at(username);
    }

private:
    std::unordered_map<std::string, std::vector<Message>> users;
};
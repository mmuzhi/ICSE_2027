#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

class Chat {
public:
    using Message = std::map<std::string, std::string>;

    Chat() = default;

    bool add_user(const std::string& username) {
        if (users.find(username) != users.end()) {
            return false;
        }
        users[username] = std::vector<Message>();
        return true;
    }

    bool remove_user(const std::string& username) {
        auto it = users.find(username);
        if (it != users.end()) {
            users.erase(it);
            return true;
        }
        return false;
    }

    bool send_message(const std::string& sender, const std::string& receiver, const std::string& message) {
        if (users.find(sender) == users.end() || users.find(receiver) == users.end()) {
            return false;
        }

        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* local_tm = std::localtime(&now_time);
        std::ostringstream oss;
        oss << std::put_time(local_tm, "%Y-%m-%d %H:%M:%S");
        std::string timestamp = oss.str();

        Message message_info;
        message_info["sender"] = sender;
        message_info["receiver"] = receiver;
        message_info["message"] = message;
        message_info["timestamp"] = timestamp;

        users[sender].push_back(message_info);
        users[receiver].push_back(message_info);
        return true;
    }

    std::vector<Message> get_messages(const std::string& username) {
        auto it = users.find(username);
        if (it == users.end()) {
            return std::vector<Message>();
        }
        return it->second;
    }

private:
    std::unordered_map<std::string, std::vector<Message>> users;
};
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

struct Message {
    std::string sender;
    std::string receiver;
    std::string message;
    std::string timestamp;
};

class Chat {
private:
    std::unordered_map<std::string, std::vector<std::shared_ptr<Message>>> users;

public:
    Chat() = default;

    bool add_user(const std::string& username) {
        if (users.find(username) != users.end()) {
            return false;
        }
        users[username] = std::vector<std::shared_ptr<Message>>();
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
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buf;
        #if defined(_WIN32) || defined(_WIN64)
            localtime_s(&tm_buf, &in_time_t);
        #else
            localtime_r(&in_time_t, &tm_buf);
        #endif
        std::stringstream ss;
        ss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
        std::string timestamp = ss.str();

        auto msg = std::make_shared<Message>();
        msg->sender = sender;
        msg->receiver = receiver;
        msg->message = message;
        msg->timestamp = timestamp;

        users[sender].push_back(msg);
        users[receiver].push_back(msg);
        return true;
    }

    std::vector<std::shared_ptr<Message>> get_messages(const std::string& username) {
        auto it = users.find(username);
        if (it != users.end()) {
            return it->second;
        }
        return {};
    }
};
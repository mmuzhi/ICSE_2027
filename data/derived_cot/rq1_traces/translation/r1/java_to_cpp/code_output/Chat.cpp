#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace org {
namespace example {

class Chat {
public:
    class Message {
    public:
        Message(const std::string& sender, const std::string& receiver, const std::string& message, const std::string& timestamp)
            : sender(sender), receiver(receiver), message(message), timestamp(timestamp) {}

        std::string getSender() const { return sender; }
        std::string getReceiver() const { return receiver; }
        std::string getMessage() const { return message; }
        std::string getTimestamp() const { return timestamp; }

        bool operator==(const Message& other) const {
            return sender == other.sender &&
                   receiver == other.receiver &&
                   message == other.message &&
                   timestamp == other.timestamp;
        }

        bool operator!=(const Message& other) const {
            return !(*this == other);
        }

        std::string toString() const {
            return "Message{sender='" + sender + "', receiver='" + receiver + "', message='" + message + "', timestamp='" + timestamp + "'}";
        }

    private:
        std::string sender;
        std::string receiver;
        std::string message;
        std::string timestamp;
    };

private:
    std::unordered_map<std::string, std::vector<Message>> users;

    static std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm;
        #if defined(_WIN32)
        localtime_s(&now_tm, &now_time);
        #else
        localtime_r(&now_time, &now_tm);
        #endif
        std::stringstream ss;
        ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

public:
    Chat() = default;

    bool addUser(const std::string& username) {
        if (users.find(username) != users.end()) {
            return false;
        }
        users[username] = std::vector<Message>();
        return true;
    }

    bool removeUser(const std::string& username) {
        if (users.find(username) != users.end()) {
            users.erase(username);
            return true;
        }
        return false;
    }

    bool sendMessage(const std::string& sender, const std::string& receiver, const std::string& message) {
        if (users.find(sender) == users.end() || users.find(receiver) == users.end()) {
            return false;
        }

        std::string timestamp = getCurrentTimestamp();
        Message messageInfo(sender, receiver, message, timestamp);

        users[sender].push_back(messageInfo);
        users[receiver].push_back(messageInfo);
        return true;
    }

    std::vector<Message>& getMessages(const std::string& username) {
        auto it = users.find(username);
        if (it != users.end()) {
            return it->second;
        } else {
            static std::vector<Message> emptyVector;
            return emptyVector;
        }
    }

    std::unordered_map<std::string, std::vector<Message>>& getUsers() {
        return users;
    }
};

} // namespace example
} // namespace org
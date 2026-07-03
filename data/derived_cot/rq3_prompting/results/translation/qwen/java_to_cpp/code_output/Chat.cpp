#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>

class Chat {
public:
    class Message;

    using UserMessages = std::vector<std::shared_ptr<Message>>;

    class Message {
    public:
        std::string sender;
        std::string receiver;
        std::string message;
        std::string timestamp;

        Message(const std::string& sender, const std::string& receiver, const std::string& message, const std::string& timestamp)
            : sender(sender), receiver(receiver), message(message), timestamp(timestamp) {}

        bool operator==(const Message& other) const {
            return sender == other.sender &&
                   receiver == other.receiver &&
                   message == other.message &&
                   timestamp == other.timestamp;
        }

        std::string toString() const {
            return "Message{sender='" + sender + "', receiver='" + receiver + "', message='" + message + "', timestamp='" + timestamp + "'}";
        }
    };

    Chat() : users(std::unordered_map<std::string, UserMessages>()) {}

    bool addUser(const std::string& username) {
        if (users.find(username) != users.end()) {
            return false;
        }
        users[username] = UserMessages();
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

        std::string timestamp = getCurrentDateTime();

        auto msg = std::make_shared<Message>(sender, receiver, message, timestamp);

        users[sender].push_back(msg);
        users[receiver].push_back(msg);

        return true;
    }

    std::vector<std::shared_ptr<Message>>& getMessages(const std::string& username) {
        if (users.find(username) == users.end()) {
            static std::vector<std::shared_ptr<Message>> empty;
            return empty;
        }
        return users[username];
    }

private:
    std::string getCurrentDateTime() {
        std::time_t now = std::time(nullptr);
        std::tm* dt = std::localtime(&now);

        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", dt);
        return std::string(buffer);
    }

    std::unordered_map<std::string, UserMessages> users;
};
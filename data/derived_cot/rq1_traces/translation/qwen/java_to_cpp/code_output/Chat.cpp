#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <string>
#include <iomanip>

class Chat {
private:
    using MessageList = std::vector<Message>;
    std::unordered_map<std::string, MessageList> users;

public:
    Chat() : users() {}

    bool addUser(const std::string& username) {
        return users.find(username) == users.end() 
               ? (users.insert({username, {}}), true) 
               : false;
    }

    bool removeUser(const std::string& username) {
        return users.erase(username) > 0;
    }

    bool sendMessage(const std::string& sender, const std::string& receiver, const std::string& message) {
        if (users.find(sender) == users.end() || users.find(receiver) == users.end()) {
            return false;
        }

        auto now = std::time(nullptr);
        std::tm* utc_time = std::gmtime(&now);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", utc_time);
        std::string timestamp(buffer);

        Message messageInfo(sender, receiver, message, timestamp);

        users[sender].push_back(messageInfo);
        users[receiver].push_back(messageInfo);
        return true;
    }

    MessageList getMessages(const std::string& username) const {
        return users.find(username) != users.end() ? users.at(username) : MessageList();
    }

    const std::unordered_map<std::string, MessageList>& getUsers() const {
        return users;
    }

    class Message {
    private:
        std::string sender;
        std::string receiver;
        std::string message;
        std::string timestamp;

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

        bool operator<(const Message& other) const {
            return timestamp < other.timestamp;
        }

        friend std::ostream& operator<<(std::ostream& os, const Message& msg) {
            return os << "Message{sender='" << msg.sender << "', receiver='" << msg.receiver << "', message='" << msg.message << "', timestamp='" << msg.timestamp << "}";
        }
    };
};
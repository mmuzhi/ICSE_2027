#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

struct Message {
    std::string sender;
    std::string receiver;
    std::string message;
    std::string timestamp;
};

class Chat {
private:
    std::unordered_map<std::string, std::vector<Message>> users;

    std::string get_current_time() {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm buf = {};
        std::strftime(&buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
        char buffer[128];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &buf);
        return std::string(buffer);
    }

public:
    bool add_user(const std::string& username) {
        if (users.find(username) != users.end()) {
            return false;
        }
        users[username] = {};
        return true;
    }

    bool remove_user(const std::string& username) {
        if (users.find(username) != users.end()) {
            users.erase(username);
            return true;
        }
        return false;
    }

    bool send_message(const std::string& sender, const std::string& receiver, const std::string& message) {
        if (users.find(sender) == users.end() || users.find(receiver) == users.end()) {
            return false;
        }

        Message msg = {
            sender,
            receiver,
            message,
            get_current_time()
        };

        users[sender].push_back(msg);
        users[receiver].push_back(msg);
        return true;
    }

    std::vector<Message> get_messages(const std::string& username) {
        if (users.find(username) == users.end()) {
            return {};
        }
        return users[username];
    }
};

int main() {
    Chat chat;
    chat.add_user("John");
    chat.add_user("Mary");
    
    chat.send_message("John", "Mary", "Hello");
    
    auto messages = chat.get_messages("John");
    for (const auto& msg : messages) {
        std::cout << "From: " << msg.sender << " To: " << msg.receiver << "\n"
                  << "Message: " << msg.message << "\n"
                  << "Time: " << msg.timestamp << "\n\n";
    }

    return 0;
}
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <sstream>
#include <iomanip>

struct Message {
    std::string sender;
    std::string receiver;
    std::string message;
    std::string timestamp;
};

class Chat {
private:
    std::map<std::string, std::vector<Message>> users;

public:
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

        // Get current timestamp formatted like datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        std::time_t t = std::time(nullptr);
        std::tm* tm_ptr = std::localtime(&t);
        std::stringstream ss;
        ss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S");
        std::string timestamp = ss.str();

        Message msg;
        msg.sender = sender;
        msg.receiver = receiver;
        msg.message = message;
        msg.timestamp = timestamp;

        users[sender].push_back(msg);
        users[receiver].push_back(msg);
        return true;
    }

    std::vector<Message> get_messages(const std::string& username) const {
        auto it = users.find(username);
        if (it == users.end()) {
            return std::vector<Message>();
        }
        return it->second;
    }
};
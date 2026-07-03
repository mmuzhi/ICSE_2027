#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <type_traits>

struct Message {
    int addr;
    std::string content;
};

class Server {
private:
    std::vector<int> white_list;
    Message send_struct;
    Message receive_struct;

    bool validate_message(const Message& msg) const {
        return msg.addr != 0 && !msg.content.empty();
    }

public:
    Server() : white_list(), send_struct(), receive_struct() {}

    std::vector<int> add_white_list(int addr) {
        if (std::find(white_list.begin(), white_list.end(), addr) != white_list.end()) {
            throw std::runtime_error("Address already exists");
        }
        white_list.push_back(addr);
        return white_list;
    }

    std::vector<int> del_white_list(int addr) {
        auto it = std::find(white_list.begin(), white_list.end(), addr);
        if (it == white_list.end()) {
            throw std::runtime_error("Address not found");
        }
        white_list.erase(it);
        return white_list;
    }

    std::string recv(const Message& info) {
        if (!validate_message(info)) {
            throw std::runtime_error("Invalid message format");
        }
        if (std::find(white_list.begin(), white_list.end(), info.addr) == white_list.end()) {
            return "RECEIVE_DENIED";
        }
        receive_struct = info;
        return receive_struct.content;
    }

    std::string send(const Message& info) {
        if (!validate_message(info)) {
            return "ERROR: Invalid message format";
        }
        send_struct = info;
        return "SUCCESS";
    }

    std::map<std::string, Message> show(const std::string& type) {
        std::map<std::string, Message> result;
        if (type == "send") {
            result["send"] = send_struct;
        } else if (type == "receive") {
            result["receive"] = receive_struct;
        }
        return result;
    }
};
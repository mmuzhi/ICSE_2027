#include <vector>
#include <unordered_map>
#include <string>

class Server {
private:
    std::vector<int> white_list;
    std::unordered_map<std::string, std::string> send_struct;
    std::unordered_map<std::string, std::string> receive_struct;

public:
    // Add address to whitelist if not already present
    std::vector<int> add_white_list(int addr) {
        if (std::find(white_list.begin(), white_list.end(), addr) != white_list.end()) {
            return white_list;
        }
        white_list.push_back(addr);
        return white_list;
    }

    // Remove address from whitelist if present
    std::vector<int> del_white_list(int addr) {
        auto it = std::find(white_list.begin(), white_list.end(), addr);
        if (it == white_list.end()) {
            return white_list;
        }
        white_list.erase(it);
        return white_list;
    }

    // Receive message if sender is on whitelist
    std::string recv(const std::unordered_map<std::string, std::string>& info) {
        if (info.find("addr") == info.end() || info.find("content") == info.end()) {
            return "-1";
        }
        int addr = std::stoi(info.at("addr"));
        std::string content = info.at("content");
        if (std::find(white_list.begin(), white_list.end(), addr) == white_list.end()) {
            return "False";
        }
        receive_struct = {{"addr", std::to_string(addr)}, {"content", content}};
        return content;
    }

    // Send message and store in send_struct
    std::string send(const std::unordered_map<std::string, std::string>& info) {
        if (info.find("addr") == info.end() || info.find("content") == info.end()) {
            return "info structure is not correct";
        }
        int addr = std::stoi(info.at("addr"));
        std::string content = info.at("content");
        send_struct = {{"addr", std::to_string(addr)}, {"content", content}};
        return "";
    }

    // Retrieve send or receive struct based on type
    std::unordered_map<std::string, std::string> show(const std::string& type) {
        if (type == "send") {
            return send_struct;
        } else if (type == "receive") {
            return receive_struct;
        }
        return {};
    }
};
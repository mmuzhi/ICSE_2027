#include <algorithm>
#include <map>
#include <string>
#include <variant>
#include <vector>

class Server {
public:
    using Dict = std::map<std::string, std::variant<int, std::string>>;

private:
    std::vector<int> white_list;
    Dict send_struct;
    Dict receive_struct;

public:
    Server() = default;

    std::variant<std::vector<int>, bool> add_white_list(int addr) {
        auto it = std::find(white_list.begin(), white_list.end(), addr);
        if (it != white_list.end()) {
            return false;
        }
        white_list.push_back(addr);
        return white_list;
    }

    std::variant<std::vector<int>, bool> del_white_list(int addr) {
        auto it = std::find(white_list.begin(), white_list.end(), addr);
        if (it == white_list.end()) {
            return false;
        }
        white_list.erase(it);
        return white_list;
    }

    std::variant<int, bool, std::string> recv(const Dict& info) {
        if (info.find("addr") == info.end() || info.find("content") == info.end()) {
            return -1;
        }
        int addr = std::get<int>(info.at("addr"));
        const std::string& content = std::get<std::string>(info.at("content"));

        auto it = std::find(white_list.begin(), white_list.end(), addr);
        if (it == white_list.end()) {
            return false;
        }
        receive_struct.clear();
        receive_struct["addr"] = addr;
        receive_struct["content"] = content;
        return content;
    }

    std::variant<std::monostate, std::string> send(const Dict& info) {
        if (info.find("addr") == info.end() || info.find("content") == info.end()) {
            return std::string("info structure is not correct");
        }
        send_struct.clear();
        send_struct["addr"] = info.at("addr");
        send_struct["content"] = info.at("content");
        return std::monostate{};
    }

    std::variant<Dict, bool> show(const std::string& type) {
        if (type == "send") {
            return send_struct;
        } else if (type == "receive") {
            return receive_struct;
        }
        return false;
    }
};
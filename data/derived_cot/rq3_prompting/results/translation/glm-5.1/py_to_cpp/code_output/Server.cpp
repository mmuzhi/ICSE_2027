#include <variant>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <optional>

class Server {
public:
    using Value = std::variant<int, std::string>;
    using Dict = std::map<std::string, Value>;

private:
    std::vector<int> white_list;
    Dict send_struct;
    Dict receive_struct;

public:
    Server() = default;

    std::variant<std::vector<int>, bool> add_white_list(int addr) {
        if (std::find(white_list.begin(), white_list.end(), addr) != white_list.end()) {
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

    std::variant<std::string, bool, int> recv(const Dict& info) {
        auto addr_it = info.find("addr");
        auto content_it = info.find("content");
        if (addr_it == info.end() || content_it == info.end()) {
            return -1;
        }
        if (!std::holds_alternative<int>(addr_it->second) ||
            !std::holds_alternative<std::string>(content_it->second)) {
            return false;
        }
        int addr = std::get<int>(addr_it->second);
        const std::string& content = std::get<std::string>(content_it->second);
        if (std::find(white_list.begin(), white_list.end(), addr) == white_list.end()) {
            return false;
        }
        receive_struct = {{"addr", addr}, {"content", content}};
        return content;
    }

    std::optional<std::string> send(const Dict& info) {
        auto addr_it = info.find("addr");
        auto content_it = info.find("content");
        if (addr_it == info.end() || content_it == info.end()) {
            return "info structure is not correct";
        }
        if (!std::holds_alternative<int>(addr_it->second) ||
            !std::holds_alternative<std::string>(content_it->second)) {
            return "info structure is not correct";
        }
        send_struct = {{"addr", std::get<int>(addr_it->second)},
                       {"content", std::get<std::string>(content_it->second)}};
        return std::nullopt;
    }

    std::variant<Dict, bool> show(const std::string& type) const {
        if (type == "send") {
            return send_struct;
        } else if (type == "receive") {
            return receive_struct;
        }
        return false;
    }
};
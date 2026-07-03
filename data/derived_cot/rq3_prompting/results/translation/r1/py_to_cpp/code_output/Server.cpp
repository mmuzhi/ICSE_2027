#include <vector>
#include <string>
#include <optional>
#include <variant>
#include <algorithm>
#include <iostream>

struct Info {
    int addr;
    std::string content;
};

class Server {
private:
    std::vector<int> white_list;
    std::optional<Info> send_struct;
    std::optional<Info> receive_struct;

public:
    Server() = default;

    // add_white_list: returns std::optional<std::vector<int>>
    //  - if addr already exists -> std::nullopt (False)
    //  - otherwise adds addr, returns the new whitelist
    std::optional<std::vector<int>> add_white_list(int addr) {
        if (std::find(white_list.begin(), white_list.end(), addr) != white_list.end()) {
            return std::nullopt;
        }
        white_list.push_back(addr);
        return white_list;
    }

    // del_white_list: returns std::optional<std::vector<int>>
    //  - if addr not present -> std::nullopt (False)
    //  - otherwise removes addr, returns the new whitelist
    std::optional<std::vector<int>> del_white_list(int addr) {
        auto it = std::find(white_list.begin(), white_list.end(), addr);
        if (it == white_list.end()) {
            return std::nullopt;
        }
        white_list.erase(it);
        return white_list;
    }

    // recv: takes an Info struct
    //  - if addr not in whitelist -> return false (std::optional with no value)
    //  - otherwise store in receive_struct and return the content
    //  (input validation (dict check) is omitted because C++ types enforce structure)
    std::optional<std::string> recv(const Info& info) {
        if (std::find(white_list.begin(), white_list.end(), info.addr) == white_list.end()) {
            return std::nullopt; // False
        }
        receive_struct = info;
        return info.content;
    }

    // send: takes an Info struct
    //  - stores in send_struct; returns void (no error handling for dict validity)
    void send(const Info& info) {
        send_struct = info;
    }

    // show: returns an Info or false
    //  - if type is "send" -> send_struct (may be empty = nullopt)
    //  - if type is "receive" -> receive_struct (may be empty)
    //  - otherwise -> false (bool)
    //  Return type: std::variant<std::optional<Info>, bool> allows both outcomes
    std::variant<std::optional<Info>, bool> show(const std::string& type) const {
        if (type == "send") {
            return send_struct;
        } else if (type == "receive") {
            return receive_struct;
        } else {
            return false;
        }
    }
};
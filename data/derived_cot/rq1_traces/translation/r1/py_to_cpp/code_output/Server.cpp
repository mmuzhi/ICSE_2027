#include <vector>
#include <map>
#include <variant>
#include <optional>
#include <algorithm>
#include <functional>
#include <string>
#include <stdexcept>

using Value = std::variant<int, std::string>;
using InfoDict = std::map<std::string, Value>;
using Addr = int;
using AddrList = std::vector<Addr>;
using AddrListRef = std::variant<std::reference_wrapper<AddrList>, bool>;

class Server {
    AddrList white_list;
    InfoDict send_struct;
    InfoDict receive_struct;

public:
    Server() : white_list(), send_struct(), receive_struct() {}

    AddrListRef add_white_list(Addr addr) {
        if (std::find(white_list.begin(), white_list.end(), addr) != white_list.end()) {
            return false;
        }
        white_list.push_back(addr);
        return std::ref(white_list);
    }

    AddrListRef del_white_list(Addr addr) {
        auto it = std::find(white_list.begin(), white_list.end(), addr);
        if (it == white_list.end()) {
            return false;
        }
        white_list.erase(it);
        return std::ref(white_list);
    }

    using RecvReturn = std::variant<int, bool, Value>;
    RecvReturn recv(const InfoDict& info) {
        if (info.find("addr") == info.end() || info.find("content") == info.end()) {
            return -1;
        }

        if (!std::holds_alternative<int>(info.at("addr"))) {
            return false;
        }
        int addr = std::get<int>(info.at("addr"));

        if (std::find(white_list.begin(), white_list.end(), addr) == white_list.end()) {
            return false;
        }

        receive_struct = InfoDict{ {"addr", info.at("addr")}, {"content", info.at("content")} };
        return info.at("content");
    }

    using SendReturn = std::optional<std::string>;
    SendReturn send(const InfoDict& info) {
        if (info.find("addr") == info.end() || info.find("content") == info.end()) {
            return std::string("info structure is not correct");
        }
        send_struct = InfoDict{ {"addr", info.at("addr")}, {"content", info.at("content")} };
        return std::nullopt;
    }

    using ShowReturn = std::variant<InfoDict, bool>;
    ShowReturn show(const std::string& type) {
        if (type == "send") {
            return send_struct;
        } else if (type == "receive") {
            return receive_struct;
        } else {
            return false;
        }
    }
};
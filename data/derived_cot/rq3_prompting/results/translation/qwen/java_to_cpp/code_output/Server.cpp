#include <vector>
#include <map>
#include <any>
#include <optional>
#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>

class Server {
private:
    std::vector<int> whiteList;
    std::map<std::string, std::any> sendStruct;
    std::map<std::string, std::any> receiveStruct;

public:
    Server() = default;

    std::optional<std::vector<int>> addWhiteList(int addr) {
        if (whiteList contains addr) {
            return std::nullopt;
        }
        whiteList.push_back(addr);
        return whiteList;
    }

    std::optional<std::vector<int>> delWhiteList(int addr) {
        if (!whiteList contains addr) {
            return std::nullopt;
        }
        auto it = std::find(whiteList.begin(), whiteList.end(), addr);
        if (it != whiteList.end()) {
            whiteList.erase(it);
        }
        return whiteList;
    }

    int recv(std::map<std::string, std::any> info) {
        if (info is null or missing "addr" or missing "content") {
            return -1;
        }
        try {
            int addr = std::any_cast<int>(info["addr"]);
            std::string content = std::any_cast<std::string>(info["content"]);
        } catch (const std::bad_cast& e) {
            return -1;
        }
        if (whiteList does not contain addr) {
            return false;
        }
        receiveStruct["addr"] = addr;
        receiveStruct["content"] = content;
        return std::any_cast<std::string>(receiveStruct["content"]);
    }

    std::string* send(std::map<std::string, std::any> info) {
        if (info is null or missing "addr" or missing "content") {
            return new std::string("info structure is not correct");
        }
        sendStruct["addr"] = info["addr"];
        sendStruct["content"] = info["content"];
        return new std::string();
    }

    std::map<std::string, std::any> show(std::string type) {
        if (type == "send") {
            return sendStruct;
        } else if (type == "receive") {
            return receiveStruct;
        }
        return {};
    }
};
#include <vector>
#include <unordered_map>
#include <string>
#include <any>
#include <variant>
#include <algorithm>

class Server {
private:
    std::vector<int> whiteList;
    std::unordered_map<std::string, std::any> sendStruct;
    std::unordered_map<std::string, std::any> receiveStruct;

public:
    Server() = default;

    // Returns pointer to whiteList on success, nullptr on failure.
    std::vector<int>* addWhiteList(int addr) {
        auto it = std::find(whiteList.begin(), whiteList.end(), addr);
        if (it != whiteList.end()) {
            return nullptr;
        } else {
            whiteList.push_back(addr);
            return &whiteList;
        }
    }

    // Returns pointer to whiteList on success, nullptr on failure.
    std::vector<int>* delWhiteList(int addr) {
        auto it = std::find(whiteList.begin(), whiteList.end(), addr);
        if (it == whiteList.end()) {
            return nullptr;
        } else {
            whiteList.erase(it);
            return &whiteList;
        }
    }

    // Returns int(-1), bool(false), or std::string (content).
    std::variant<int, bool, std::string> recv(std::unordered_map<std::string, std::any>* info) {
        if (info == nullptr || info->find("addr") == info->end() || info->find("content") == info->end()) {
            return -1;
        }
        int addr = std::any_cast<int>((*info)["addr"]);
        std::string content = std::any_cast<std::string>((*info)["content"]);

        auto it = std::find(whiteList.begin(), whiteList.end(), addr);
        if (it == whiteList.end()) {
            return false;
        }

        receiveStruct["addr"] = addr;
        receiveStruct["content"] = content;
        return std::any_cast<std::string>(receiveStruct["content"]);
    }

    // Returns nullptr on success, or a pointer to an error message string literal.
    const char* send(std::unordered_map<std::string, std::any>* info) {
        if (info == nullptr || info->find("addr") == info->end() || info->find("content") == info->end()) {
            return "info structure is not correct";
        }
        sendStruct["addr"] = (*info)["addr"];
        sendStruct["content"] = (*info)["content"];
        return nullptr;
    }

    // Returns pointer to the requested struct, or nullptr if type is unknown.
    std::unordered_map<std::string, std::any>* show(const std::string& type) {
        if (type == "send") {
            return &sendStruct;
        } else if (type == "receive") {
            return &receiveStruct;
        } else {
            return nullptr;
        }
    }
};
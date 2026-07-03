#include <vector>
#include <unordered_map>
#include <any>
#include <string>

class Server {
private:
    std::vector<int> whiteList;
    std::unordered_map<std::string, std::any> sendStruct;
    std::unordered_map<std::string, std::any> receiveStruct;

public:
    Server() = default;

    std::vector<int>* addWhiteList(int addr) {
        if (std::find(whiteList.begin(), whiteList.end(), addr) != whiteList.end()) {
            return nullptr;
        }
        whiteList.push_back(addr);
        return &whiteList;
    }

    std::vector<int>* delWhiteList(int addr) {
        auto it = std::find(whiteList.begin(), whiteList.end(), addr);
        if (it == whiteList.end()) {
            return nullptr;
        }
        whiteList.erase(it);
        return &whiteList;
    }

    std::any recv(std::unordered_map<std::string, std::any> info) {
        if (info.find("addr") == info.end() || info.find("content") == info.end()) {
            return -1;
        }
        int addr = std::any_cast<int>(info["addr"]);
        std::string content = std::any_cast<std::string>(info["content"]);
        if (std::find(whiteList.begin(), whiteList.end(), addr) == whiteList.end()) {
            return false;
        }
        receiveStruct["addr"] = addr;
        receiveStruct["content"] = content;
        return content;
    }

    std::string* send(std::unordered_map<std::string, std::any> info) {
        if (info.find("addr") == info.end() || info.find("content") == info.end()) {
            return new std::string("info structure is not correct");
        }
        sendStruct["addr"] = info["addr"];
        sendStruct["content"] = info["content"];
        return nullptr;
    }

    std::unordered_map<std::string, std::any>* show(std::string type) {
        if (type == "send") {
            return &sendStruct;
        } else if (type == "receive") {
            return &receiveStruct;
        }
        return nullptr;
    }
};
#include <vector>
#include <unordered_map>
#include <string>
#include <any>
#include <algorithm>

class Server {
private:
    std::vector<int> whiteList;
    std::unordered_map<std::string, std::any> sendStruct;
    std::unordered_map<std::string, std::any> receiveStruct;

public:
    Server() : whiteList(), sendStruct(), receiveStruct() {}

    std::vector<int>* addWhiteList(int addr) {
        if (std::find(whiteList.begin(), whiteList.end(), addr) != whiteList.end()) {
            return nullptr;
        } else {
            whiteList.push_back(addr);
            return &whiteList;
        }
    }

    std::vector<int>* delWhiteList(int addr) {
        auto it = std::find(whiteList.begin(), whiteList.end(), addr);
        if (it == whiteList.end()) {
            return nullptr;
        } else {
            whiteList.erase(it);
            return &whiteList;
        }
    }

    std::any recv(const std::unordered_map<std::string, std::any>* info) {
        if (info == nullptr || info->find("addr") == info->end() || info->find("content") == info->end()) {
            return std::any(-1);
        }
        int addr = std::any_cast<int>(info->at("addr"));
        std::string content = std::any_cast<std::string>(info->at("content"));
        if (std::find(whiteList.begin(), whiteList.end(), addr) == whiteList.end()) {
            return std::any(false);
        } else {
            receiveStruct["addr"] = addr;
            receiveStruct["content"] = content;
            return receiveStruct["content"];
        }
    }

    const char* send(const std::unordered_map<std::string, std::any>* info) {
        if (info == nullptr || info->find("addr") == info->end() || info->find("content") == info->end()) {
            return "info structure is not correct";
        }
        sendStruct["addr"] = info->at("addr");
        sendStruct["content"] = info->at("content");
        return nullptr;
    }

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
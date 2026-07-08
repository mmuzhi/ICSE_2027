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
    Server() = default;

    std::vector<int>* addWhiteList(int addr) {
        // whiteList.contains(addr) equivalent
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
            // Removes the first occurrence of addr
            whiteList.erase(it);
            return &whiteList;
        }
    }

    std::any recv(const std::unordered_map<std::string, std::any>* info) {
        if (info == nullptr || info->find("addr") == info->end() || info->find("content") == info->end()) {
            return -1;
        }
        
        // std::any_cast throws std::bad_any_cast if the type doesn't match, 
        // mirroring Java's ClassCastException behavior.
        int addr = std::any_cast<int>(info->at("addr"));
        std::string content = std::any_cast<std::string>(info->at("content"));
        
        if (std::find(whiteList.begin(), whiteList.end(), addr) == whiteList.end()) {
            return false;
        } else {
            receiveStruct["addr"] = addr;
            receiveStruct["content"] = content;
            return receiveStruct["content"];
        }
    }

    const std::string* send(const std::unordered_map<std::string, std::any>* info) {
        if (info == nullptr || info->find("addr") == info->end() || info->find("content") == info->end()) {
            static const std::string errorMsg = "info structure is not correct";
            return &errorMsg;
        }
        sendStruct["addr"] = info->at("addr");
        sendStruct["content"] = info->at("content");
        return nullptr;
    }

    std::unordered_map<std::string, std::any>* show(const std::string* type) {
        // Check for null to prevent dereferencing a null pointer, 
        // mirroring Java's "send".equals(type) null-safe check.
        if (type == nullptr) {
            return nullptr;
        }
        
        if (*type == "send") {
            return &sendStruct;
        } else if (*type == "receive") {
            return &receiveStruct;
        } else {
            return nullptr;
        }
    }
};
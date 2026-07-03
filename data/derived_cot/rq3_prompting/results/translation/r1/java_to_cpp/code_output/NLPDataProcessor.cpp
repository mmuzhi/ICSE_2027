#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class NLPDataProcessor {
public:
    std::vector<std::string> constructStopWordList() {
        return {"a", "an", "the"};
    }

    std::vector<std::vector<std::string>> removeStopWords(
            const std::vector<std::string>& stringList,
            const std::vector<std::string>& stopWordList) {
        std::vector<std::vector<std::string>> result;
        for (const auto& str : stringList) {
            std::vector<std::string> words = split(str);
            words.erase(
                std::remove_if(words.begin(), words.end(),
                               [&](const std::string& w) {
                                   return std::find(stopWordList.begin(), stopWordList.end(), w)
                                          != stopWordList.end();
                               }),
                words.end());
            result.push_back(words);
        }
        return result;
    }

    std::vector<std::vector<std::string>> process(const std::vector<std::string>& stringList) {
        std::vector<std::string> stopWordList = constructStopWordList();
        return removeStopWords(stringList, stopWordList);
    }

private:
    std::vector<std::string> split(const std::string& s) {
        std::vector<std::string> tokens;
        std::istringstream iss(s);
        std::string token;
        while (std::getline(iss, token, ' ')) {
            tokens.push_back(token);
        }
        // Remove trailing empty strings (Java's split omits them)
        while (!tokens.empty() && tokens.back().empty()) {
            tokens.pop_back();
        }
        return tokens;
    }
};
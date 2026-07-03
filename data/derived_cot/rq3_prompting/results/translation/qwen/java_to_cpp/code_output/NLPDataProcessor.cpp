#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class NLPDataProcessor {
public:
    static std::vector<std::string> constructStopWordList() {
        return {"a", "an", "the"};
    }

    static std::vector<std::vector<std::string>> removeStopWords(const std::vector<std::string>& stringList, const std::vector<std::string>& stopWordList) {
        std::vector<std::vector<std::string>> result;
        for (const auto& s : stringList) {
            std::vector<std::string> words;
            std::istringstream iss(s);
            std::string word;
            while (std::getline(iss, word, ' ')) {
                words.push_back(word);
            }
            for (const auto& stopWord : stopWordList) {
                auto it = std::find(words.begin(), words.end(), stopWord);
                while (it != words.end()) {
                    it = words.erase(it);
                }
            }
            result.push_back(words);
        }
        return result;
    }

    static std::vector<std::vector<std::string>> process(const std::vector<std::string>& stringList) {
        std::vector<std::string> stopWordList = constructStopWordList();
        return removeStopWords(stringList, stopWordList);
    }
};
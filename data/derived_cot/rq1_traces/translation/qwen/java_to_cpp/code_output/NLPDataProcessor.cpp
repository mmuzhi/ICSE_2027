#include <vector>
#include <string>
#include <algorithm>
#include <regex>

class NLPDataProcessor {
public:
    std::vector<std::string> constructStopWordList() {
        return {"a", "an", "the"};
    }

    std::vector<std::vector<std::string>> removeStopWords(
        const std::vector<std::string>& stringList,
        const std::vector<std::string>& stopWordList
    ) {
        std::vector<std::vector<std::string>> result;
        for (const auto& s : stringList) {
            std::regex space_regex(" ");
            auto words_begin = std::sregex_token_iterator(s.begin(), s.end(), space_regex, -1);
            auto words_end = std::sregex_token_iterator();
            std::vector<std::string> words(words_begin, words_end);

            auto it = std::remove_if(words.begin(), words.end(),
                [&stopWordList](const std::string& word) {
                    return std::find(stopWordList.begin(), stopWordList.end(), word) != stopWordList.end();
                });
            words.erase(it, words.end());
            result.push_back(words);
        }
        return result;
    }

    std::vector<std::vector<std::string>> process(const std::vector<std::string>& stringList) {
        std::vector<std::string> stopWordList = constructStopWordList();
        return removeStopWords(stringList, stopWordList);
    }
};
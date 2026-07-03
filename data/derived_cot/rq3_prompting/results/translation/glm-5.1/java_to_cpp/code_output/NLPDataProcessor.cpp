#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

class NLPDataProcessor {
public:
    std::vector<std::string> constructStopWordList() {
        return {"a", "an", "the"};
    }

    std::vector<std::vector<std::string>> removeStopWords(
        const std::vector<std::string>& stringList,
        const std::vector<std::string>& stopWordList) {

        std::unordered_set<std::string> stopSet(stopWordList.begin(), stopWordList.end());
        std::vector<std::vector<std::string>> result;

        for (const auto& str : stringList) {
            // Split by single space, mimicking Java's String.split(" ")
            std::vector<std::string> words;
            size_t start = 0;
            size_t pos;
            while ((pos = str.find(' ', start)) != std::string::npos) {
                words.push_back(str.substr(start, pos - start));
                start = pos + 1;
            }
            words.push_back(str.substr(start));

            // Java's split removes trailing empty strings
            while (!words.empty() && words.back().empty()) {
                words.pop_back();
            }

            // removeAll: erase all elements present in stopWordList
            words.erase(
                std::remove_if(words.begin(), words.end(),
                    [&](const std::string& w) { return stopSet.count(w) > 0; }),
                words.end());

            result.push_back(words);
        }
        return result;
    }

    std::vector<std::vector<std::string>> process(const std::vector<std::string>& stringList) {
        auto stopWordList = constructStopWordList();
        return removeStopWords(stringList, stopWordList);
    }
};
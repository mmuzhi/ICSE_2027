#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

class NLPDataProcessor {
public:
    std::vector<std::string> constructStopWordList() {
        return {"a", "an", "the"};
    }

    std::vector<std::vector<std::string>> removeStopWords(const std::vector<std::string>& stringList, const std::vector<std::string>& stopWordList) {
        std::vector<std::vector<std::string>> result;
        std::unordered_set<std::string> stopWordSet(stopWordList.begin(), stopWordList.end());
        
        for (const std::string& str : stringList) {
            std::vector<std::string> words = splitSpace(str);
            
            // Erase-remove idiom acts identically to Java's ArrayList.removeAll
            words.erase(std::remove_if(words.begin(), words.end(),
                                       [&stopWordSet](const std::string& word) {
                                           return stopWordSet.count(word) > 0;
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
    // Helper function to identically mimic Java's String.split(" ")
    std::vector<std::string> splitSpace(const std::string& s) {
        std::vector<std::string> words;
        std::string word;
        bool splitOccurred = false;
        
        for (char c : s) {
            if (c == ' ') {
                words.push_back(word);
                word.clear();
                splitOccurred = true;
            } else {
                word += c;
            }
        }
        words.push_back(word);
        
        // Java's split(regex) discards trailing empty strings resulting from the split,
        // but preserves the original string if no split occurred (e.g., an empty string input).
        if (splitOccurred) {
            while (!words.empty() && words.back().empty()) {
                words.pop_back();
            }
        }
        
        return words;
    }
};
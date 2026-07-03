#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <regex>
#include <sstream>
#include <cctype>

class NLPDataProcessor2 {
public:
    struct WordFrequency {
        std::string word;
        int frequency;

        WordFrequency(std::string word, int frequency) : word(std::move(word)), frequency(frequency) {}
    };

    std::vector<std::vector<std::string>> processData(const std::vector<std::string>& stringList) {
        static const std::regex nonAlphabetPattern("[^a-zA-Z\\s]");
        std::vector<std::vector<std::string>> result;
        for (const std::string& str : stringList) {
            std::string lowerStr = str;
            std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            std::string processedString = std::regex_replace(lowerStr, nonAlphabetPattern, "");
            std::vector<std::string> words;
            if (!processedString.empty()) {
                std::istringstream iss(processedString);
                std::string word;
                while (iss >> word) {
                    words.push_back(word);
                }
            }
            result.push_back(words);
        }
        return result;
    }

    std::vector<WordFrequency> calculateWordFrequency(const std::vector<std::vector<std::string>>& wordsList) {
        std::unordered_map<std::string, int> frequencyMap;
        std::unordered_map<std::string, int> orderMap;
        int index = 0;

        for (const auto& words : wordsList) {
            for (const std::string& word : words) {
                if (frequencyMap.find(word) == frequencyMap.end()) {
                    orderMap[word] = index++;
                    frequencyMap[word] = 0;
                }
                frequencyMap[word]++;
            }
        }

        std::vector<WordFrequency> wordFrequencies;
        for (const auto& entry : frequencyMap) {
            const std::string& word = entry.first;
            int freq = entry.second;
            if (freq > 1 || word == "%%%") {
                wordFrequencies.push_back(WordFrequency(word, freq));
            }
        }

        std::sort(wordFrequencies.begin(), wordFrequencies.end(),
            [&orderMap](const WordFrequency& a, const WordFrequency& b) {
                if (a.frequency != b.frequency) {
                    return a.frequency > b.frequency;
                }
                return orderMap.at(a.word) < orderMap.at(b.word);
            }
        );

        return wordFrequencies;
    }

    std::vector<WordFrequency> process(const std::vector<std::string>& stringList) {
        auto wordsList = processData(stringList);
        return calculateWordFrequency(wordsList);
    }
};
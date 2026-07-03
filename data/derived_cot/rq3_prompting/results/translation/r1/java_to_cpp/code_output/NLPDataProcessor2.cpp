#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <sstream>
#include <algorithm>
#include <map>
#include <cctype>

class NLPDataProcessor2 {
public:
    struct WordFrequency {
        std::string word;
        int frequency;

        WordFrequency(const std::string& word, int frequency)
            : word(word), frequency(frequency) {}

        std::string getWord() const { return word; }
        int getFrequency() const { return frequency; }

        bool operator==(const WordFrequency& other) const {
            return word == other.word && frequency == other.frequency;
        }

        std::string toString() const {
            return "WordFrequency{word='" + word + "', frequency=" + std::to_string(frequency) + "}";
        }

        static bool byFrequencyThenWord(const WordFrequency& a, const WordFrequency& b) {
            if (a.frequency != b.frequency)
                return a.frequency > b.frequency;
            return a.word < b.word;
        }
    };

    std::vector<std::vector<std::string>> processData(const std::vector<std::string>& stringList) {
        std::vector<std::vector<std::string>> wordsList;
        std::regex nonAlphaWhitespace("[^a-zA-Z\\s]");

        for (const auto& str : stringList) {
            std::string lower = str;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            std::string processed = std::regex_replace(lower, nonAlphaWhitespace, "");

            std::vector<std::string> words;
            if (!processed.empty()) {
                std::istringstream stream(processed);
                std::string token;
                while (stream >> token) {
                    words.push_back(token);
                }
            }
            wordsList.push_back(words);
        }
        return wordsList;
    }

    std::vector<WordFrequency> calculateWordFrequency(const std::vector<std::vector<std::string>>& wordsList) {
        std::map<std::string, int> frequencyMap;
        std::vector<std::string> order;
        std::map<std::string, int> orderMap;

        for (const auto& words : wordsList) {
            for (const auto& word : words) {
                if (frequencyMap.find(word) == frequencyMap.end()) {
                    order.push_back(word);
                    orderMap[word] = order.size() - 1;
                }
                frequencyMap[word]++;
            }
        }

        std::vector<WordFrequency> wordFrequencies;
        for (const auto& entry : frequencyMap) {
            const std::string& word = entry.first;
            int frequency = entry.second;
            if (frequency > 1 || word == "%%%") {
                wordFrequencies.emplace_back(word, frequency);
            }
        }

        std::sort(wordFrequencies.begin(), wordFrequencies.end(),
            [&orderMap](const WordFrequency& a, const WordFrequency& b) {
                if (a.frequency != b.frequency)
                    return a.frequency > b.frequency;
                return orderMap[a.word] < orderMap[b.word];
            });

        return wordFrequencies;
    }

    std::vector<WordFrequency> process(const std::vector<std::string>& stringList) {
        auto wordsList = processData(stringList);
        return calculateWordFrequency(wordsList);
    }
};
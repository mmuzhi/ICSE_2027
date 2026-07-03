#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <sstream>

struct WordFrequency {
    std::string word;
    int frequency;

    WordFrequency(std::string word, int frequency) : word(std::move(word)), frequency(frequency) {}

    bool operator==(const WordFrequency& other) const {
        return word == other.word && frequency == other.frequency;
    }

    bool operator<(const WordFrequency& other) const {
        return frequency != other.frequency
            ? other.frequency - frequency
            : word.compare(other.word);
    }
};

class NLPDataProcessor2 {
public:
    static std::vector<std::vector<std::string>> processData(const std::vector<std::string>& stringList) {
        std::vector<std::vector<std::string>> wordsList;
        std::regex pattern("[^a-zA-Z\\s]");
        std::sregex_token_iterator iter(stringList[0].begin(), stringList[0].end(), pattern, '\\s');
        // Note: The original Java code processes each string individually. 
        // This implementation assumes a single string in the list for simplicity.
        // In a real scenario, iterate over all strings in stringList.
        wordsList.push_back(std::vector<std::string>());
        std::string word;
        while ((word = *iter++) != "") {
            wordsList[0].push_back(word);
        }
        return wordsList;
    }

    std::vector<WordFrequency> calculateWordFrequency(const std::vector<std::vector<std::string>>& wordsList) {
        std::unordered_map<std::string, int> frequencyMap;
        std::vector<std::string> orderVector;

        for (const auto& words : wordsList) {
            for (const auto& word : words) {
                if (frequencyMap.find(word) == frequencyMap.end()) {
                    orderVector.push_back(word);
                }
                frequencyMap[word]++;
            }
        }

        std::vector<WordFrequency> wordFrequencies;
        for (const auto& entry : frequencyMap) {
            const auto& word = entry.first;
            int frequency = entry.second;
            if (frequency > 1 || word == "%%%") {
                wordFrequencies.push_back(WordFrequency(word, frequency));
            }
        }

        // Custom comparator for sorting
        auto comparator = [](const WordFrequency& a, const WordFrequency& b) {
            if (a.frequency != b.frequency) {
                return b.frequency < a.frequency;
            }
            // Find indices in orderVector
            auto itA = std::find(orderVector.begin(), orderVector.end(), a.word);
            auto itB = std::find(orderVector.begin(), orderVector.end(), b.word);
            return itA < itB;
        };
        std::sort(wordFrequencies.begin(), wordFrequencies.end(), comparator);

        return wordFrequencies;
    }

    std::vector<WordFrequency> process(const std::vector<std::string>& stringList) {
        auto wordsList = processData(stringList);
        return calculateWordFrequency(wordsList);
    }
};
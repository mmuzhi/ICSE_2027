#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <locale>

namespace org::example {

class NLPDataProcessor2 {

public:

    struct WordFrequency {
        std::string word;
        int frequency;

        WordFrequency(std::string word, int frequency) : word(std::move(word)), frequency(frequency) {}

        std::string getWord() const { return word; }
        int getFrequency() const { return frequency; }

        static auto byFrequencyThenWord = [](const WordFrequency& a, const WordFrequency& b) {
            if (a.frequency != b.frequency) {
                return a.frequency > b.frequency;
            }
            return a.word < b.word;
        };
    };

    static std::vector<std::vector<std::string>> processData(const std::vector<std::string>& stringList) {
        std::vector<std::vector<std::string>> wordsList;
        std::regex pattern(R"([^a-zA-Z\s])");

        for (const auto& s : stringList) {
            std::string lowerCaseStr = s;
            std::transform(lowerCaseStr.begin(), lowerCaseStr.end(), lowerCaseStr.begin(),
                [](unsigned char c) { return std::tolower(c); });

            std::string processedString(lowerCaseStr.begin(), lowerCaseStr.end(),
                [pattern](unsigned char c) {
                    return !std::regex_match(std::string(1, c), pattern) ? c : std::string(1, '\0');
                });

            std::regex wordSplitPattern("\\s+");
            std::sregex_token_iterator it(processedString.begin(), processedString.end(), wordSplitPattern);
            std::vector<std::string> words(it.end(), it.begin());

            wordsList.push_back(words);
        }

        return wordsList;
    }

    static std::vector<WordFrequency> calculateWordFrequency(const std::vector<std::vector<std::string>>& wordsList) {
        std::unordered_map<std::string, int> frequencyMap;
        std::unordered_map<std::string, int> orderMap;
        std::vector<std::string> orderVector;

        for (const auto& words : wordsList) {
            for (const auto& word : words) {
                if (orderMap.find(word) == orderMap.end()) {
                    orderMap[word] = orderVector.size();
                    orderVector.push_back(word);
                }
                frequencyMap[word]++;
            }
        }

        std::vector<WordFrequency> wordFrequencies;
        for (const auto& entry : frequencyMap) {
            const std::string& word = entry.first;
            int frequency = entry.second;
            if (frequency > 1 || word == "%%%") {
                wordFrequencies.push_back(WordFrequency(word, frequency));
            }
        }

        std::sort(wordFrequencies.begin(), wordFrequencies.end(), WordFrequency::byFrequencyThenWord);

        return wordFrequencies;
    }

    static std::vector<WordFrequency> process(const std::vector<std::string>& stringList) {
        auto wordsList = processData(stringList);
        return calculateWordFrequency(wordsList);
    }
};

} // namespace org::example
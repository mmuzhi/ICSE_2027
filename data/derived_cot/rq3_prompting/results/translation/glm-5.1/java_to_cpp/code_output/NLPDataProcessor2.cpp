#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <regex>
#include <cctype>

class WordFrequency {
public:
    const std::string word;
    const int frequency;

    WordFrequency(std::string word, int frequency)
        : word(std::move(word)), frequency(frequency) {}

    std::string getWord() const { return word; }
    int getFrequency() const { return frequency; }

    std::string toString() const {
        return "WordFrequency{word='" + word + "', frequency=" + std::to_string(frequency) + '}';
    }

    bool operator==(const WordFrequency& other) const {
        return frequency == other.frequency && word == other.word;
    }

    bool operator!=(const WordFrequency& other) const {
        return !(*this == other);
    }
};

struct WordFrequencyHash {
    size_t operator()(const WordFrequency& wf) const {
        size_t h1 = std::hash<std::string>()(wf.word);
        size_t h2 = std::hash<int>()(wf.frequency);
        return h1 ^ (h2 << 1);
    }
};

class NLPDataProcessor2 {
public:
    std::vector<std::vector<std::string>> processData(const std::vector<std::string>& stringList) {
        std::vector<std::vector<std::string>> wordsList;
        std::regex pattern("[^a-zA-Z\\s]");

        for (const std::string& str : stringList) {
            std::string lowerStr = str;
            std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                          [](unsigned char c) { return std::tolower(c); });

            std::string processedString = std::regex_replace(lowerStr, pattern, "");

            std::vector<std::string> words;
            if (!processedString.empty()) {
                std::regex wsRegex("\\s+");
                std::sregex_token_iterator it(processedString.begin(), processedString.end(), wsRegex, -1);
                std::sregex_token_iterator end;
                for (; it != end; ++it) {
                    words.push_back(it->str());
                }
                // Remove trailing empty strings to match Java's split behavior
                while (!words.empty() && words.back().empty()) {
                    words.pop_back();
                }
            }
            wordsList.push_back(words);
        }
        return wordsList;
    }

    std::vector<WordFrequency> calculateWordFrequency(const std::vector<std::vector<std::string>>& wordsList) {
        std::unordered_map<std::string, int> frequencyMap;
        std::unordered_map<std::string, int> orderMap;
        int index = 0;

        for (const auto& words : wordsList) {
            for (const std::string& word : words) {
                if (frequencyMap.find(word) == frequencyMap.end()) {
                    orderMap[word] = index++;
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
            [&orderMap](const WordFrequency& wf1, const WordFrequency& wf2) {
                if (wf2.getFrequency() != wf1.getFrequency()) {
                    return wf2.getFrequency() < wf1.getFrequency();
                }
                return orderMap.at(wf1.getWord()) < orderMap.at(wf2.getWord());
            });

        return wordFrequencies;
    }

    std::vector<WordFrequency> process(const std::vector<std::string>& stringList) {
        auto wordsList = processData(stringList);
        return calculateWordFrequency(wordsList);
    }
};
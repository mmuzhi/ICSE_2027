#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <regex>
#include <cctype>
#include <functional>

class NLPDataProcessor2 {
public:
    class WordFrequency {
    private:
        std::string word_;
        int frequency_;

    public:
        WordFrequency(const std::string& word, int frequency)
            : word_(word), frequency_(frequency) {}

        std::string getWord() const { return word_; }
        int getFrequency() const { return frequency_; }

        std::string toString() const {
            return "WordFrequency{word='" + word_ + "', frequency=" + std::to_string(frequency_) + '}';
        }

        bool equals(const WordFrequency& that) const {
            return frequency_ == that.frequency_ && word_ == that.word_;
        }

        bool operator==(const WordFrequency& that) const {
            return equals(that);
        }

        bool operator!=(const WordFrequency& that) const {
            return !equals(that);
        }

        size_t hashCode() const {
            size_t h1 = std::hash<std::string>()(word_);
            size_t h2 = std::hash<int>()(frequency_);
            return h1 ^ (h2 << 1);
        }

        static std::function<bool(const WordFrequency&, const WordFrequency&)> byFrequencyThenWord() {
            return [](const WordFrequency& wf1, const WordFrequency& wf2) {
                if (wf1.getFrequency() != wf2.getFrequency()) {
                    return wf1.getFrequency() > wf2.getFrequency();
                }
                return wf1.getWord() < wf2.getWord();
            };
        }
    };

private:
    // Replicates Java's String.split(regex) which discards trailing empty strings
    static std::vector<std::string> javaSplit(const std::string& str, const std::regex& pattern) {
        std::vector<std::string> result;
        std::sregex_token_iterator it(str.begin(), str.end(), pattern, -1);
        std::sregex_token_iterator end;
        for (; it != end; ++it) {
            result.push_back(it->str());
        }
        while (!result.empty() && result.back().empty()) {
            result.pop_back();
        }
        return result;
    }

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
                words = javaSplit(processedString, wsRegex);
            }
            wordsList.push_back(words);
        }
        return wordsList;
    }

    std::vector<WordFrequency> calculateWordFrequency(const std::vector<std::vector<std::string>>& wordsList) {
        std::unordered_map<std::string, int> frequencyMap;
        std::unordered_map<std::string, int> orderMap;
        std::vector<std::string> insertionOrder;
        int index = 0;

        for (const auto& words : wordsList) {
            for (const std::string& word : words) {
                if (frequencyMap.find(word) == frequencyMap.end()) {
                    orderMap[word] = index++;
                    insertionOrder.push_back(word);
                }
                frequencyMap[word]++;
            }
        }

        std::vector<WordFrequency> wordFrequencies;
        for (const auto& word : insertionOrder) {
            int frequency = frequencyMap[word];
            if (frequency > 1 || word == "%%%") {
                wordFrequencies.push_back(WordFrequency(word, frequency));
            }
        }

        std::sort(wordFrequencies.begin(), wordFrequencies.end(),
            [&orderMap](const WordFrequency& wf1, const WordFrequency& wf2) {
                if (wf1.getFrequency() != wf2.getFrequency()) {
                    return wf1.getFrequency() > wf2.getFrequency();
                }
                return orderMap[wf1.getWord()] < orderMap[wf2.getWord()];
            });

        return wordFrequencies;
    }

    std::vector<WordFrequency> process(const std::vector<std::string>& stringList) {
        std::vector<std::vector<std::string>> wordsList = processData(stringList);
        return calculateWordFrequency(wordsList);
    }
};
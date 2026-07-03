#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

class LongestWord {
private:
    std::vector<std::string> wordList;
    static const std::string punctuation;

    static std::string toLowerCase(const std::string& s) {
        std::string result = s;
        for (char& c : result) {
            c = std::tolower(static_cast<unsigned char>(c));
        }
        return result;
    }

    static std::string removePunctuation(const std::string& s) {
        std::string result;
        for (char c : s) {
            if (punctuation.find(c) == std::string::npos) {
                result += c;
            }
        }
        return result;
    }

public:
    LongestWord() = default;

    void addWord(const std::string& word) {
        wordList.push_back(word);
    }

    std::string findLongestWord(const std::string& sentence) {
        std::string longestWord;
        std::string processed = toLowerCase(sentence);
        processed = removePunctuation(processed);

        std::istringstream iss(processed);
        std::string word;
        while (iss >> word) {
            if (std::find(wordList.begin(), wordList.end(), word) != wordList.end() &&
                word.length() > longestWord.length()) {
                longestWord = word;
            }
        }
        return longestWord;
    }
};

const std::string LongestWord::punctuation = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

int main() {
    LongestWord longestWord;
    longestWord.addWord("A");
    longestWord.addWord("aM");
    std::cout << longestWord.findLongestWord("I am a student.") << std::endl;
    return 0;
}
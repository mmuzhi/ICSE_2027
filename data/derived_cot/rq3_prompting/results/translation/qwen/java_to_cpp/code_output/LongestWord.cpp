#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

class LongestWord {
public:
    std::vector<std::string> wordList;

    LongestWord() {}

    void addWord(const std::string& word) {
        wordList.push_back(word);
    }

    std::string findLongestWord(const std::string& sentence) {
        std::string longestWord = "";
        // Convert sentence to lowercase
        std::string cleanSentence = sentence;
        for (char& c : cleanSentence) {
            c = std::tolower(c);
        }
        // Remove punctuation
        std::string punctuation = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
        for (char p : punctuation) {
            cleanSentence.erase(std::remove(cleanSentence.begin(), cleanSentence.end(), p), cleanSentence.end());
        }
        // Split into words
        std::string word = "";
        for (char c : cleanSentence) {
            if (c == ' ') {
                if (!word.empty()) {
                    if (std::find(wordList.begin(), wordList.end(), word) != wordList.end() &&
                        word.length() > longestWord.length()) {
                        longestWord = word;
                    }
                    word = "";
                }
            } else {
                word += c;
            }
        }
        // Check last word
        if (!word.empty()) {
            if (std::find(wordList.begin(), wordList.end(), word) != wordList.end() &&
                word.length() > longestWord.length()) {
                longestWord = word;
            }
        }
        return longestWord;
    }
};

int main() {
    LongestWord longestWord;
    longestWord.addWord("A");
    longestWord.addWord("aM");
    std::cout << longestWord.findLongestWord("I am a student.") << std::endl;
    return 0;
}
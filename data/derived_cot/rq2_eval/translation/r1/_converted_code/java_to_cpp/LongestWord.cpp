#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

class LongestWord {
private:
    std::vector<std::string> wordList;

public:
    LongestWord() {}

    void add_word(std::string word) {
        wordList.push_back(word);
    }

    std::string find_longest_word(std::string sentence) {
        for (char &c : sentence) {
            c = std::tolower(c);
        }

        static const std::string punctuation = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
        std::string cleanSentence;
        for (char c : sentence) {
            if (punctuation.find(c) == std::string::npos) {
                cleanSentence.push_back(c);
            }
        }

        std::string longestWord = "";
        std::size_t start = 0;
        std::size_t end = 0;

        while (true) {
            end = cleanSentence.find(' ', start);
            std::string token = cleanSentence.substr(start, end - start);

            if (std::find(wordList.begin(), wordList.end(), token) != wordList.end()) {
                if (token.length() > longestWord.length()) {
                    longestWord = token;
                }
            }

            if (end == std::string::npos) {
                break;
            }
            start = end + 1;
        }

        return longestWord;
    }
};

int main() {
    LongestWord lw;
    lw.add_word("A");
    lw.add_word("aM");
    std::cout << lw.find_longest_word("I am a student.") << std::endl;
    return 0;
}
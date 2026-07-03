#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <algorithm>

class LongestWord {
private:
    std::vector<std::string> wordList;

public:
    void addWord(const std::string& word) {
        wordList.push_back(word);
    }

    std::string findLongestWord(std::string sentence) {
        std::string longestWord = "";
        // Convert to lower case
        std::transform(sentence.begin(), sentence.end(), sentence.begin(), ::tolower);

        // Remove punctuation (same set as Java: !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)
        // Escaped regex: [] and - placed at end to avoid range, other special chars escaped.
        std::regex punctRegex("[!\"#$%&'()*+,\\-./:;<=>?@\\[\\]^_`{|}~]");
        sentence = std::regex_replace(sentence, punctRegex, "");

        // Split by spaces (consecutive spaces produce empty tokens, like Java's split(" "))
        std::istringstream stream(sentence);
        std::string word;
        while (std::getline(stream, word, ' ')) {
            // Check if word is in wordList and longer
            if (std::find(wordList.begin(), wordList.end(), word) != wordList.end()) {
                if (word.length() > longestWord.length()) {
                    longestWord = word;
                }
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
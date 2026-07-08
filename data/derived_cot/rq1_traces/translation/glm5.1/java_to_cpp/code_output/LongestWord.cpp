#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

class LongestWord {
private:
    std::vector<std::string> wordList;

    std::string removePunctuation(const std::string& s) {
        std::string result;
        // The exact set of punctuation characters from the Java Pattern.quote string
        std::string punct = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
        for (char c : s) {
            if (punct.find(c) == std::string::npos) {
                result += c;
            }
        }
        return result;
    }

    std::vector<std::string> splitSpace(const std::string& s) {
        // Mimics Java's String.split(" ") behavior
        bool hasSpace = false;
        for (char c : s) {
            if (c == ' ') {
                hasSpace = true;
                break;
            }
        }
        // If no space is found, Java's split returns an array containing the original string
        if (!hasSpace) {
            return {s};
        }

        std::vector<std::string> tokens;
        std::string token;
        for (char c : s) {
            if (c == ' ') {
                tokens.push_back(token);
                token.clear();
            } else {
                token += c;
            }
        }
        tokens.push_back(token);

        // Java's split by default discards trailing empty strings
        while (!tokens.empty() && tokens.back().empty()) {
            tokens.pop_back();
        }
        return tokens;
    }

public:
    LongestWord() {}

    void addWord(std::string word) {
        wordList.push_back(std::move(word));
    }

    std::string findLongestWord(std::string sentence) {
        std::string longestWord = "";
        
        // sentence.toLowerCase()
        std::transform(sentence.begin(), sentence.end(), sentence.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        
        // sentence.replaceAll(...)
        sentence = removePunctuation(sentence);
        
        // sentence.split(" ")
        std::vector<std::string> words = splitSpace(sentence);
        
        // Iterating through words and finding the longest match
        for (const std::string& word : words) {
            // wordList.contains(word) && word.length() > longestWord.length()
            if (std::find(wordList.begin(), wordList.end(), word) != wordList.end() && word.length() > longestWord.length()) {
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
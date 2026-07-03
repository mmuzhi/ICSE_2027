#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

vector<string> splitSentences(const string& sentencesString) {
    vector<string> sentences;
    if (sentencesString.empty()) {
        return sentences;
    }

    string current;
    int n = sentencesString.length();
    for (int i = 0; i < n; i++) {
        if (sentencesString[i] == ' ') {
            // Check conditions for splitting
            bool shouldSplit = true;

            // Condition 1: must be preceded by '.' or '?'
            if (i > 0 && (sentencesString[i-1] == '.' || sentencesString[i-1] == '?')) {
                // Condition 2: not preceded by word, '.', word
                if (i >= 3) {
                    char c3 = sentencesString[i-3];
                    char c2 = sentencesString[i-2];
                    char c1 = sentencesString[i-1];
                    if (isLetter(c3) && c2 == '.' && isLetter(c1)) {
                        shouldSplit = false;
                    }
                }
                // Condition 3: not preceded by uppercase, lowercase, '.', space
                if (shouldSplit && i >= 4) {
                    char c4 = sentencesString[i-4];
                    char c3 = sentencesString[i-3];
                    char c2 = sentencesString[i-2];
                    char c1 = sentencesString[i-1];
                    if (isupper(c4) && islower(c3) && c2 == '.' && c1 == ' ') {
                        shouldSplit = false;
                    }
                }
            } else {
                // If not preceded by '.' or '?', but there's a space, add it to current
                current += ' ';
                continue;
            }

            if (shouldSplit) {
                sentences.push_back(current);
                current.clear();
            } else {
                current += ' ';
            }
        } else {
            current += sentencesString[i];
        }
    }

    if (!current.empty()) {
        sentences.push_back(current);
    }

    return sentences;
}

int countWords(const string& sentence) {
    if (sentence.empty()) {
        return 0;
    }

    string cleaned;
    for (char c : sentence) {
        if (isLetter(c) || c == ' ') {
            cleaned += c;
        }
    }

    if (cleaned.empty()) {
        return 0;
    }

    int count = 0;
    string word;
    for (char c : cleaned) {
        if (c == ' ') {
            if (!word.empty()) {
                count++;
                word.clear();
            }
        } else {
            word += c;
        }
    }

    if (!word.empty()) {
        count++;
    }

    return count;
}

int processTextFile(const string& sentencesString) {
    if (sentencesString.empty()) {
        return 0;
    }

    vector<string> sentences = splitSentences(sentencesString);
    int maxCount = 0;
    for (const string& sentence : sentences) {
        int count = countWords(sentence);
        if (count > maxCount) {
            maxCount = count;
        }
    }

    return maxCount;
}
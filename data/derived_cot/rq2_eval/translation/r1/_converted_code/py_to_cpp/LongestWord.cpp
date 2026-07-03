#include <vector>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

class LongestWord {
private:
    vector<string> word_list;
    string punct;

public:
    LongestWord() {
        punct = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    }

    void add_word(string word) {
        word_list.push_back(word);
    }

    string find_longest_word(string sentence) {
        for (char &c : sentence) {
            c = tolower(c);
        }

        string cleaned;
        for (char c : sentence) {
            if (punct.find(c) == string::npos) {
                cleaned += c;
            }
        }

        stringstream ss(cleaned);
        vector<string> words;
        string word_str;
        while (ss >> word_str) {
            words.push_back(word_str);
        }

        string longest = "";
        for (string w : words) {
            bool found = false;
            for (const string& dict_word : word_list) {
                if (w == dict_word) {
                    found = true;
                    break;
                }
            }
            if (found && w.length() > longest.length()) {
                longest = w;
            }
        }
        return longest;
    }
};
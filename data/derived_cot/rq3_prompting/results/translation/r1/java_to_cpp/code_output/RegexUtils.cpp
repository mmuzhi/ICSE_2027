#include <regex>
#include <string>
#include <vector>

class RegexUtils {
public:
    bool match(const std::string& pattern, const std::string& text) {
        std::regex compiled(pattern);
        return std::regex_match(text, compiled);
    }

    std::vector<std::string> findall(const std::string& pattern, const std::string& text) {
        std::vector<std::string> matches;
        std::regex compiled(pattern);
        auto it = std::sregex_iterator(text.begin(), text.end(), compiled);
        auto end = std::sregex_iterator();
        for (; it != end; ++it) {
            matches.push_back(it->str());
        }
        return matches;
    }

    std::vector<std::string> split(const std::string& pattern, const std::string& text) {
        std::vector<std::string> splits;
        std::regex compiled(pattern);
        std::sregex_token_iterator it(text.begin(), text.end(), compiled, -1);
        std::sregex_token_iterator end;
        for (; it != end; ++it) {
            splits.push_back(it->str());
        }
        return splits;
    }

    std::string sub(const std::string& pattern, const std::string& replacement, const std::string& text) {
        std::regex compiled(pattern);
        return std::regex_replace(text, compiled, replacement);
    }

    std::string generateEmailPattern() {
        return R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)";
    }

    std::string generatePhoneNumberPattern() {
        return R"(\b\d{3}-\d{3}-\d{4}\b)";
    }

    std::string generateSplitSentencesPattern() {
        return R"([.!?][\s]{1,2}(?=[A-Z]))";
    }

    std::vector<std::string> splitSentences(const std::string& text) {
        // Custom implementation because std::regex does not support lookahead.
        std::vector<std::string> result;
        std::regex delimiter(R"([.!?][\s]{1,2})");
        auto it = std::sregex_iterator(text.begin(), text.end(), delimiter);
        auto end = std::sregex_iterator();
        size_t start = 0;
        for (; it != end; ++it) {
            size_t pos = it->position();
            size_t len = it->length();
            size_t next = pos + len;
            // Only split if the character after the match is uppercase (lookahead condition).
            if (next < text.length() && std::isupper(text[next])) {
                result.push_back(text.substr(start, pos - start));
                start = next; // start after whitespace, next char is uppercase
            }
        }
        result.push_back(text.substr(start));
        return result;
    }

    bool validatePhoneNumber(const std::string& phoneNumber) {
        std::string pattern = generatePhoneNumberPattern();
        return match(pattern, phoneNumber);
    }

    std::vector<std::string> extractEmail(const std::string& text) {
        std::string pattern = generateEmailPattern();
        return findall(pattern, text);
    }
};
#include <regex>
#include <vector>
#include <string>

class RegexUtils {
public:
    bool match(const std::string& pattern, const std::string& text) {
        return std::regex_match(text, std::regex(pattern));
    }

    std::vector<std::string> findall(const std::string& pattern, const std::string& text) {
        std::vector<std::string> matches;
        std::regex compiledPattern(pattern);
        auto it = std::sregex_iterator(text.begin(), text.end(), compiledPattern);
        auto end = std::sregex_iterator();
        while (it != end) {
            matches.push_back((*it).str());
            ++it;
        }
        return matches;
    }

    std::vector<std::string> split(const std::string& pattern, const std::string& text) {
        std::vector<std::string> splits;
        std::regex compiledPattern(pattern);
        std::sregex_token_iterator iter(text.begin(), text.end(), compiledPattern, -1);
        std::sregex_token_iterator end;
        for (; iter != end; ++iter) {
            splits.push_back(*iter);
        }
        return splits;
    }

    std::string sub(const std::string& pattern, const std::string& replacement, const std::string& text) {
        std::regex compiledPattern(pattern);
        return std::regex_replace(text, compiledPattern, replacement);
    }

    static std::string generateEmailPattern() {
        return "\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b";
    }

    static std::string generatePhoneNumberPattern() {
        return "\\b\\d{3}-\\d{3}-\\d{4}\\b";
    }

    static std::string generateSplitSentencesPattern() {
        return "[.!?][\\s]{1,2}(?=[A-Z])";
    }

    std::vector<std::string> splitSentences(const std::string& text) {
        return split(generateSplitSentencesPattern(), text);
    }

    bool validatePhoneNumber(const std::string& phoneNumber) {
        return match(generatePhoneNumberPattern(), phoneNumber);
    }

    std::vector<std::string> extractEmail(const std::string& text) {
        return findall(generateEmailPattern(), text);
    }
};
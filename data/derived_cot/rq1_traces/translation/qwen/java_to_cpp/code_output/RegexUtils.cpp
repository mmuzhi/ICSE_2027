#include <regex>
#include <vector>
#include <string>

class RegexUtils {
public:
    bool match(const std::string& pattern, const std::string& text) {
        std::regex compiledPattern(pattern);
        return std::regex_match(text, compiledPattern);
    }

    std::vector<std::string> findall(const std::string& pattern, const std::string& text) {
        std::regex compiledPattern(pattern);
        std::sregex_iterator matches(text.begin(), text.end(), compiledPattern);
        std::sregex_iterator end;
        std::vector<std::string> foundMatches;
        for (; matches != end; ++matches) {
            foundMatches.push_back(*matches);
        }
        return foundMatches;
    }

    std::vector<std::string> split(const std::string& pattern, const std::string& text) {
        std::regex compiledPattern(pattern);
        std::sregex_token_iterator iter(text.begin(), text.end(), compiledPattern, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> splits;
        for (; iter != end; ++iter) {
            splits.push_back(*iter);
        }
        return splits;
    }

    std::string sub(const std::string& pattern, const std::string& replacement, const std::string& text) {
        std::regex compiledPattern(pattern);
        std::string result;
        std::regex_replace(std::back_inserter(result), text.begin(), text.end(), compiledPattern, replacement);
        return result;
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
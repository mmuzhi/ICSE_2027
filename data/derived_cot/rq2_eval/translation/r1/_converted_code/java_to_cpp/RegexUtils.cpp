#include <regex>
#include <vector>
#include <string>
#include <iterator>

class RegexUtils {
public:
    bool match(const std::string& pattern, const std::string& text) {
        std::regex compiledPattern(pattern);
        return std::regex_match(text, compiledPattern);
    }

    std::vector<std::string> findall(const std::string& pattern, const std::string& text) {
        std::regex compiledPattern(pattern);
        std::sregex_iterator matcher(text.begin(), text.end(), compiledPattern);
        std::sregex_iterator end;
        std::vector<std::string> matches;
        while (matcher != end) {
            matches.push_back((*matcher).str());
            ++matcher;
        }
        return matches;
    }

    std::vector<std::string> split(const std::string& pattern, const std::string& text) {
        std::regex compiledPattern(pattern);
        std::sregex_token_iterator it(text.begin(), text.end(), compiledPattern, -1);
        std::sregex_token_iterator end;
        return std::vector<std::string>(it, end);
    }

    std::string sub(const std::string& pattern, const std::string& replacement, const std::string& text) {
        std::regex compiledPattern(pattern);
        return std::regex_replace(text, compiledPattern, replacement);
    }

    std::string generate_email_pattern() {
        return "\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b";
    }

    std::string generate_phone_number_pattern() {
        return "\\b\\d{3}-\\d{3}-\\d{4}\\b";
    }

    std::string generate_split_sentences_pattern() {
        return "[.!?][\\s]{1,2}(?=[A-Z])";
    }

    std::vector<std::string> splitSentences(const std::string& text) {
        std::string pattern = generate_split_sentences_pattern();
        return split(pattern, text);
    }

    bool validate_phone_number(const std::string& phoneNumber) {
        std::string pattern = generate_phone_number_pattern();
        return match(pattern, phoneNumber);
    }

    std::vector<std::string> extractEmail(const std::string& text) {
        std::string pattern = generate_email_pattern();
        return findall(pattern, text);
    }
};
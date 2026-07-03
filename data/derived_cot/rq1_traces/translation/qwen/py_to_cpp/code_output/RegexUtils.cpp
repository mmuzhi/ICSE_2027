#include <regex>
#include <vector>
#include <string>

class RegexUtils {
public:
    bool match(const std::string& pattern, const std::string& text) {
        std::regex re(pattern);
        std::smatch match_result;
        return std::regex_search(text, match_result, re) && match_result.position() == 0;
    }

    std::vector<std::string> findall(const std::string& pattern, const std::string& text) {
        std::regex re(pattern);
        std::sregex_iterator it(text.begin(), text.end(), re);
        std::sregex_iterator end;
        std::vector<std::string> matches;
        while (it != end) {
            matches.push_back(*it);
            ++it;
        }
        return matches;
    }

    std::vector<std::string> split(const std::string& pattern, const std::string& text) {
        std::regex re(pattern);
        std::sregex_token_iterator it(text.begin(), text.end(), re, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> parts;
        for (; it != end; ++it) {
            parts.push_back(*it);
        }
        return parts;
    }

    std::string sub(const std::string& pattern, const std::string& replacement, const std::string& text) {
        std::regex re(pattern);
        return std::regex_replace(text, re, replacement);
    }

    std::string generate_email_pattern() {
        return R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)";
    }

    std::string generate_phone_number_pattern() {
        return R"(\b\d{3}-\d{3}-\d{4}\b)";
    }

    std::string generate_split_sentences_pattern() {
        return R"([.!?][\s]{1,2}(?=[A-Z]))";
    }

    std::vector<std::string> split_sentences(const std::string& text) {
        std::string pattern = generate_split_sentences_pattern();
        return split(pattern, text);
    }

    bool validate_phone_number(const std::string& phone_number) {
        std::string pattern = generate_phone_number_pattern();
        return match(pattern, phone_number);
    }

    std::vector<std::string> extract_email(const std::string& text) {
        std::string pattern = generate_email_pattern();
        return findall(pattern, text);
    }
};
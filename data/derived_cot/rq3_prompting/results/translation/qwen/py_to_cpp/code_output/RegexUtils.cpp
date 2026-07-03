#include <regex>
#include <vector>
#include <string>
#include <stdexcept>

class RegexUtils {
public:
    bool match(const std::string& pattern, const std::string& text) {
        try {
            std::regex regex_pattern(pattern);
            std::smatch match_result;
            bool found = std::regex_search(text, match_result, regex_pattern);
            if (!found) {
                return false;
            }
            return match_result.position() == 0;
        } catch (const std::regex_error& e) {
            throw std::runtime_error("Invalid regex pattern: " + pattern);
        }
    }

    std::vector<std::string> findall(const std::string& pattern, const std::string& text) {
        try {
            std::regex regex_pattern(pattern);
            std::sregex_iterator iter(text.begin(), text.end(), regex_pattern);
            std::sregex_iterator end;
            std::vector<std::string> matches;
            for (; iter != end; ++iter) {
                matches.push_back(*iter);
            }
            return matches;
        } catch (const std::regex_error& e) {
            throw std::runtime_error("Invalid regex pattern: " + pattern);
        }
    }

    std::vector<std::string> split(const std::string& pattern, const std::string& text) {
        try {
            std::regex regex_pattern(pattern);
            std::vector<std::string> result;
            std::sregex_token_iterator iter(text.begin(), text.end(), regex_pattern, -1);
            std::sregex_token_iterator end;
            for (; iter != end; ++iter) {
                result.push_back(*iter);
            }
            return result;
        } catch (const std::regex_error& e) {
            throw std::runtime_error("Invalid regex pattern: " + pattern);
        }
    }

    std::string sub(const std::string& pattern, const std::string& replacement, const std::string& text) {
        try {
            std::regex regex_pattern(pattern);
            return std::regex_replace(text, regex_pattern, replacement);
        } catch (const std::regex_error& e) {
            throw std::runtime_error("Invalid regex pattern: " + pattern);
        }
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
        try {
            std::string pattern = generate_phone_number_pattern();
            return match(pattern, phone_number);
        } catch (const std::exception& e) {
            return false;
        }
    }

    std::vector<std::string> extract_email(const std::string& text) {
        try {
            std::string pattern = generate_email_pattern();
            return findall(pattern, text);
        } catch (const std::exception& e) {
            return {};
        }
    }
};
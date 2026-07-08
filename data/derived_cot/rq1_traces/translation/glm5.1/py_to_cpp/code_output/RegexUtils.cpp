#include <string>
#include <vector>
#include <regex>

class RegexUtils {
public:
    bool match(const std::string& pattern, const std::string& text) const {
        std::regex re(pattern);
        std::smatch match;
        // re.match in Python only checks for a match at the beginning of the string.
        if (std::regex_search(text, match, re)) {
            return match.position() == 0;
        }
        return false;
    }

    std::vector<std::string> findall(const std::string& pattern, const std::string& text) const {
        std::vector<std::string> result;
        std::regex re(pattern);
        auto it = std::sregex_iterator(text.begin(), text.end(), re);
        auto end = std::sregex_iterator();
        for (; it != end; ++it) {
            result.push_back(it->str());
        }
        return result;
    }

    std::vector<std::string> split(const std::string& pattern, const std::string& text) const {
        std::vector<std::string> result;
        std::regex re(pattern);
        // -1 iterates over the parts of the string that do not match the regex,
        // which correctly replicates Python's re.split behavior including empty strings at the ends.
        auto it = std::sregex_token_iterator(text.begin(), text.end(), re, -1);
        auto end = std::sregex_token_iterator();
        for (; it != end; ++it) {
            result.push_back(it->str());
        }
        return result;
    }

    std::string sub(const std::string& pattern, const std::string& replacement, const std::string& text) const {
        std::regex re(pattern);
        return std::regex_replace(text, re, replacement);
    }

    std::string generate_email_pattern() const {
        return R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)";
    }

    std::string generate_phone_number_pattern() const {
        return R"(\b\d{3}-\d{3}-\d{4}\b)";
    }

    std::string generate_split_sentences_pattern() const {
        return R"([.!?][\s]{1,2}(?=[A-Z]))";
    }

    std::vector<std::string> split_sentences(const std::string& text) const {
        std::string pattern = generate_split_sentences_pattern();
        return split(pattern, text);
    }

    bool validate_phone_number(const std::string& phone_number) const {
        std::string pattern = generate_phone_number_pattern();
        return match(pattern, phone_number);
    }

    std::vector<std::string> extract_email(const std::string& text) const {
        std::string pattern = generate_email_pattern();
        return findall(pattern, text);
    }
};
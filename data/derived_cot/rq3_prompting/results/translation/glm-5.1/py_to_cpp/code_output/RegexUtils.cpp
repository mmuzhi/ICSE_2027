#include <string>
#include <vector>
#include <regex>

class RegexUtils {
public:
    bool match(const std::string& pattern, const std::string& text) {
        std::regex e(pattern);
        std::smatch m;
        if (std::regex_search(text, m, e)) {
            return m.position() == 0;
        }
        return false;
    }

    std::vector<std::string> findall(const std::string& pattern, const std::string& text) {
        std::regex e(pattern);
        std::vector<std::string> result;
        auto it = std::sregex_iterator(text.begin(), text.end(), e);
        auto end = std::sregex_iterator();
        for (; it != end; ++it) {
            result.push_back(it->str());
        }
        return result;
    }

    std::vector<std::string> split(const std::string& pattern, const std::string& text) {
        std::regex e(pattern);
        std::vector<std::string> result;
        std::regex_token_iterator<std::string::const_iterator> it(text.begin(), text.end(), e, -1);
        std::regex_token_iterator<std::string::const_iterator> end;
        for (; it != end; ++it) {
            result.push_back(it->str());
        }
        return result;
    }

    std::string sub(const std::string& pattern, const std::string& replacement, const std::string& text) {
        std::regex e(pattern);
        return std::regex_replace(text, e, replacement);
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
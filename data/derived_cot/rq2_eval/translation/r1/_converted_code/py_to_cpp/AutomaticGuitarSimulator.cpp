#include <string>
#include <vector>
#include <cctype>

struct PlayItem {
    std::string Chord;
    std::string Tune;
};

class AutomaticGuitarSimulator {
private:
    std::string play_text;

public:
    AutomaticGuitarSimulator(std::string text) : play_text(std::move(text)) {}

    std::vector<PlayItem> interpret(bool display = false) const {
        if (play_text.find_first_not_of(" \t\n\r\v\f") == std::string::npos) {
            return {};
        }

        std::vector<PlayItem> play_list;
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = play_text.find(' ', start);

        while (end != std::string::npos) {
            tokens.push_back(play_text.substr(start, end - start));
            start = end + 1;
            end = play_text.find(' ', start);
        }
        tokens.push_back(play_text.substr(start));

        for (const auto& token : tokens) {
            size_t i = 0;
            while (i < token.size() && std::isalpha(static_cast<unsigned char>(token[i]))) {
                i++;
            }
            std::string chord = token.substr(0, i);
            std::string tune = token.substr(i);
            play_list.push_back({chord, tune});
            if (display) {
                format_display(chord, tune);
            }
        }

        return play_list;
    }

    std::string format_display(const std::string& key, const std::string& value) const {
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value;
    }
};
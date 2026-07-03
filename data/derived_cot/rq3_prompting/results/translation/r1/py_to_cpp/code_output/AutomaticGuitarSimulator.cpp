#include <string>
#include <vector>
#include <sstream>
#include <cctype>

struct PlayEntry {
    std::string chord;
    std::string tune;
};

class AutomaticGuitarSimulator {
private:
    std::string play_text;

    // Helper to trim leading and trailing whitespace (spaces, tabs, newlines)
    static std::string trim(const std::string& s) {
        size_t start = s.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(" \t\n\r");
        return s.substr(start, end - start + 1);
    }

public:
    AutomaticGuitarSimulator(const std::string& text) : play_text(text) {}

    std::vector<PlayEntry> interpret(bool display = false) {
        std::string trimmed = trim(play_text);
        if (trimmed.empty()) {
            return {};
        }

        std::vector<PlayEntry> play_list;
        std::istringstream iss(trimmed);
        std::string segment;
        // Split by single space (consecutive spaces produce empty segments)
        while (std::getline(iss, segment, ' ')) {
            // Find where letters end
            size_t pos = 0;
            while (pos < segment.size() && std::isalpha(segment[pos])) {
                ++pos;
            }
            std::string chord = segment.substr(0, pos);
            std::string tune = segment.substr(pos);
            play_list.push_back({chord, tune});
            if (display) {
                display(chord, tune); // return value ignored
            }
        }
        return play_list;
    }

    std::string display(const std::string& key, const std::string& value) const {
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value;
    }
};
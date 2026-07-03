#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

namespace org {
namespace example {

class AutomaticGuitarSimulator {
private:
    std::string playText;

    // Custom trim function to remove leading and trailing whitespace
    static std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\n\r\f\v");
        size_t end = str.find_last_not_of(" \t\n\r\f\v");
        if (start == std::string::npos) return "";
        return str.substr(start, (end - start + 1));
    }

    // Nested ChordTune struct
    struct ChordTune {
        std::string chord;
        std::string tune;

        ChordTune(const std::string& chord, const std::string& tune)
            : chord(chord), tune(tune) {}

        bool operator==(const ChordTune& other) const {
            return chord == other.chord && tune == other.tune;
        }
    };

    // Display function
    std::string display(const std::string& key, const std::string& value) const {
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value;
    }

public:
    explicit AutomaticGuitarSimulator(const std::string& text) : playText(text) {}

    std::vector<ChordTune> interpret(bool display) {
        if (playText.empty() || trim(playText).empty()) {
            return {};
        }

        std::vector<ChordTune> playList;
        std::istringstream iss(playText);
        std::string token;

        while (iss >> token) {
            size_t pos = 0;
            while (pos < token.size() && std::isalpha(static_cast<unsigned char>(token[pos]))) {
                ++pos;
            }

            if (pos == 0) {
                // No alphabetic characters found, skip this token
                continue;
            }

            std::string playChord = token.substr(0, pos);
            std::string playValue = token.substr(pos);
            playList.push_back(ChordTune(playChord, playValue));

            if (display) {
                display(playChord, playValue);
            }
        }

        return playList;
    }
};
} // namespace example
} // namespace org
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>

struct ChordTune {
    std::string chord;
    std::string tune;
};

class AutomaticGuitarSimulator {
private:
    std::string play_text;

    bool isAllWhitespace(const std::string& str) {
        if (str.empty()) return true;
        for (char c : str) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                return false;
            }
        }
        return true;
    }

public:
    explicit AutomaticGuitarSimulator(const std::string& text) : play_text(text) {}

    std::vector<ChordTune> interpret(bool display = false) {
        if (play_text.empty() || isAllWhitespace(play_text)) {
            return {};
        }

        std::vector<ChordTune> play_list;
        std::istringstream iss(play_text);
        std::string play_seg;

        while (std::getline(iss, play_seg, ' ')) {
            if (play_seg.empty()) {
                continue;
            }

            size_t pos = 0;
            for (size_t i = 0; i < play_seg.size(); ++i) {
                if (!std::isalpha(static_cast<unsigned char>(play_seg[i]))) {
                    pos = i;
                    break;
                }
            }

            std::string chord = play_seg.substr(0, pos);
            std::string tune = play_seg.substr(pos);

            play_list.push_back({chord, tune});

            if (display) {
                format_display(chord, tune);
            }
        }

        return play_list;
    }

    std::string format_display(const std::string& key, const std::string& value) {
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value;
    }
};
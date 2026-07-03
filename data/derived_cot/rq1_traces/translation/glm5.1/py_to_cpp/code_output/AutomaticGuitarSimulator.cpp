#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>

class AutomaticGuitarSimulator {
private:
    std::string play_text;

public:
    AutomaticGuitarSimulator(std::string text) : play_text(std::move(text)) {}

    std::vector<std::map<std::string, std::string>> interpret(bool display_flag = false) {
        // Check if the string is empty or contains only whitespace
        if (std::all_of(play_text.begin(), play_text.end(), [](unsigned char c) { return std::isspace(c); })) {
            return {};
        }

        std::vector<std::map<std::string, std::string>> play_list;
        std::vector<std::string> play_segs;
        std::string current_seg;

        // Mimic Python's split(" ") exactly, preserving empty strings from consecutive spaces
        for (char c : play_text) {
            if (c == ' ') {
                play_segs.push_back(current_seg);
                current_seg.clear();
            } else {
                current_seg += c;
            }
        }
        play_segs.push_back(current_seg);

        for (const std::string& play_seg : play_segs) {
            int pos = 0;
            for (char ele : play_seg) {
                if (std::isalpha(static_cast<unsigned char>(ele))) {
                    pos += 1;
                    continue;
                }
                break;
            }
            
            std::string play_chord = play_seg.substr(0, pos);
            std::string play_value = play_seg.substr(pos);
            
            play_list.push_back({{"Chord", play_chord}, {"Tune", play_value}});
            
            if (display_flag) {
                this->display(play_chord, play_value);
            }
        }
        return play_list;
    }

    std::string display(const std::string& key, const std::string& value) {
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value;
    }
};
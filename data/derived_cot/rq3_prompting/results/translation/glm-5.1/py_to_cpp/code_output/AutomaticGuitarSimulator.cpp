#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

class AutomaticGuitarSimulator {
private:
    std::string play_text;

    std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = s.find(delim);
        while (end != std::string::npos) {
            tokens.push_back(s.substr(start, end - start));
            start = end + 1;
            end = s.find(delim, start);
        }
        tokens.push_back(s.substr(start));
        return tokens;
    }

public:
    AutomaticGuitarSimulator(std::string text) : play_text(std::move(text)) {}

    std::vector<std::map<std::string, std::string>> interpret(bool display_flag = false) {
        std::string stripped = play_text;
        stripped.erase(stripped.begin(), std::find_if(stripped.begin(), stripped.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        stripped.erase(std::find_if(stripped.rbegin(), stripped.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), stripped.end());

        if (stripped.empty()) {
            return {};
        }

        std::vector<std::map<std::string, std::string>> play_list;
        std::vector<std::string> play_segs = split(play_text, ' ');

        for (const auto& play_seg : play_segs) {
            size_t pos = 0;
            for (char ele : play_seg) {
                if (std::isalpha(static_cast<unsigned char>(ele))) {
                    pos += 1;
                    continue;
                }
                break;
            }
            std::string play_chord = play_seg.substr(0, pos);
            std::string play_value = play_seg.substr(pos);
            
            std::map<std::string, std::string> item;
            item["Chord"] = play_chord;
            item["Tune"] = play_value;
            play_list.push_back(item);

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
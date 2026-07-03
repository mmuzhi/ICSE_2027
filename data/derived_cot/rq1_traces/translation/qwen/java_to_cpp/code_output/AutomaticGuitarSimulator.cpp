#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <iostream>

class AutomaticGuitarSimulator {
private:
    std::string playText;

public:
    AutomaticGuitarSimulator(const std::string& text) : playText(text) {}

    std::vector<ChordTune> interpret(bool display) {
        if (playText.empty() || playText.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
            return std::vector<ChordTune>();
        }

        std::vector<ChordTune> playList;
        std::istringstream iss(playText);
        std::string playSeg;
        while (iss >> playSeg) {
            if (playSeg.empty()) {
                continue;
            }
            size_t pos = 0;
            while (pos < playSeg.length() && std::isalpha(playSeg[pos])) {
                pos++;
            }
            std::string playChord = playSeg.substr(0, pos);
            std::string playValue = playSeg.substr(pos);
            playList.push_back(ChordTune(playChord, playValue));
            if (display) {
                display(playChord, playValue);
            }
        }
        return playList;
    }

    std::string display(const std::string& key, const std::string& value) {
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value;
    }

    class ChordTune {
    private:
        std::string chord;
        std::string tune;

    public:
        ChordTune(const std::string& chord, const std::string& tune) : chord(chord), tune(tune) {}

        const std::string& getChord() const { return chord; }
        const std::string& getTune() const { return tune; }

        bool operator==(const ChordTune& other) const {
            return chord == other.chord && tune == other.tune;
        }

        struct Hash {
            size_t operator()(const ChordTune& ct) const {
                auto hash1 = std::hash<std::string>{}(ct.chord);
                auto hash2 = std::hash<std::string>{}(ct.tune);
                return hash1 ^ (hash2 << 1);
            }
        };
    };
};
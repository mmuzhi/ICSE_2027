#include <vector>
#include <memory>
#include <optional>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <cstdint>
#include <iostream>

class AutomaticGuitarSimulator {
private:
    std::optional<std::string> playTextOpt;

    static void trim(std::string &s) {
        if (s.empty()) return;
        auto it = std::find_if_not(s.begin(), s.end(), [](unsigned char c) {
            return std::isspace(c);
        });
        s.erase(s.begin(), it);

        if (s.empty()) return;
        auto rit = std::find_if_not(s.rbegin(), s.rend(), [](unsigned char c) {
            return std::isspace(c);
        });
        s.erase(rit.base(), s.end());
    }

    static int32_t javaStringHash(const std::string &s) {
        uint32_t hash = 0;
        for (char c : s) {
            hash = 31 * hash + static_cast<unsigned char>(c);
        }
        return static_cast<int32_t>(hash);
    }

public:
    class ChordTune {
    private:
        std::string chord;
        std::string tune;

    public:
        ChordTune(const std::string &chord, const std::string &tune)
            : chord(chord), tune(tune) {}

        std::string getChord() const {
            return chord;
        }

        std::string getTune() const {
            return tune;
        }

        bool operator==(const ChordTune &other) const {
            return chord == other.chord && tune == other.tune;
        }

        int hashCode() const {
            int32_t chordHash = javaStringHash(chord);
            int32_t tuneHash = javaStringHash(tune);
            uint32_t temp = static_cast<uint32_t>(chordHash) * 31 + static_cast<uint32_t>(tuneHash);
            return static_cast<int32_t>(temp);
        }
    };

    AutomaticGuitarSimulator(const std::string *text) {
        if (text) {
            playTextOpt = *text;
        } else {
            playTextOpt = std::nullopt;
        }
    }

    std::unique_ptr<std::vector<ChordTune>> interpret(bool display) {
        if (!playTextOpt) {
            return nullptr;
        }
        std::string trimmed = *playTextOpt;
        trim(trimmed);
        if (trimmed.empty()) {
            return nullptr;
        }

        std::vector<ChordTune> playList;
        std::istringstream iss(*playTextOpt);
        std::string seg;
        while (std::getline(iss, seg, ' ')) {
            std::string trimmedSeg = seg;
            trim(trimmedSeg);
            if (trimmedSeg.empty()) {
                continue;
            }

            size_t pos = 0;
            for (char c : seg) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    pos++;
                } else {
                    break;
                }
            }

            std::string playChord = seg.substr(0, pos);
            std::string playValue = seg.substr(pos);
            playList.push_back(ChordTune(playChord, playValue));

            if (display) {
                this->display(playChord, playValue);
            }
        }

        return std::make_unique<std::vector<ChordTune>>(playList);
    }

    std::string display(const std::string &key, const std::string &value) {
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value;
    }
};
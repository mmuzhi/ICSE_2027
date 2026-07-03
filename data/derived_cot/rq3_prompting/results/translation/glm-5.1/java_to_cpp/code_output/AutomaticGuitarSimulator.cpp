#pragma once
#include <string>
#include <vector>
#include <optional>
#include <cctype>
#include <sstream>
#include <functional>

class AutomaticGuitarSimulator {
public:
    class ChordTune {
    public:
        std::string chord;
        std::string tune;

        ChordTune(std::string chord, std::string tune)
            : chord(std::move(chord)), tune(std::move(tune)) {}

        const std::string& getChord() const { return chord; }
        const std::string& getTune() const { return tune; }

        bool operator==(const ChordTune& that) const {
            return chord == that.chord && tune == that.tune;
        }

        int hashCode() const {
            int result = static_cast<int>(std::hash<std::string>{}(chord));
            result = 31 * result + static_cast<int>(std::hash<std::string>{}(tune));
            return result;
        }
    };

private:
    std::optional<std::string> playText;

    static bool isWhitespaceOnly(const std::string& s) {
        for (char c : s) {
            if (!std::isspace(static_cast<unsigned char>(c))) return false;
        }
        return true;
    }

public:
    AutomaticGuitarSimulator(std::optional<std::string> text)
        : playText(std::move(text)) {}

    std::optional<std::vector<ChordTune>> interpret(bool displayFlag) {
        if (!playText.has_value() || isWhitespaceOnly(playText.value())) {
            return std::nullopt;
        }

        std::vector<ChordTune> playList;
        std::istringstream iss(playText.value());
        std::string playSeg;
        while (iss >> playSeg) {
            if (playSeg.empty()) continue;

            int pos = 0;
            for (char ele : playSeg) {
                if (std::isalpha(static_cast<unsigned char>(ele))) {
                    pos++;
                    continue;
                }
                break;
            }
            std::string playChord = playSeg.substr(0, pos);
            std::string playValue = playSeg.substr(pos);
            playList.emplace_back(playChord, playValue);
            if (displayFlag) {
                display(playChord, playValue);
            }
        }
        return playList;
    }

    std::string display(const std::string& key, const std::string& value) {
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value;
    }
};
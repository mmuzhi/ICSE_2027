#ifndef AUTOMATIC_GUITAR_SIMULATOR_H
#define AUTOMATIC_GUITAR_SIMULATOR_H

#include <string>
#include <vector>
#include <optional>
#include <cctype>
#include <sstream>
#include <functional>

class AutomaticGuitarSimulator {
public:
    class ChordTune {
    private:
        std::string chord;
        std::string tune;

    public:
        ChordTune(const std::string& chord, const std::string& tune)
            : chord(chord), tune(tune) {}

        std::string getChord() const {
            return chord;
        }

        std::string getTune() const {
            return tune;
        }

        bool operator==(const ChordTune& that) const {
            return chord == that.chord && tune == that.tune;
        }

        bool operator!=(const ChordTune& that) const {
            return !(*this == that);
        }

        struct Hash {
            size_t operator()(const ChordTune& ct) const {
                size_t result = std::hash<std::string>{}(ct.chord);
                result = 31 * result + std::hash<std::string>{}(ct.tune);
                return result;
            }
        };

    private:
        // Mirrors Java's Object.hashCode() for the chord field
        static int javaStringHashCode(const std::string& s) {
            int h = 0;
            for (char c : s) {
                h = 31 * h + static_cast<int>(c);
            }
            return h;
        }

    public:
        int hashCode() const {
            int result = javaStringHashCode(chord);
            result = 31 * result + javaStringHashCode(tune);
            return result;
        }
    };

private:
    std::string playText;

    static std::string trim(const std::string& s) {
        size_t start = s.find_first_not_of(" \t\n\r\f\v");
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(" \t\n\r\f\v");
        return s.substr(start, end - start + 1);
    }

    static std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> tokens;
        std::istringstream iss(s);
        std::string token;
        while (std::getline(iss, token, delim)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static bool isLetter(char c) {
        return std::isalpha(static_cast<unsigned char>(c)) != 0;
    }

public:
    AutomaticGuitarSimulator(const std::string& text) : playText(text) {}

    std::optional<std::vector<ChordTune>> interpret(bool display) {
        if (playText.empty() || trim(playText).empty()) {
            return std::nullopt;
        }

        std::vector<ChordTune> playList;
        std::vector<std::string> playSegs = split(playText, ' ');
        for (const std::string& playSeg : playSegs) {
            if (trim(playSeg).empty()) {
                continue;
            }
            int pos = 0;
            for (char ele : playSeg) {
                if (isLetter(ele)) {
                    pos++;
                    continue;
                }
                break;
            }
            std::string playChord = playSeg.substr(0, pos);
            std::string playValue = playSeg.substr(pos);
            playList.emplace_back(playChord, playValue);
            if (display) {
                this->display(playChord, playValue);
            }
        }
        return playList;
    }

    std::string display(const std::string& key, const std::string& value) {
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value;
    }
};

#endif
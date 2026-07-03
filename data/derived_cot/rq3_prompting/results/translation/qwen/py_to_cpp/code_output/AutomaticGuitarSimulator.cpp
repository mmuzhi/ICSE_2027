#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

struct ChordTune {
    std::string chord;
    std::string tune;
};

class AutomaticGuitarSimulator {
private:
    std::string play_text;

public:
    explicit AutomaticGuitarSimulator(const std::string& text) : play_text(text) {}

    std::vector<ChordTune> interpret(bool display = false) {
        if (play_text.empty()) {
            return {};
        }

        std::istringstream iss(play_text);
        std::string token;
        std::vector<std::string> tokens;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            return {};
        }

        std::vector<ChordTune> result;
        for (const auto& t : tokens) {
            size_t pos = 0;
            while (pos < t.size() && std::isalpha(static_cast<unsigned char>(t[pos]))) {
                pos++;
            }

            std::string chord = t.substr(0, pos);
            std::string tune = t.substr(pos);

            result.push_back({chord, tune});

            if (display) {
                display(chord, tune);
            }
        }

        return result;
    }

    void display(const std::string& key, const std::string& value) {
        std::cout << "Normal Guitar Playing -- Chord: " << key << ", Play Tune: " << value << std::endl;
    }
};
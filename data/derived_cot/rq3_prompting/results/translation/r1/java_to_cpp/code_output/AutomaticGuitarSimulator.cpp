#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <optional>
#include <algorithm>
#include <functional>

class AutomaticGuitarSimulator {
public:
    // ChordTune nested class
    class ChordTune {
    public:
        ChordTune() = default;
        ChordTune(const std::string& chord, const std::string& tune)
            : chord_(chord), tune_(tune) {}

        const std::string& getChord() const { return chord_; }
        const std::string& getTune() const { return tune_; }

        bool operator==(const ChordTune& other) const {
            return chord_ == other.chord_ && tune_ == other.tune_;
        }

        bool operator!=(const ChordTune& other) const {
            return !(*this == other);
        }

    private:
        std::string chord_;
        std::string tune_;
    };

    AutomaticGuitarSimulator(const std::string& text) : playText_(text) {}

    std::optional<std::vector<ChordTune>> interpret(bool display) {
        // Trim leading/trailing whitespace (equivalent to Java's trim())
        std::string trimmed = trim(playText_);
        if (trimmed.empty()) {
            return std::nullopt;
        }

        std::vector<ChordTune> playList;
        std::istringstream stream(trimmed);
        std::string token;
        while (stream >> token) {
            if (token.empty()) continue; // safety, not strictly needed

            // Find position of first non-letter character
            size_t pos = 0;
            while (pos < token.size() && std::isalpha(static_cast<unsigned char>(token[pos]))) {
                ++pos;
            }
            std::string playChord = token.substr(0, pos);
            std::string playValue = token.substr(pos);

            playList.emplace_back(playChord, playValue);
            if (display) {
                display(playChord, playValue); // return value intentionally ignored
            }
        }
        return playList;
    }

    // Returns a formatted string (identical to Java display, no side effects)
    std::string display(const std::string& key, const std::string& value) const {
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value;
    }

private:
    std::string playText_;

    // Helper to trim whitespace (spaces, tabs, etc.) from both ends
    static std::string trim(const std::string& str) {
        auto front = std::find_if_not(str.begin(), str.end(), [](unsigned char ch) {
            return std::isspace(ch);
        });
        auto back = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char ch) {
            return std::isspace(ch);
        }).base();
        return (front < back) ? std::string(front, back) : std::string();
    }
};

// Specialize std::hash for ChordTune if needed (not used in original Java, but provided for completeness)
namespace std {
    template<>
    struct hash<AutomaticGuitarSimulator::ChordTune> {
        size_t operator()(const AutomaticGuitarSimulator::ChordTune& ct) const {
            size_t h1 = hash<string>()(ct.getChord());
            size_t h2 = hash<string>()(ct.getTune());
            return h1 ^ (h2 << 1); // similar to Java's 31 * result + tune.hashCode()
        }
    };
}
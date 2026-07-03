#include <vector>
#include <string>
#include <optional>
#include <variant>
#include <algorithm>
#include <random>
#include <stdexcept>

class MusicPlayer {
public:
    std::vector<std::string> playlist;
    std::optional<std::string> current_song;
    int volume;

    MusicPlayer() : playlist(), current_song(std::nullopt), volume(50) {}

    void add_song(const std::string& song) {
        playlist.push_back(song);
    }

    void remove_song(const std::string& song) {
        auto it = std::find(playlist.begin(), playlist.end(), song);
        if (it != playlist.end()) {
            playlist.erase(it);
            if (current_song.has_value() && current_song.value() == song) {
                stop();
            }
        }
    }

    // Returns: string (playlist[0]), false, or monostate (None)
    std::variant<std::string, bool, std::monostate> play() {
        if (!playlist.empty() && current_song.has_value() && !current_song.value().empty()) {
            return playlist[0];
        } else if (!playlist.empty()) {
            return false;
        }
        return std::monostate{};
    }

    bool stop() {
        if (current_song.has_value() && !current_song.value().empty()) {
            current_song = std::nullopt;
            return true;
        }
        return false;
    }

    bool switch_song() {
        if (current_song.has_value() && !current_song.value().empty()) {
            auto it = std::find(playlist.begin(), playlist.end(), current_song.value());
            if (it == playlist.end()) {
                throw std::runtime_error("ValueError: current_song not in playlist");
            }
            size_t current_index = static_cast<size_t>(std::distance(playlist.begin(), it));
            if (current_index < playlist.size() - 1) {
                current_song = playlist[current_index + 1];
                return true;
            }
            return false;
        }
        return false;
    }

    bool previous_song() {
        if (current_song.has_value() && !current_song.value().empty()) {
            auto it = std::find(playlist.begin(), playlist.end(), current_song.value());
            if (it == playlist.end()) {
                throw std::runtime_error("ValueError: current_song not in playlist");
            }
            size_t current_index = static_cast<size_t>(std::distance(playlist.begin(), it));
            if (current_index > 0) {
                current_song = playlist[current_index - 1];
                return true;
            }
            return false;
        }
        return false;
    }

    // Returns: monostate (None) on success, false on invalid volume
    std::variant<std::monostate, bool> set_volume(int volume) {
        if (volume >= 0 && volume <= 100) {
            this->volume = volume;
            return std::monostate{};
        }
        return false;
    }

    bool shuffle() {
        if (!playlist.empty()) {
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(playlist.begin(), playlist.end(), g);
            return true;
        }
        return false;
    }
};
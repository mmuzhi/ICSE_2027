#include <vector>
#include <string>
#include <optional>
#include <variant>
#include <algorithm>
#include <stdexcept>
#include <random>

class MusicPlayer {
public:
    using PlayResult = std::variant<std::string, bool, std::monostate>;

    MusicPlayer() : volume(50) {}

    void add_song(const std::string& song) {
        playlist.push_back(song);
    }

    void remove_song(const std::string& song) {
        auto it = std::find(playlist.begin(), playlist.end(), song);
        if (it != playlist.end()) {
            playlist.erase(it);
            if (current_song && *current_song == song) {
                current_song = std::nullopt;
            }
        }
    }

    PlayResult play() {
        if (!playlist.empty() && current_song) {
            return playlist[0];
        } else if (!playlist.empty()) {
            return false;
        } else {
            return std::monostate{};
        }
    }

    bool stop() {
        if (current_song) {
            current_song = std::nullopt;
            return true;
        }
        return false;
    }

    bool switch_song() {
        if (!current_song) {
            return false;
        }
        auto it = std::find(playlist.begin(), playlist.end(), *current_song);
        if (it == playlist.end()) {
            throw std::runtime_error("Current song not found in playlist");
        }
        size_t current_index = std::distance(playlist.begin(), it);
        if (current_index < playlist.size() - 1) {
            current_song = playlist[current_index + 1];
            return true;
        }
        return false;
    }

    bool previous_song() {
        if (!current_song) {
            return false;
        }
        auto it = std::find(playlist.begin(), playlist.end(), *current_song);
        if (it == playlist.end()) {
            throw std::runtime_error("Current song not found in playlist");
        }
        size_t current_index = std::distance(playlist.begin(), it);
        if (current_index > 0) {
            current_song = playlist[current_index - 1];
            return true;
        }
        return false;
    }

    std::optional<bool> set_volume(int volume) {
        if (volume >= 0 && volume <= 100) {
            this->volume = volume;
            return std::nullopt;
        }
        return false;
    }

    bool shuffle() {
        if (playlist.empty()) {
            return false;
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(playlist.begin(), playlist.end(), g);
        return true;
    }

private:
    std::vector<std::string> playlist;
    std::optional<std::string> current_song;
    int volume;
};
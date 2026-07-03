#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <random>
#include <chrono>

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

    std::optional<std::string> play() {
        if (!playlist.empty() && current_song.has_value()) {
            return playlist[0];
        } else if (!playlist.empty()) {
            return std::nullopt;
        }
        return std::nullopt;
    }

    bool stop() {
        if (current_song.has_value()) {
            current_song = std::nullopt;
            return true;
        }
        return false;
    }

    bool switch_song() {
        if (current_song.has_value()) {
            auto it = std::find(playlist.begin(), playlist.end(), current_song.value());
            if (it != playlist.end()) {
                size_t idx = std::distance(playlist.begin(), it);
                if (idx < playlist.size() - 1) {
                    current_song = playlist[idx + 1];
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    bool previous_song() {
        if (current_song.has_value()) {
            auto it = std::find(playlist.begin(), playlist.end(), current_song.value());
            if (it != playlist.end()) {
                size_t idx = std::distance(playlist.begin(), it);
                if (idx > 0) {
                    current_song = playlist[idx - 1];
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    bool set_volume(int vol) {
        if (vol >= 0 && vol <= 100) {
            volume = vol;
            return true;
        }
        return false;
    }

    bool shuffle() {
        if (!playlist.empty()) {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(playlist.begin(), playlist.end(), std::default_random_engine(seed));
            return true;
        }
        return false;
    }
};
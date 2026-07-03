#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <algorithm>
#include <random>

class MusicPlayer {
private:
    std::vector<std::string> playlist;
    std::optional<std::string> current_song; // None if not set
    int volume;

public:
    MusicPlayer() : volume(50) {}

    void add_song(const std::string& song) {
        playlist.push_back(song);
    }

    void remove_song(const std::string& song) {
        auto it = std::find(playlist.begin(), playlist.end(), song);
        if (it != playlist.end()) {
            playlist.erase(it);
            if (current_song.has_value() && current_song.value() == song) {
                stop(); // stop() will reset current_song and return true, but we ignore return
            }
        }
    }

    // Returns song (string) if playing, false if playlist non-empty but no current song,
    // and an empty state (represented by std::monostate) if playlist is empty.
    std::variant<std::string, bool, std::monostate> play() {
        if (!playlist.empty() && current_song.has_value()) {
            return playlist[0];
        } else if (!playlist.empty()) {
            return false;
        }
        // playlist empty -> return monostate (simulates None)
        return std::monostate{};
    }

    bool stop() {
        if (current_song.has_value()) {
            current_song.reset();
            return true;
        }
        return false;
    }

    bool switch_song() {
        if (!current_song.has_value()) {
            return false;
        }
        auto it = std::find(playlist.begin(), playlist.end(), current_song.value());
        if (it == playlist.end()) {
            return false; // should not happen, but be safe
        }
        std::size_t idx = std::distance(playlist.begin(), it);
        if (idx + 1 < playlist.size()) {
            current_song = playlist[idx + 1];
            return true;
        }
        return false;
    }

    bool previous_song() {
        if (!current_song.has_value()) {
            return false;
        }
        auto it = std::find(playlist.begin(), playlist.end(), current_song.value());
        if (it == playlist.end()) {
            return false;
        }
        std::size_t idx = std::distance(playlist.begin(), it);
        if (idx > 0) {
            current_song = playlist[idx - 1];
            return true;
        }
        return false;
    }

    // Returns true on success, false if volume is out of range.
    bool set_volume(int vol) {
        if (vol >= 0 && vol <= 100) {
            volume = vol;
            return true;   // follows docstring (implementation bug returns None, but we correct)
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
};
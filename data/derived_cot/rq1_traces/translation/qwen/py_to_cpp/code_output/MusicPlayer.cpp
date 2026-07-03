#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

class MusicPlayer {
private:
    std::vector<std::string> playlist;
    std::string current_song;
    int volume;

public:
    MusicPlayer() : playlist(), current_song(), volume(50) {}

    void add_song(const std::string& song) {
        playlist.push_back(song);
    }

    void remove_song(const std::string& song) {
        auto it = std::find(playlist.begin(), playlist.end(), song);
        if (it != playlist.end()) {
            playlist.erase(it);
            if (!current_song.empty() && current_song == song) {
                current_song.clear();
            }
        }
    }

    std::variant<std::string, bool> play() {
        if (!playlist.empty() && !current_song.empty()) {
            return playlist[0];
        } else if (!playlist.empty()) {
            return false;
        } else {
            return false;
        }
    }

    bool stop() {
        if (!current_song.empty()) {
            current_song.clear();
            return true;
        }
        return false;
    }

    bool switch_song() {
        if (!current_song.empty()) {
            auto it = std::find(playlist.begin(), playlist.end(), current_song);
            if (it != playlist.end()) {
                int current_index = std::distance(playlist.begin(), it);
                if (current_index < static_cast<int>(playlist.size()) - 1) {
                    current_song = playlist[current_index + 1];
                    return true;
                }
            }
        }
        return false;
    }

    bool previous_song() {
        if (!current_song.empty()) {
            auto it = std::find(playlist.begin(), playlist.end(), current_song);
            if (it != playlist.end()) {
                int current_index = std::distance(playlist.begin(), it);
                if (current_index > 0) {
                    current_song = playlist[current_index - 1];
                    return true;
                }
            }
        }
        return false;
    }

    bool set_volume(int volume) {
        if (volume >= 0 && volume <= 100) {
            this->volume = volume;
            return true;
        }
        return false;
    }

    bool shuffle() {
        if (playlist.empty()) {
            return false;
        }
        std::random_shuffle(playlist.begin(), playlist.end());
        return true;
    }
};
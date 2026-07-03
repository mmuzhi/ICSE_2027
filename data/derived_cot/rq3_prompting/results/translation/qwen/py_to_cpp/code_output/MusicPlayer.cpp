#include <vector>
#include <string>
#include <algorithm>
#include <random>

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

    bool remove_song(const std::string& song) {
        auto it = std::find(playlist.begin(), playlist.end(), song);
        if (it != playlist.end()) {
            playlist.erase(it);
            if (current_song == song) {
                current_song.clear();
            }
            return true;
        }
        return false;
    }

    std::string play() {
        if (!playlist.empty() && !current_song.empty()) {
            return playlist[0];
        }
        return "";
    }

    bool stop() {
        if (!current_song.empty()) {
            current_song.clear();
            return true;
        }
        return false;
    }

    bool switch_song() {
        if (!playlist.empty() && !current_song.empty()) {
            auto it = std::find(playlist.begin(), playlist.end(), current_song);
            if (it != playlist.end() && std::next(it) != playlist.end()) {
                current_song = *(std::next(it));
                return true;
            }
        }
        return false;
    }

    bool previous_song() {
        if (!playlist.empty() && !current_song.empty()) {
            auto it = std::find(playlist.begin(), playlist.end(), current_song);
            if (it != playlist.begin()) {
                std::prev(it);
                current_song = *it;
                return true;
            }
        }
        return false;
    }

    bool set_volume(int new_volume) {
        if (new_volume >= 0 && new_volume <= 100) {
            volume = new_volume;
            return true;
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
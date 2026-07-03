#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <optional>

class MusicPlayer {
private:
    std::vector<std::string> playlist;
    std::optional<std::string> currentSong;
    int volume;

public:
    MusicPlayer()
        : playlist(), currentSong(std::nullopt), volume(50) {}

    void addSong(const std::string& song) {
        playlist.push_back(song);
    }

    void removeSong(const std::string& song) {
        auto it = std::find(playlist.begin(), playlist.end(), song);
        if (it != playlist.end()) {
            playlist.erase(it);
            if (currentSong.has_value() && currentSong.value() == song) {
                stop();
            }
        }
    }

    std::optional<std::string> play() {
        if (playlist.empty()) {
            return std::nullopt;
        }
        if (currentSong.has_value()) {
            if (std::find(playlist.begin(), playlist.end(), currentSong.value()) != playlist.end()) {
                return currentSong;
            }
        }
        return playlist[0];
    }

    bool stop() {
        if (currentSong.has_value()) {
            currentSong = std::nullopt;
            return true;
        } else {
            return false;
        }
    }

    bool switchSong() {
        if (!currentSong.has_value()) {
            return false;
        }
        auto it = std::find(playlist.begin(), playlist.end(), currentSong.value());
        if (it == playlist.end()) {
            return false; // should not happen normally
        }
        size_t index = std::distance(playlist.begin(), it);
        if (index < playlist.size() - 1) {
            currentSong = playlist[index + 1];
            return true;
        } else {
            return false;
        }
    }

    bool previousSong() {
        if (!currentSong.has_value()) {
            return false;
        }
        auto it = std::find(playlist.begin(), playlist.end(), currentSong.value());
        if (it == playlist.end()) {
            return false;
        }
        size_t index = std::distance(playlist.begin(), it);
        if (index > 0) {
            currentSong = playlist[index - 1];
            return true;
        } else {
            return false;
        }
    }

    bool setVolume(int vol) {
        if (vol >= 0 && vol <= 100) {
            volume = vol;
            return true;
        } else {
            return false;
        }
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

    std::vector<std::string>& getPlaylist() {
        return playlist;
    }

    void setPlaylist(const std::vector<std::string>& newPlaylist) {
        playlist = newPlaylist;
    }

    std::optional<std::string> getCurrentSong() const {
        return currentSong;
    }

    void setCurrentSong(const std::optional<std::string>& song) {
        currentSong = song;
    }

    int getVolume() const {
        return volume;
    }
};
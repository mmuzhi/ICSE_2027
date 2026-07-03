#include <vector>
#include <algorithm>
#include <string>
#include <random>

class MusicPlayer {
private:
    std::vector<std::string> playlist;
    std::string currentSong;
    int volume;

public:
    MusicPlayer() : playlist(), currentSong(), volume(50) {}

    void addSong(const std::string& song) {
        playlist.push_back(song);
    }

    void removeSong(const std::string& song) {
        auto it = std::find(playlist.begin(), playlist.end(), song);
        if (it != playlist.end()) {
            playlist.erase(it);
            if (currentSong == song) {
                currentSong = "";
            }
        }
    }

    std::string play() {
        if (playlist.empty()) {
            return "";
        }
        if (!currentSong.empty()) {
            for (const auto& s : playlist) {
                if (s == currentSong) {
                    return currentSong;
                }
            }
        }
        return playlist[0];
    }

    bool stop() {
        if (!currentSong.empty()) {
            currentSong = "";
            return true;
        }
        return false;
    }

    bool switchSong() {
        if (currentSong.empty()) {
            return false;
        }
        auto it = std::find(playlist.begin(), playlist.end(), currentSong);
        if (it != playlist.end()) {
            int index = std::distance(playlist.begin(), it);
            if (index < playlist.size() - 1) {
                currentSong = playlist[index + 1];
                return true;
            }
        }
        return false;
    }

    bool previousSong() {
        if (currentSong.empty()) {
            return false;
        }
        auto it = std::find(playlist.begin(), playlist.end(), currentSong);
        if (it != playlist.end()) {
            int index = std::distance(playlist.begin(), it);
            if (index > 0) {
                currentSong = playlist[index - 1];
                return true;
            }
        }
        return false;
    }

    bool setVolume(int volume) {
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
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(playlist.begin(), playlist.end(), gen);
        return true;
    }

    const std::vector<std::string>& getPlaylist() const {
        return playlist;
    }

    void setPlaylist(const std::vector<std::string>& playlist) {
        this->playlist = playlist;
    }

    std::string getCurrentSong() const {
        return currentSong;
    }

    void setCurrentSong(const std::string& currentSong) {
        this->currentSong = currentSong;
    }

    int getVolume() const {
        return volume;
    }
};
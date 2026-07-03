#include <vector>
#include <string>
#include <algorithm>
#include <random>

class MusicPlayer {
private:
    std::vector<std::string> playlist;
    std::string currentSong;
    int volume;

public:
    MusicPlayer() : currentSong(""), volume(50) {}

    void addSong(const std::string& song) {
        playlist.push_back(song);
    }

    void removeSong(const std::string& song) {
        auto it = std::find(playlist.begin(), playlist.end(), song);
        if (it != playlist.end()) {
            playlist.erase(it);
            if (currentSong == song) {
                stop();
            }
        }
    }

    std::string play() {
        if (playlist.empty()) {
            return "";
        }
        if (!currentSong.empty()) {
            for (const std::string& s : playlist) {
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
        } else {
            return false;
        }
    }

    bool switchSong() {
        if (currentSong.empty()) {
            return false;
        }
        auto it = std::find(playlist.begin(), playlist.end(), currentSong);
        if (it == playlist.end()) {
            return false;
        }
        int currentIndex = it - playlist.begin();
        if (currentIndex < static_cast<int>(playlist.size()) - 1) {
            currentSong = playlist[currentIndex + 1];
            return true;
        } else {
            return false;
        }
    }

    bool previousSong() {
        if (currentSong.empty()) {
            return false;
        }
        auto it = std::find(playlist.begin(), playlist.end(), currentSong);
        if (it == playlist.end()) {
            return false;
        }
        int currentIndex = it - playlist.begin();
        if (currentIndex > 0) {
            currentSong = playlist[currentIndex - 1];
            return true;
        } else {
            return false;
        }
    }

    bool setVolume(int volume) {
        if (volume >= 0 && volume <= 100) {
            this->volume = volume;
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
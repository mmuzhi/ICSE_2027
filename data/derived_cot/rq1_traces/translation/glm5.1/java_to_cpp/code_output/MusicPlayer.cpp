#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <algorithm>
#include <optional>
#include <random>
#include <string>
#include <vector>

class MusicPlayer {
private:
    std::vector<std::string> playlist;
    std::optional<std::string> currentSong;
    int volume;

public:
    MusicPlayer() : playlist(), currentSong(std::nullopt), volume(50) {}

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
            for (const auto& song : playlist) {
                if (song == currentSong.value()) {
                    return currentSong;
                }
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
        int currentIndex = (it == playlist.end())
            ? -1
            : static_cast<int>(std::distance(playlist.begin(), it));
        if (currentIndex < static_cast<int>(playlist.size()) - 1) {
            currentSong = playlist[currentIndex + 1];
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
        int currentIndex = (it == playlist.end())
            ? -1
            : static_cast<int>(std::distance(playlist.begin(), it));
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

    std::optional<std::string> getCurrentSong() const {
        return currentSong;
    }

    void setCurrentSong(const std::optional<std::string>& currentSong) {
        this->currentSong = currentSong;
    }

    int getVolume() const {
        return volume;
    }
};

#endif // MUSIC_PLAYER_H
import random
import time


class MusicPlayer:
    def __init__(self):
        self.playlist = []
        self.current_song = ""
        self.volume = 50
        random.seed(int(time.time()))

    def add_song(self, song):
        self.playlist.append(song)

    def remove_song(self, song):
        try:
            idx = self.playlist.index(song)
            self.playlist.pop(idx)
            if self.current_song == song:
                self.stop()
        except ValueError:
            pass

    def play(self):
        if self.playlist:
            if self.current_song:
                if self.current_song in self.playlist:
                    return self.current_song
                return self.playlist[0]
            else:
                return self.playlist[0]
        return ""

    def stop(self):
        if self.current_song:
            self.current_song = ""
            return True
        return False

    def switch_song(self):
        if self.current_song:
            try:
                idx = self.playlist.index(self.current_song)
                if idx + 1 < len(self.playlist):
                    self.current_song = self.playlist[idx + 1]
                    return True
                return False
            except ValueError:
                return False
        return False

    def previous_song(self):
        if self.current_song:
            try:
                idx = self.playlist.index(self.current_song)
                if idx > 0:
                    self.current_song = self.playlist[idx - 1]
                    return True
                return False
            except ValueError:
                # C++: find returns end(); if end()!=begin(), *(it-1) is last element
                if self.playlist:
                    self.current_song = self.playlist[-1]
                    return True
                return False
        return False

    def set_volume(self, volume):
        if self._is_valid_volume(volume):
            self.volume = volume
            return True
        return False

    def shuffle(self):
        if self.playlist:
            random.shuffle(self.playlist)
            return True
        return False

    def _is_valid_volume(self, volume):
        return 0 <= volume <= 100
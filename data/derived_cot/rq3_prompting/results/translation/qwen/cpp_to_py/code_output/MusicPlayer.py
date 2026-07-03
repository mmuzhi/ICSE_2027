import random
import time

class MusicPlayer:
    def __init__(self):
        self.playlist = []
        self.current_song = ""
        self.volume = 50
        random.seed(int(time.time()))  # Seed the random number generator

    def add_song(self, song):
        self.playlist.append(song)

    def remove_song(self, song):
        if song in self.playlist:
            self.playlist.remove(song)
            if self.current_song == song:
                self.stop()

    def play(self):
        if not self.playlist:
            return ""
        if self.current_song:
            if self.current_song in self.playlist:
                return self.current_song
            else:
                return self.playlist[0]
        else:
            return self.playlist[0]

    def stop(self):
        if self.current_song:
            self.current_song = ""
            return True
        return False

    def switch_song(self):
        if not self.current_song:
            return False
        if self.current_song in self.playlist:
            index = self.playlist.index(self.current_song)
            if index + 1 < len(self.playlist):
                self.current_song = self.playlist[index + 1]
                return True
        return False

    def previous_song(self):
        if not self.current_song:
            return False
        if self.current_song in self.playlist:
            index = self.playlist.index(self.current_song)
            if index - 1 >= 0:
                self.current_song = self.playlist[index - 1]
                return True
        return False

    def set_volume(self, volume):
        if 0 <= volume <= 100:
            self.volume = volume
            return True
        return False

    def shuffle(self):
        if not self.playlist:
            return False
        random.shuffle(self.playlist)
        return True
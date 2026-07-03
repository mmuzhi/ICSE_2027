import random
import os
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
        if not self.playlist or not self.current_song:
            return False
        try:
            index = self.playlist.index(self.current_song)
            if index < len(self.playlist) - 1:
                self.current_song = self.playlist[index + 1]
                return True
            return False
        except ValueError:
            return False

    def previous_song(self):
        if not self.playlist or not self.current_song:
            return False
        try:
            index = self.playlist.index(self.current_song)
            if index > 0:
                self.current_song = self.playlist[index - 1]
                return True
            return False
        except ValueError:
            return False

    def set_volume(self, volume):
        if 0 <= volume <= 100:
            self.volume = volume
            return True
        return False

    def shuffle(self):
        if not self.playlist:
            return False
        random_device = random.SystemRandom()
        random_device.shuffle(self.playlist)
        return True

    def is_valid_volume(self, volume):
        return 0 <= volume <= 100
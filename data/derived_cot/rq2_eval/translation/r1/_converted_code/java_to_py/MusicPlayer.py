import random

class MusicPlayer:
    def __init__(self):
        self.playlist = []
        self.current_song = None
        self.volume = 50

    def add_song(self, song):
        self.playlist.append(song)

    def remove_song(self, song):
        if song in self.playlist:
            self.playlist.remove(song)
            if self.current_song == song:
                self.stop()

    def play(self):
        if not self.playlist:
            return None
        if self.current_song is not None:
            if self.current_song in self.playlist:
                return self.current_song
        return self.playlist[0]

    def stop(self):
        if self.current_song is not None:
            self.current_song = None
            return True
        return False

    def switch_song(self):
        if self.current_song is None:
            return False
        if self.current_song not in self.playlist:
            return False
        current_index = self.playlist.index(self.current_song)
        if current_index < len(self.playlist) - 1:
            self.current_song = self.playlist[current_index + 1]
            return True
        return False

    def previous_song(self):
        if self.current_song is None:
            return False
        if self.current_song not in self.playlist:
            return False
        current_index = self.playlist.index(self.current_song)
        if current_index > 0:
            self.current_song = self.playlist[current_index - 1]
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

    def get_playlist(self):
        return self.playlist

    def set_playlist(self, playlist):
        self.playlist = playlist

    def get_current_song(self):
        return self.current_song

    def set_current_song(self, current_song):
        self.current_song = current_song

    def get_volume(self):
        return self.volume
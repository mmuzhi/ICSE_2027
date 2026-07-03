import random

class MusicPlayer:
    def __init__(self):
        self.playlist = []
        self.currentSong = None
        self.volume = 50

    def add_song(self, song):
        self.playlist.append(song)

    def remove_song(self, song):
        if song in self.playlist:
            self.playlist.remove(song)
            if self.currentSong == song:
                self.stop()

    def play(self):
        if not self.playlist:
            return None
        if self.currentSong is not None:
            for song in self.playlist:
                if song == self.currentSong:
                    return self.currentSong
        return self.playlist[0] if self.playlist else None

    def stop(self):
        if self.currentSong is not None:
            self.currentSong = None
            return True
        return False

    def switch_song(self):
        if self.currentSong is None:
            return False
        try:
            index = self.playlist.index(self.currentSong)
        except ValueError:
            return False
        if index < len(self.playlist) - 1:
            self.currentSong = self.playlist[index + 1]
            return True
        return False

    def previous_song(self):
        if self.currentSong is None:
            return False
        try:
            index = self.playlist.index(self.currentSong)
        except ValueError:
            return False
        if index > 0:
            self.currentSong = self.playlist[index - 1]
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
        return self.currentSong

    def set_current_song(self, currentSong):
        self.currentSong = currentSong

    def get_volume(self):
        return self.volume
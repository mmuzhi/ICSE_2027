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
            return True
        return False

    def play(self):
        if not self.playlist:
            return None
        if self.current_song is not None:
            try:
                index = self.playlist.index(self.current_song)
                return self.playlist[index]
            except ValueError:
                pass
        return self.playlist[0] if self.playlist else None

    def stop(self):
        if self.current_song is not None:
            self.current_song = None
            return True
        return False

    def switch_song(self):
        if self.current_song is None:
            return False
        try:
            index = self.playlist.index(self.current_song)
            if index < len(self.playlist) - 1:
                self.current_song = self.playlist[index + 1]
                return True
        except ValueError:
            pass
        return False

    def previous_song(self):
        if self.current_song is None:
            return False
        try:
            index = self.playlist.index(self.current_song)
            if index > 0:
                self.current_song = self.playlist[index - 1]
                return True
        except ValueError:
            pass
        return False

    def set_volume(self, volume):
        if 0 <= volume <= 100:
            self.volume = volume
            return True
        return False

    def shuffle(self):
        import random
        if not self.playlist:
            return False
        random.shuffle(self.playlist)
        return True

    def get_playlist(self):
        return self.playlist.copy()

    def set_playlist(self, playlist):
        self.playlist = playlist
        self.current_song = None

    def get_current_song(self):
        return self.current_song

    def set_current_song(self, song):
        self.current_song = song
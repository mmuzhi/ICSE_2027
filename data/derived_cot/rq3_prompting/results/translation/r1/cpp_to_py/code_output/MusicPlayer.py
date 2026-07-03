import random

class MusicPlayer:
    def __init__(self):
        self.volume = 50
        self.playlist = []
        self.current_song = ""

    def add_song(self, song: str) -> None:
        self.playlist.append(song)

    def remove_song(self, song: str) -> None:
        try:
            self.playlist.remove(song)    # will raise ValueError if not found
            if self.current_song == song:
                self.stop()
        except ValueError:
            pass

    def play(self) -> str:
        if not self.playlist:
            return ""
        if self.current_song:
            # If current_song is still in the playlist, return it; else first
            if self.current_song in self.playlist:
                return self.current_song
            else:
                return self.playlist[0]
        else:
            return self.playlist[0]

    def stop(self) -> bool:
        if self.current_song:
            self.current_song = ""
            return True
        return False

    def switch_song(self) -> bool:
        if not self.current_song:
            return False
        try:
            idx = self.playlist.index(self.current_song)
        except ValueError:
            return False
        if idx + 1 < len(self.playlist):
            self.current_song = self.playlist[idx + 1]
            return True
        return False

    def previous_song(self) -> bool:
        if not self.current_song:
            return False
        try:
            idx = self.playlist.index(self.current_song)
        except ValueError:
            return False
        if idx > 0:
            self.current_song = self.playlist[idx - 1]
            return True
        return False

    def set_volume(self, volume: int) -> bool:
        if self._is_valid_volume(volume):
            self.volume = volume
            return True
        return False

    def shuffle(self) -> bool:
        if not self.playlist:
            return False
        random.shuffle(self.playlist)
        return True

    def _is_valid_volume(self, volume: int) -> bool:
        return 0 <= volume <= 100
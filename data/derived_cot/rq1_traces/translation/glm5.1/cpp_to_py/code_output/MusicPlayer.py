import random
import time

class MusicPlayer:
    def __init__(self):
        self.playlist: list[str] = []
        self.current_song: str = ""
        self.volume: int = 50
        # Replicating the global srand side effect from the C++ constructor
        random.seed(int(time.time()))

    def add_song(self, song: str) -> None:
        self.playlist.append(song)

    def remove_song(self, song: str) -> None:
        if song in self.playlist:
            self.playlist.remove(song) # Removes the first occurrence, matching std::find + erase
            if self.current_song == song:
                self.stop()

    def play(self) -> str:
        if self.playlist:
            if self.current_song:
                if self.current_song in self.playlist:
                    return self.current_song
                return self.playlist[0]
            else:
                return self.playlist[0]
        return ""

    def stop(self) -> bool:
        if self.current_song:
            self.current_song = ""
            return True
        return False

    def switch_song(self) -> bool:
        if self.current_song:
            try:
                idx = self.playlist.index(self.current_song)
                if idx < len(self.playlist) - 1:
                    self.current_song = self.playlist[idx + 1]
                    return True
            except ValueError:
                # current_song is not in the playlist
                pass
        return False

    def previous_song(self) -> bool:
        if self.current_song:
            try:
                idx = self.playlist.index(self.current_song)
                if idx > 0:
                    self.current_song = self.playlist[idx - 1]
                    return True
            except ValueError:
                # C++ behavior edge case: if current_song is not in the playlist, 
                # std::find returns end(). end() != begin() is true, and *(end() - 1) 
                # points to the last element of the playlist.
                if self.playlist:
                    self.current_song = self.playlist[-1]
                    return True
        return False

    def set_volume(self, volume: int) -> bool:
        if self.is_valid_volume(volume):
            self.volume = volume
            return True
        return False

    def shuffle(self) -> bool:
        if self.playlist:
            random.shuffle(self.playlist)
            return True
        return False

    def is_valid_volume(self, volume: int) -> bool:
        return 0 <= volume <= 100
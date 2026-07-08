import random
from typing import List, Optional

class MusicPlayer:
    def __init__(self) -> None:
        self.playlist: List[str] = []
        self.current_song: Optional[str] = None
        self.volume: int = 50

    def add_song(self, song: str) -> None:
        self.playlist.append(song)

    def remove_song(self, song: str) -> None:
        if song in self.playlist:
            self.playlist.remove(song)
            if self.current_song is not None and self.current_song == song:
                self.stop()

    def play(self) -> Optional[str]:
        if not self.playlist:
            return None
        if self.current_song is not None:
            if self.current_song in self.playlist:
                return self.current_song
        return self.playlist[0]

    def stop(self) -> bool:
        if self.current_song is not None:
            self.current_song = None
            return True
        else:
            return False

    def switch_song(self) -> bool:
        if self.current_song is None:
            return False
        
        try:
            current_index = self.playlist.index(self.current_song)
        except ValueError:
            current_index = -1
            
        if current_index < len(self.playlist) - 1:
            self.current_song = self.playlist[current_index + 1]
            return True
        else:
            return False

    def previous_song(self) -> bool:
        if self.current_song is None:
            return False
            
        try:
            current_index = self.playlist.index(self.current_song)
        except ValueError:
            current_index = -1
            
        if current_index > 0:
            self.current_song = self.playlist[current_index - 1]
            return True
        else:
            return False

    def set_volume(self, volume: int) -> bool:
        if 0 <= volume <= 100:
            self.volume = volume
            return True
        else:
            return False

    def shuffle(self) -> bool:
        if not self.playlist:
            return False
        random.shuffle(self.playlist)
        return True

    def get_playlist(self) -> List[str]:
        return self.playlist

    def set_playlist(self, playlist: List[str]) -> None:
        self.playlist = playlist

    def get_current_song(self) -> Optional[str]:
        return self.current_song

    def set_current_song(self, current_song: Optional[str]) -> None:
        self.current_song = current_song

    def get_volume(self) -> int:
        return self.volume
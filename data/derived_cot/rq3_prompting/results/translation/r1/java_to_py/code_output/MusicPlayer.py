import random
from typing import List, Optional

class MusicPlayer:
    def __init__(self):
        self.playlist: List[str] = []
        self.currentSong: Optional[str] = None
        self.volume: int = 50

    def addSong(self, song: str) -> None:
        self.playlist.append(song)

    def removeSong(self, song: str) -> None:
        if song in self.playlist:
            self.playlist.remove(song)
            if self.currentSong is not None and self.currentSong == song:
                self.stop()

    def play(self) -> Optional[str]:
        if not self.playlist:
            return None
        if self.currentSong is not None:
            for s in self.playlist:
                if s == self.currentSong:
                    return self.currentSong
        return self.playlist[0]

    def stop(self) -> bool:
        if self.currentSong is not None:
            self.currentSong = None
            return True
        return False

    def switchSong(self) -> bool:
        if self.currentSong is None:
            return False
        # Java's indexOf returns -1 if not found; replicate that behavior
        try:
            currentIndex = self.playlist.index(self.currentSong)
        except ValueError:
            currentIndex = -1
        if currentIndex < len(self.playlist) - 1:
            self.currentSong = self.playlist[currentIndex + 1]
            return True
        return False

    def previousSong(self) -> bool:
        if self.currentSong is None:
            return False
        try:
            currentIndex = self.playlist.index(self.currentSong)
        except ValueError:
            currentIndex = -1
        if currentIndex > 0:
            self.currentSong = self.playlist[currentIndex - 1]
            return True
        return False

    def setVolume(self, volume: int) -> bool:
        if 0 <= volume <= 100:
            self.volume = volume
            return True
        return False

    def shuffle(self) -> bool:
        if not self.playlist:
            return False
        random.shuffle(self.playlist)
        return True

    def getPlaylist(self) -> List[str]:
        return self.playlist

    def setPlaylist(self, playlist: List[str]) -> None:
        self.playlist = playlist

    def getCurrentSong(self) -> Optional[str]:
        return self.currentSong

    def setCurrentSong(self, currentSong: Optional[str]) -> None:
        self.currentSong = currentSong

    def getVolume(self) -> int:
        return self.volume
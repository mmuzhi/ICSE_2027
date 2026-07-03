from typing import List

class PlayItem:
    def __init__(self, chord: str, tune: str):
        self.chord = chord
        self.tune = tune

class AutomaticGuitarSimulator:
    def __init__(self, text: str):
        self.play_text = text

    def interpret(self, display: bool = False) -> List[PlayItem]:
        if not self.play_text.strip():
            return []
        segments = self.play_text.split()
        play_list = []
        for seg in segments:
            i = 0
            while i < len(seg) and seg[i].isalpha():
                i += 1
            chord = seg[:i]
            tune = seg[i:]
            item = PlayItem(chord, tune)
            play_list.append(item)
            if display:
                print(self.format_display(chord, tune), flush=True)
        return play_list

    def format_display(self, key: str, value: str) -> str:
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value
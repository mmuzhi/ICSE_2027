class PlayItem:
    def __init__(self, chord: str, tune: str):
        self.Chord = chord
        self.Tune = tune


class AutomaticGuitarSimulator:
    def __init__(self, text: str):
        self.play_text = text

    def interpret(self, display: bool = False):
        play_list = []
        if not self.play_text:
            return play_list

        for seg in self.play_text.split():
            # find position where alphabetic characters end
            pos = 0
            while pos < len(seg) and seg[pos].isalpha():
                pos += 1
            chord = seg[:pos]
            value = seg[pos:]
            item = PlayItem(chord, value)
            play_list.append(item)
            if display:
                print(self.format_display(chord, value))

        return play_list

    def format_display(self, key: str, value: str) -> str:
        return f"Normal Guitar Playing -- Chord: {key}, Play Tune: {value}"
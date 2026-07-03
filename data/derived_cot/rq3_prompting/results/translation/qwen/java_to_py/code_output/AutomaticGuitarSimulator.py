class AutomaticGuitarSimulator:
    def __init__(self, text):
        self.playText = text

    def interpret(self, display):
        if self.playText is None or (self.playText and self.playText.strip() == ""):
            return None

        play_list = []
        play_segs = self.playText.split(" ")
        for play_seg in play_segs:
            if play_seg.strip() == "":
                continue
            pos = 0
            for char in play_seg:
                if char.isalpha():
                    pos += 1
                else:
                    break
            play_chord = play_seg[:pos]
            play_value = play_seg[pos:]
            play_list.append(self.ChordTune(play_chord, play_value))
            if display:
                self.display(play_chord, play_value)
        return play_list

    def display(self, key, value):
        return f"Normal Guitar Playing -- Chord: {key}, Play Tune: {value}"

    class ChordTune:
        def __init__(self, chord, tune):
            self.chord = chord
            self.tune = tune

        def getChord(self):
            return self.chord

        def getTune(self):
            return self.tune

        def __eq__(self, other):
            if isinstance(other, AutomaticGuitarSimulator.ChordTune):
                return self.chord == other.chord and self.tune == other.tune
            return False

        def __hash__(self):
            return hash((self.chord, self.tune))
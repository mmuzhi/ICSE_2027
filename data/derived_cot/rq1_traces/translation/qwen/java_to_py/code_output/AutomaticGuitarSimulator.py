class AutomaticGuitarSimulator:
    def __init__(self, text):
        self.play_text = text

    def interpret(self, display):
        if self.play_text is None or self.play_text.strip() == "":
            return None

        play_list = []
        play_segs = self.play_text.split(" ")
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
            play_list.append(ChordTune(play_chord, play_value))
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
            if not isinstance(other, AutomaticGuitarSimulator.ChordTune):
                return False
            return self.chord == other.chord and self.tune == other.tune

        def __hash__(self):
            h1 = hash(self.chord) if self.chord else 0
            h2 = hash(self.tune) if self.tune else 0
            return 31 * h1 + h2


# Example usage:
# simulator = AutomaticGuitarSimulator("C G D E")
# result = simulator.interpret(True)
# print(result)
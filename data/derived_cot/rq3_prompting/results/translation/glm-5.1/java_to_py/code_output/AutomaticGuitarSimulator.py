class AutomaticGuitarSimulator:
    class ChordTune:
        def __init__(self, chord, tune):
            self.chord = chord
            self.tune = tune

        def get_chord(self):
            return self.chord

        def get_tune(self):
            return self.tune

        def __eq__(self, obj):
            if self is obj:
                return True
            if obj is None or type(self) != type(obj):
                return False
            return self.chord == obj.chord and self.tune == obj.tune

        def __hash__(self):
            return hash((self.chord, self.tune))

    def __init__(self, text):
        self.playText = text

    def interpret(self, display):
        if self.playText is None or self.playText.strip() == "":
            return None

        play_list = []
        play_segs = self.playText.split(" ")
        for play_seg in play_segs:
            if play_seg.strip() == "":
                continue
            pos = 0
            for ele in play_seg:
                if ele.isalpha():
                    pos += 1
                    continue
                break
            play_chord = play_seg[:pos]
            play_value = play_seg[pos:]
            play_list.append(self.ChordTune(play_chord, play_value))
            if display:
                self.display(play_chord, play_value)
        return play_list

    def display(self, key, value):
        return f"Normal Guitar Playing -- Chord: {key}, Play Tune: {value}"
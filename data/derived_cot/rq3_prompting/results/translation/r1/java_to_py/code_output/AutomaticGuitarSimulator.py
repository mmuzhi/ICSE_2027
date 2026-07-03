class AutomaticGuitarSimulator:
    def __init__(self, text: str):
        self.playText = text

    def interpret(self, display_flag: bool):
        # Return None for null/empty/whitespace-only input
        if self.playText is None or self.playText.strip() == "":
            return None

        play_list = []
        # Split on single space (Java's String.split(" "))
        for seg in self.playText.split(' '):
            if seg.strip() == "":
                continue

            pos = 0
            for ch in seg:
                if ch.isalpha():
                    pos += 1
                else:
                    break

            play_chord = seg[:pos]
            play_value = seg[pos:]
            tune = self.ChordTune(play_chord, play_value)
            play_list.append(tune)

            if display_flag:
                # Call display and discard return (same as Java)
                self.display(play_chord, play_value)

        return play_list

    def display(self, key: str, value: str) -> str:
        return f"Normal Guitar Playing -- Chord: {key}, Play Tune: {value}"

    class ChordTune:
        def __init__(self, chord: str, tune: str):
            self.chord = chord
            self.tune = tune

        # Getter methods to mirror Java API
        def getChord(self) -> str:
            return self.chord

        def getTune(self) -> str:
            return self.tune

        def __eq__(self, other):
            if self is other:
                return True
            if other is None or type(self) != type(other):
                return False
            return self.chord == other.chord and self.tune == other.tune

        def __hash__(self):
            # Equivalent to Java's 31 * chord.hashCode() + tune.hashCode()
            return hash((self.chord, self.tune))
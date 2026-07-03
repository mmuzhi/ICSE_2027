class ChordTune:
    def __init__(self, chord, tune):
        self.chord = chord
        self.tune = tune
    
    def get_chord(self):
        return self.chord
    
    def get_tune(self):
        return self.tune
    
    def __eq__(self, other):
        if self is other:
            return True
        if not isinstance(other, ChordTune):
            return False
        return self.chord == other.chord and self.tune == other.tune
    
    def __hash__(self):
        result = hash(self.chord)
        result = 31 * result + hash(self.tune)
        return result

class AutomaticGuitarSimulator:
    def __init__(self, text):
        self.play_text = text
    
    def interpret(self, display_flag):
        if self.play_text is None or self.play_text.strip() == "":
            return None
        
        play_list = []
        play_segments = self.play_text.split()
        for seg in play_segments:
            if seg == "":
                continue
            pos = 0
            for char in seg:
                if char.isalpha():
                    pos += 1
                else:
                    break
            play_chord = seg[:pos]
            play_value = seg[pos:]
            chord_tune = ChordTune(play_chord, play_value)
            play_list.append(chord_tune)
            if display_flag:
                self.display(play_chord, play_value)
        return play_list
    
    def display(self, key, value):
        return f"Normal Guitar Playing -- Chord: {key}, Play Tune: {value}"
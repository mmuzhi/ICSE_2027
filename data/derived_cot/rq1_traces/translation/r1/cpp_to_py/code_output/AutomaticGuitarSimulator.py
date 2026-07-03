class PlayItem:
    def __init__(self, Chord, Tune):
        self.Chord = Chord
        self.Tune = Tune

class AutomaticGuitarSimulator:
    def __init__(self, text):
        self.play_text = text
    
    def interpret(self, display=False):
        if self.play_text == "":
            return []
        
        segments = self.play_text.split()
        play_list = []
        ascii_letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        
        for seg in segments:
            pos = 0
            n = len(seg)
            while pos < n and seg[pos] in ascii_letters:
                pos += 1
            chord = seg[:pos]
            tune = seg[pos:]
            item = PlayItem(chord, tune)
            play_list.append(item)
            if display:
                print(self.format_display(chord, tune))
                
        return play_list
    
    def format_display(self, key, value):
        return "Normal Guitar Playing -- Chord: " + key + ", Play Tune: " + value
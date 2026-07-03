from collections import namedtuple

class AutomaticGuitarSimulator:

    def __init__(self, text):
        self.play_text = text

    def interpret(self, display=False):
        if not self.play_text.strip():
            return []
        tokens = self.play_text.split()
        play_list = []
        for token in tokens:
            pos = 0
            while pos < len(token) and token[pos].isalpha():
                pos += 1
            chord = token[:pos]
            tune = token[pos:]
            item = namedtuple('PlayItem', ('Chord', 'Tune'))(Chord=chord, Tune=tune)
            play_list.append(item)
            if display:
                print(self.display(chord, tune))
        return play_list

    def display(self, key, value):
        return 'Normal Guitar Playing -- Chord: ' + key + ', Play Tune: ' + value
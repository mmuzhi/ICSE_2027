class Words2Numbers:

    def __init__(self):
        self.numwords = {}
        units = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine', 'ten', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen']
        tens = ['', '', 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety']
        scales = ['hundred', 'thousand', 'million', 'billion', 'trillion']
        self.numwords['and'] = (1, 0)
        for idx, word in enumerate(units):
            self.numwords[word] = (1, idx)
        for idx, word in enumerate(tens):
            if word:
                self.numwords[word] = (1, idx * 10)
        for idx, word in enumerate(scales):
            scale = 10 ** (idx * 3) if idx != 0 else 100
            self.numwords[word] = (scale, 0)
        self.ordinalWords = {'first': 1, 'second': 2, 'third': 3, 'fifth': 5, 'eighth': 8, 'ninth': 9, 'twelfth': 12}
        self.ordinalEndings = [('ieth', 'y'), ('th', '')]

    def text2int(self, textnum):
        textnum = textnum.replace('-', ' ')
        current = 0
        result = 0
        curstring = []
        onnumber = False
        words = textnum.split()
        for word in words:
            if word in self.ordinalWords:
                increment = self.ordinalWords[word]
                current = current * 1 + increment
                onnumber = True
            else:
                base_word = word
                for ending, replacement in self.ordinalEndings:
                    if word.endswith(ending):
                        base_word = word[:-len(ending)] + replacement
                        break
                if base_word not in self.numwords:
                    if onnumber:
                        curstring.append(str(result + current))
                        result = current = 0
                        onnumber = False
                    curstring.append(word)
                else:
                    scale, increment = self.numwords[base_word]
                    current = current * scale + increment
                    if scale >= 100:
                        result += current
                        current = 0
                    onnumber = True
        if onnumber:
            curstring.append(str(result + current))
        return ' '.join(curstring)

    def is_valid_input(self, textnum):
        textnum = textnum.replace('-', ' ')
        words = textnum.split()
        for word in words:
            if word in self.ordinalWords:
                continue
            base_word = word
            for ending, replacement in self.ordinalEndings:
                if word.endswith(ending):
                    base_word = word[:-len(ending)] + replacement
                    break
            if base_word not in self.numwords:
                return False
        return True
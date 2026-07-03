class Words2Numbers:
    def __init__(self):
        self.numwords = {}
        self.units = [
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight",
            "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
            "sixteen", "seventeen", "eighteen", "nineteen"
        ]
        self.tens = [
            "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
        ]
        self.scales = [
            "hundred", "thousand", "million", "billion", "trillion"
        ]
        self.ordinal_words = {
            "first": 1, "second": 2, "third": 3, "fifth": 5, "eighth": 8,
            "ninth": 9, "twelfth": 12
        }
        self.ordinal_endings = [["ieth", "y"], ["th", ""]]

        self.numwords["and"] = (1, 0)
        for idx, word in enumerate(self.units):
            self.numwords[word] = (1, idx)
        for idx, word in enumerate(self.tens):
            if word:  # Skip empty strings
                self.numwords[word] = (1, idx * 10)
        for idx, word in enumerate(self.scales):
            power = 2 if idx * 3 == 0 else idx * 3
            self.numwords[word] = (10 ** power, 0)

    def text2int(self, textnum):
        textnum = textnum.replace('-', ' ')
        words = textnum.split()

        current = 0
        result = 0
        curstring = []
        onnumber = False

        for word in words:
            if word in self.ordinal_words:
                scale = 1
                increment = self.ordinal_words[word]
                current = current * scale + increment
                onnumber = True
            else:
                for ending, replacement in self.ordinal_endings:
                    if word.endswith(ending):
                        word = word[:-len(ending)] + replacement
                if word not in self.numwords:
                    if onnumber:
                        curstring.append(str(result + current))
                        result = 0
                        current = 0
                        onnumber = False
                    curstring.append(word)
                else:
                    scale, increment = self.numwords[word]
                    current = current * scale + increment
                    if scale > 100:
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
            modified = word
            for ending, replacement in self.ordinal_endings:
                if modified.endswith(ending):
                    modified = modified[:-len(ending)] + replacement
            if modified not in self.numwords:
                return False
        return True
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
        self.scales = ["hundred", "thousand", "million", "billion", "trillion"]
        
        self.ordinalWords = {
            "first": 1,
            "second": 2,
            "third": 3,
            "fifth": 5,
            "eighth": 8,
            "ninth": 9,
            "twelfth": 12
        }
        
        self.ordinalEndings = [
            ("ieth", "y"),
            ("th", "")
        ]
        
        # Build numwords dictionary
        for idx, word in enumerate(self.units):
            self.numwords[word] = (1, idx)
        for idx, word in enumerate(self.tens):
            if idx == 0 or idx == 1:
                continue
            self.numwords[word] = (1, idx * 10)
        for idx, word in enumerate(self.scales):
            exponent = 2 if idx * 3 == 0 else idx * 3
            self.numwords[word] = (10**exponent, 0)

    def text2int(self, textnum):
        textnum = textnum.replace('-', ' ')
        words = textnum.split()
        tokens = []
        current = 0
        result = 0
        onnumber = False
        
        for word in words:
            if word in self.ordinalWords:
                scale = 1
                increment = self.ordinalWords[word]
                current = current * scale + increment
                onnumber = True
            else:
                for pattern, replacement in self.ordinalEndings:
                    if word.endswith(pattern):
                        word = word[:-len(pattern)] + replacement
                if word not in self.numwords:
                    if onnumber:
                        tokens.append(str(result + current))
                    tokens.append(word)
                    result = current = 0
                    onnumber = False
                else:
                    scale, increment = self.numwords[word]
                    current = current * scale + increment
                    if scale > 100:
                        result += current
                        current = 0
                    onnumber = True
        
        if onnumber:
            tokens.append(str(result + current))
        
        return ' '.join(tokens)

    def isValidInput(self, textnum):
        textnum = textnum.replace('-', ' ')
        words = textnum.split()
        for word in words:
            if word in self.ordinalWords:
                continue
            else:
                for pattern, replacement in self.ordinalEndings:
                    if word.endswith(pattern):
                        word = word[:-len(pattern)] + replacement
                if word not in self.numwords:
                    return False
        return True
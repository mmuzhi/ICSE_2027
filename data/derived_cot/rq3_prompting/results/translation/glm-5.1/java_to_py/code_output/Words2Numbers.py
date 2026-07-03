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

        self.numwords["and"] = [1, 0]
        for idx, unit in enumerate(self.units):
            self.numwords[unit] = [1, idx]
        for idx, ten in enumerate(self.tens):
            self.numwords[ten] = [1, idx * 10]
        for idx, scale in enumerate(self.scales):
            exp = 2 if idx * 3 == 0 else idx * 3
            self.numwords[scale] = [10 ** exp, 0]

        self.ordinal_words = {
            "first": 1,
            "second": 2,
            "third": 3,
            "fifth": 5,
            "eighth": 8,
            "ninth": 9,
            "twelfth": 12
        }

        self.ordinal_endings = [
            ["ieth", "y"],
            ["th", ""]
        ]

    def text2int(self, textnum):
        textnum = textnum.replace("-", " ")

        current = 0
        result = 0
        curstring = ""
        onnumber = False

        for word in textnum.split(" "):
            if word in self.ordinal_words:
                scale = 1
                increment = self.ordinal_words[word]
                current = current * scale + increment
                onnumber = True
            else:
                for ending in self.ordinal_endings:
                    if word.endswith(ending[0]):
                        word = word[:len(word) - len(ending[0])] + ending[1]

                if word not in self.numwords:
                    if onnumber:
                        curstring += str(result + current) + " "
                    curstring += word + " "
                    result = current = 0
                    onnumber = False
                else:
                    scale = self.numwords[word][0]
                    increment = self.numwords[word][1]
                    current = current * scale + increment
                    if scale > 100:
                        result += current
                        current = 0
                    onnumber = True

        if onnumber:
            curstring += str(result + current)

        return curstring

    def isValidInput(self, textnum):
        textnum = textnum.replace("-", " ")

        for word in textnum.split(" "):
            if word in self.ordinal_words:
                continue
            else:
                for ending in self.ordinal_endings:
                    if word.endswith(ending[0]):
                        word = word[:len(word) - len(ending[0])] + ending[1]

                if word not in self.numwords:
                    return False

        return True
class Words2Numbers:
    def __init__(self):
        self.units = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
                     "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                     "eighteen", "nineteen"]
        self.tens = ["", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]
        self.scales = ["hundred", "thousand", "million", "billion", "trillion"]
        self.numwords = {}
        self.ordinal_words = {
            "first": 1, "second": 2, "third": 3, "fifth": 5, "eighth": 8,
            "ninth": 9, "twelfth": 12
        }
        self.ordinal_endings = [("ieth", "y"), ("th", "")]

        self.numwords["and"] = (1, 0)
        for idx, word in enumerate(self.units):
            self.numwords[word] = (1, idx)
        for idx, word in enumerate(self.tens):
            self.numwords[word] = (1, idx * 10)
        for idx, word in enumerate(self.scales):
            self.numwords[word] = (10 ** (idx * 3), 0)
        self.numwords["hundred"] = (100, 0)

    def text2int(self, textnum):
        text = textnum.replace('-', ' ')
        words = text.split()
        current = 0
        result = 0
        curstring = ""

        for word in words:
            if word in self.ordinal_words:
                scale = 1
                increment = self.ordinal_words[word]
                current = current * scale + increment
            else:
                new_word = word
                for ending, replacement in self.ordinal_endings:
                    if len(new_word) > len(ending) and new_word.endswith(ending):
                        new_word = new_word[:-len(ending)] + replacement
                if new_word not in self.numwords:
                    if current > 0:
                        result += current
                        current = 0
                    curstring += word + " "
                else:
                    scale, increment = self.numwords[new_word]
                    if scale == 1:
                        current += increment
                    else:
                        current *= scale
                        result += current
                        current = 0

        if current > 0:
            result += current

        curstring += str(result)
        return curstring

    def is_valid_input(self, textnum):
        text = textnum.replace('-', ' ')
        words = text.split()
        for word in words:
            if word in self.ordinal_words:
                continue
            new_word = word
            for ending, replacement in self.ordinal_endings:
                if len(new_word) > len(ending) and new_word.endswith(ending):
                    new_word = new_word[:-len(ending)] + replacement
            if new_word not in self.numwords:
                return False
        return True
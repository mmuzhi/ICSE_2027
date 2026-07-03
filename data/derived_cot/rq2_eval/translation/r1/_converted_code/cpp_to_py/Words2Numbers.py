class Words2Numbers:
    def __init__(self):
        self.units = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
                     "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                     "eighteen", "nineteen"]
        self.tens = ["", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]
        self.scales = ["hundred", "thousand", "million", "billion", "trillion"]
        
        self.numwords = {}
        self.numwords["and"] = (1, 0)
        
        for idx, word in enumerate(self.units):
            self.numwords[word] = (1, idx)
        
        for idx, word in enumerate(self.tens):
            if word:
                self.numwords[word] = (1, idx * 10)
        
        for idx, word in enumerate(self.scales):
            scale_val = 10 ** (idx * 3)
            self.numwords[word] = (scale_val, 0)
        
        self.numwords["hundred"] = (100, 0)
        
        self.ordinal_words = {
            "first": 1,
            "second": 2,
            "third": 3,
            "fifth": 5,
            "eighth": 8,
            "ninth": 9,
            "twelfth": 12
        }
        
        self.ordinal_endings = [("ieth", "y"), ("th", "")]
    
    def text2int(self, textnum: str) -> str:
        text = textnum.replace('-', ' ')
        words = text.split()
        
        total_result = 0
        current = 0
        output_string = ""
        
        for word in words:
            if word in self.ordinal_words:
                current += self.ordinal_words[word]
            else:
                base_word = word
                for ending, replacement in self.ordinal_endings:
                    if len(base_word) > len(ending) and base_word.endswith(ending):
                        base_word = base_word[:-len(ending)] + replacement
                if base_word in self.numwords:
                    scale, increment = self.numwords[base_word]
                    if scale == 1:
                        current += increment
                    else:
                        current *= scale
                        total_result += current
                        current = 0
                else:
                    if current != 0:
                        total_result += current
                        current = 0
                    output_string += word + " "
        
        if current != 0:
            total_result += current
        
        output_string += str(total_result)
        return output_string
    
    def is_valid_input(self, textnum: str) -> bool:
        text = textnum.replace('-', ' ')
        words = text.split()
        
        for word in words:
            if word in self.ordinal_words:
                continue
            
            base_word = word
            for ending, replacement in self.ordinal_endings:
                if len(base_word) > len(ending) and base_word.endswith(ending):
                    base_word = base_word[:-len(ending)] + replacement
            
            if base_word not in self.numwords:
                return False
        
        return True
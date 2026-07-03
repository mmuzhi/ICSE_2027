class Manacher:
    def __init__(self, input_string):
        self.input_string = input_string

    def palindromic_length(self, center, diff, s):
        n = len(s)
        if center - diff < 0 or center + diff >= n or s[center - diff] != s[center + diff]:
            return 0
        return 1 + self.palindromic_length(center, diff + 1, s)

    def palindromic_string(self):
        if not self.input_string:
            return ""
        
        new_input_string = []
        for i in range(len(self.input_string) - 1):
            new_input_string.append(self.input_string[i])
            new_input_string.append('|')
        new_input_string.append(self.input_string[-1])
        s = ''.join(new_input_string)
        
        max_length = 0
        start = 0
        
        for i in range(len(s)):
            length = self.palindromic_length(i, 1, s)
            if length > max_length:
                max_length = length
                start = i
                
        output_string = []
        for j in range(start - max_length, start + max_length + 1):
            if j >= 0 and j < len(s) and s[j] != '|':
                output_string.append(s[j])
                
        return ''.join(output_string)
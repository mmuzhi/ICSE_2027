class Manacher:
    def __init__(self, input_string):
        self.input_string = input_string

    def palindromic_length(self, center, diff, s):
        if center - diff < 0 or center + diff >= len(s) or s[center - diff] != s[center + diff]:
            return 0
        return 1 + self.palindromic_length(center, diff + 1, s)

    def palindromic_string(self):
        new_input_string = ""
        n = len(self.input_string)
        for i in range(n - 1):
            new_input_string += self.input_string[i] + '|'
        new_input_string += self.input_string[-1]

        max_length = 0
        start = 0

        for i in range(len(new_input_string)):
            length = self.palindromic_length(i, 1, new_input_string)
            if length > max_length:
                max_length = length
                start = i

        output_string = ""
        for idx in range(start - max_length, start + max_length + 1):
            if new_input_string[idx] != '|':
                output_string += new_input_string[idx]

        return output_string
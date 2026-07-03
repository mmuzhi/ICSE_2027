class Manacher:
    def __init__(self, input_string):
        self.input_string = input_string

    def palindromic_length(self, center, diff, new_string):
        n = len(new_string)
        left = center - diff
        right = center + diff
        if left < 0 or right >= n or new_string[left] != new_string[right]:
            return 0
        return 1 + self.palindromic_length(center, diff + 1, new_string)

    def palindromic_string(self):
        s = self.input_string
        if len(s) == 0:
            # Behavior identical to C++: crashes on empty string
            pass

        new_input_string = ""
        for i in range(len(s) - 1):
            new_input_string += s[i] + "|"
        new_input_string += s[-1]

        max_length = 0
        start = 0

        for i in range(len(new_input_string)):
            length = self.palindromic_length(i, 1, new_input_string)
            if length > max_length:
                max_length = length
                start = i

        output_string = ""
        for i in range(start - max_length, start + max_length + 1):
            if new_input_string[i] != '|':
                output_string += new_input_string[i]

        return output_string
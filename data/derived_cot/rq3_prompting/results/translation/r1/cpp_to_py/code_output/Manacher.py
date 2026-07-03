class Manacher:
    def __init__(self, input_string: str) -> None:
        self.input_string = input_string

    def palindromic_length(self, center: int, diff: int, s: str) -> int:
        # left and right indices around center at distance diff
        left = center - diff
        right = center + diff
        if left < 0 or right >= len(s) or s[left] != s[right]:
            return 0
        return 1 + self.palindromic_length(center, diff + 1, s)

    def palindromic_string(self) -> str:
        max_length = 0
        new_input_string = ""
        output_string = ""

        # Insert '|' between characters (and after each character except the last)
        for i in range(len(self.input_string) - 1):
            new_input_string += self.input_string[i] + "|"
        new_input_string += self.input_string[-1]

        start = 0
        for i in range(len(new_input_string)):
            length = self.palindromic_length(i, 1, new_input_string)
            if max_length < length:
                max_length = length
                start = i

        # Reconstruct the palindrome from new_input_string, omitting '|'
        for i in range(start - max_length, start + max_length + 1):
            if new_input_string[i] != '|':
                output_string += new_input_string[i]

        return output_string
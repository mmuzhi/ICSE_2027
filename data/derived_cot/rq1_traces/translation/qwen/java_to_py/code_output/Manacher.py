class Manacher:
    def __init__(self, input_string):
        self.input_string = input_string

    def preprocess(self, s):
        processed_chars = ['|']
        for char in s:
            processed_chars.append(char)
            processed_chars.append('|')
        return ''.join(processed_chars)

    def palindromic_length(self, s, center):
        diff = 1
        while (center - diff >= 0 and center + diff < len(s) and 
               s[center - diff] == s[center + diff]):
            diff += 1
        return diff - 1

    def palindromic_string(self):
        processed_string = self.preprocess(self.input_string)
        max_length = 0
        center_index = 0

        for i in range(len(processed_string)):
            length = self.palindromic_length(processed_string, i)
            if length > max_length:
                max_length = length
                center_index = i

        start_index = center_index - max_length
        end_index = center_index + max_length
        result = processed_string[start_index:end_index+1]
        return result.replace('|', '')

# Example usage:
# manacher = Manacher("ababaxse")
# print(manacher.palindromic_string())  # Output: "aba"
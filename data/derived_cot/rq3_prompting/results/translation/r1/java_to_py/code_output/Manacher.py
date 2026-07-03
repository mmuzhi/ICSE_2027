class Manacher:
    def __init__(self, input_string: str):
        self.input_string = input_string

    def _preprocess(self, s: str) -> str:
        sb = ['|']
        for ch in s:
            sb.append(ch)
            sb.append('|')
        return ''.join(sb)

    def palindromic_length(self, s: str, center: int) -> int:
        diff = 1
        while (center - diff >= 0 and center + diff < len(s)
               and s[center - diff] == s[center + diff]):
            diff += 1
        return diff - 1

    def palindromic_string(self) -> str:
        processed_string = self._preprocess(self.input_string)
        max_length = 0
        center_index = 0

        for i in range(len(processed_string)):
            length = self.palindromic_length(processed_string, i)
            if length > max_length:
                max_length = length
                center_index = i

        start = center_index - max_length
        end = center_index + max_length + 1
        result = processed_string[start:end]
        return result.replace('|', '')


if __name__ == '__main__':
    manacher = Manacher("ababaxse")
    print(manacher.palindromic_string())
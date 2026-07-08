class BoyerMooreSearch:
    def __init__(self, text: str, pattern: str):
        self.text = text
        self.pattern = pattern
        self.textLen = len(text)
        self.patLen = len(pattern)

    def match_in_pattern(self, ch: str) -> int:
        return self.pattern.rfind(ch)

    def mismatch_in_text(self, current_pos: int) -> int:
        for i in range(self.patLen - 1, -1, -1):
            if self.pattern[i] != self.text[current_pos + i]:
                return current_pos + i
        return -1

    def bad_character_heuristic(self) -> list[int]:
        positions = []
        i = 0

        bad_char_heuristic = {}
        for j in range(self.patLen):
            bad_char_heuristic[self.pattern[j]] = j

        if self.patLen == 0:
            return list(range(self.textLen + 1))

        while i <= self.textLen - self.patLen:
            mismatch_index = self.mismatch_in_text(i)
            if mismatch_index == -1:
                positions.append(i)
                i += self.patLen
            else:
                mismatch_char = self.text[mismatch_index]
                match_index = bad_char_heuristic.get(mismatch_char, -1)
                if match_index >= 0:
                    i += max(1, mismatch_index - i - match_index)
                else:
                    i += mismatch_index - i + 1

        return positions
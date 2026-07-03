import re

# Helper functions that mimic C++ default locale behavior (ASCII only)
def to_lowercase(s: str) -> str:
    """Convert uppercase ASCII letters to lowercase; keep other characters unchanged."""
    result = []
    for c in s:
        if 'A' <= c <= 'Z':
            result.append(chr(ord(c) + 32))
        else:
            result.append(c)
    return ''.join(result)


def remove_non_alpha(s: str) -> str:
    """Keep only ASCII alphabetic characters and ASCII whitespace (space, tab, newline, etc.)."""
    whitespace = set(' \t\n\r\f\v')
    result = []
    for c in s:
        if ('a' <= c <= 'z') or ('A' <= c <= 'Z') or c in whitespace:
            result.append(c)
    return ''.join(result)


class NLPDataProcessor2:
    def process_data(self, string_list):
        words_list = []
        for s in string_list:
            # Lowercase, remove non‑alpha/whitespace, then split on whitespace
            processed = to_lowercase(remove_non_alpha(s))
            # split() on whitespace and discards empty strings (matches C++ behavior)
            words = processed.split()
            words_list.append(words)
        return words_list

    def calculate_word_frequency(self, words_list):
        word_frequency = {}
        first_appear = {}   # tracks order of first appearance (1‑based)
        js = 0

        for words in words_list:
            for word in words:
                if word not in word_frequency:
                    js += 1
                    first_appear[word] = js
                word_frequency[word] = word_frequency.get(word, 0) + 1

        # Sort: descending frequency, then ascending first‑appearance index
        sorted_items = sorted(
            word_frequency.items(),
            key=lambda x: (-x[1], first_appear[x[0]])
        )

        # Keep top 5 (or fewer)
        top_5 = sorted_items[:5]

        # Return a dict with keys sorted alphabetically (to match std::map ordering)
        top_5_sorted_by_key = dict(sorted(top_5, key=lambda x: x[0]))
        return top_5_sorted_by_key

    def process(self, string_list):
        words_list = self.process_data(string_list)
        return self.calculate_word_frequency(words_list)
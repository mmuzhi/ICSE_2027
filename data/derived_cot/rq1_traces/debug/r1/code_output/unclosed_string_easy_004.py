import re
from typing import List
from collections import Counter

class Solution:
    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
        # Replace specified punctuation with spaces and convert to lowercase
        normalized = re.sub(r'[.,!?;]', ' ', paragraph.lower())
        # Split into words and filter out banned words
        words = [word for word in normalized.split() if word not in banned]
        # Return the most common word
        return Counter(words).most_common(1)[0][0]
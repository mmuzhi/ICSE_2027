from typing import List
import re
from collections import Counter

class Solution:
    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
        paragraph = re.subn(r"[.,!?;']", ' ', paragraph.lower())[0]
        words = paragraph.split()
        words = [word for word in words if word not in banned]
        return Counter(words).most_common(1)[0][0]
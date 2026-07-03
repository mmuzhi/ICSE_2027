class Solution:
    def capitalizeTitle(self, title: str) -> str:
        words = title.split()
        result = []
        for word in words:
            result.append(word[0].upper() + word[1:].lower())
        return ' '.join(result)
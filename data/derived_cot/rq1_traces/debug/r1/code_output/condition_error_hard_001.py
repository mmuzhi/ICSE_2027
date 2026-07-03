class Solution:
    def palindromePairs(self, words: List[str]) -> List[List[int]]:
        backward, res = {}, set()
        for i, word in enumerate(words):
            backward[word[::-1]] = i

        for i, word in enumerate(words):
            # Case 1: word matches a reversed word (different index)
            if word in backward and backward[word] != i:
                res.add((i, backward[word]))
            
            # Case 2: word is a palindrome and there's an empty string
            if word != "" and "" in backward and word == word[::-1]:
                res.add((i, backward[""]))
                res.add((backward[""], i))
            
            # Case 3: split into prefix and suffix
            for j in range(len(word)):
                # Check suffix can form a pair with reversed suffix and prefix is a palindrome
                if word[j:] in backward and word[:j] == word[:j][::-1]:
                    res.add((backward[word[j:]], i))
                # Check prefix can form a pair with reversed prefix and suffix is a palindrome
                if word[:j] in backward and word[j:] == word[j:][::-1]:
                    res.add((i, backward[word[:j]]))
        
        return [list(pair) for pair in res]
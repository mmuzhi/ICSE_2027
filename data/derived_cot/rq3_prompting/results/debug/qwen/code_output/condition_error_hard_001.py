class Solution:
    def palindromePairs(self, words: List[str]) -> List[List[int]]:
        # Build a dictionary that maps the reversed word to the list of indices
        dic = {}
        for i, word in enumerate(words):
            rev = word[::-1]
            if rev not in dic:
                dic[rev] = []
            dic[rev].append(i)
        
        res = []
        n = len(words)
        
        for i, word in enumerate(words):
            for j in range(len(word) + 1):
                prefix = word[:j]
                suffix = word[j:]
                
                # Case 1: prefix is a palindrome and suffix is in the dictionary
                if prefix == prefix[::-1]:
                    if suffix in dic:
                        for index in dic[suffix]:
                            if index != i:
                                res.append([index, i])
                # Case 2: suffix is a palindrome and prefix is in the dictionary
                if suffix == suffix[::-1]:
                    if prefix in dic:
                        for index in dic[prefix]:
                            if index != i:
                                res.append([i, index])
        
        return res
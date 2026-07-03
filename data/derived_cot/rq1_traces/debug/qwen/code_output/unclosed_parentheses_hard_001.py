from collections import deque

class TextEditor:
    def __init__(self):
        self.stack = []
        self.q = deque([])
        
    def addText(self, text: str) -> None:
        for c in text:
            self.stack.append(c)
        
    def deleteText(self, k: int) -> int:
        i = 0
        while self.stack and i < k:
            self.stack.pop()
            i += 1
        return i
        
    def cursorLeft(self, k: int) -> str:
        while k > 0 and self.stack:
            char = self.stack.pop()
            self.q.append(char)
            k -= 1
        entire_text = ''.join(self.stack) + ''.join(self.q)
        if len(entire_text) < 10:
            return entire_text
        else:
            return entire_text[:10]
            
    def cursorRight(self, k: int) -> str:
        while k > 0 and self.q:
            char = self.q.popleft()
            self.stack.append(char)
            k -= 1
        entire_text = ''.join(self.stack) + ''.join(self.q)
        if len(entire_text) < 10:
            return entire_text
        else:
            return entire_text[:10]
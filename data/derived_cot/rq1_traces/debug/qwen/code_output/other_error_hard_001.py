from collections import deque

class TextEditor:
    def __init__(self):
        self.stack = []
        self.q = deque([])
        
    def addText(self, text: str) -> None:
        self.stack.extend(text)
        
    def deleteText(self, k: int) -> int:
        i = 0
        while self.stack and i < k:
            self.stack.pop()
            i += 1
        return i
        
    def cursorLeft(self, k: int) -> str:
        i = 0
        while self.q and i < k:
            char = self.q.popleft()
            self.stack.append(char)
            i += 1
        return "".join(self.stack + self.q)[-10:] if len(self.stack + self.q) >= 10 else "".join(self.stack + self.q)
        
    def cursorRight(self, k: int) -> str:
        i = 0
        while self.stack and i < k:
            char = self.stack.pop()
            self.q.append(char)
            i += 1
        return "".join(self.stack + self.q)[-10:] if len(self.stack + self.q) >= 10 else "".join(self.stack + self.q)
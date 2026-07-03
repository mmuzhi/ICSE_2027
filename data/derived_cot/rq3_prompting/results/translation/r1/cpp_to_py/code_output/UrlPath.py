class UrlPath:
    def __init__(self):
        self.segments = []
        self._with_end_tag = False

    def add(self, segment: str) -> None:
        self.segments.append(self.fix_path(segment))

    def parse(self, path: str, charset: str) -> None:
        if path:
            if path[-1] == '/':
                self._with_end_tag = True

            fixed_path = self.fix_path(path)
            if fixed_path:
                for segment in fixed_path.split('/'):
                    decoded_seg = ""
                    for ch in segment:
                        if ch == '%':
                            pass  # skip '%' character
                        else:
                            # replicate static_cast<char>(wchar_t): low byte of code point
                            decoded_seg += chr(ord(ch) & 0xFF)
                    self.segments.append(decoded_seg)

    @staticmethod
    def fix_path(path: str) -> str:
        if not path:
            return ""
        if path[0] == '/':
            path = path[1:]
        if path and path[-1] == '/':
            path = path[:-1]
        return path

    def get_segments(self):
        # Return a copy to prevent external modification (C++ const reference behavior)
        return self.segments[:]

    def with_end_tag(self) -> bool:
        return self._with_end_tag
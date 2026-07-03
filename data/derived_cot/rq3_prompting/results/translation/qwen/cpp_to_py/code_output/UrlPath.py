import re


class UrlPath:
    def __init__(self):
        self.segments = []
        self._with_end_tag = False

    def add(self, segment):
        self.segments.append(self._fix_path(segment))

    def parse(self, path, charset):
        if path:
            if path[-1] == '/':
                self._with_end_tag = True

            fixed_path = self._fix_path(path)
            if fixed_path:
                segments = fixed_path.split('/')
                for seg in segments:
                    decoded_seg = ''
                    for char in seg:
                        if char != '%':
                            decoded_seg += char
                    self.segments.append(decoded_seg)

    @staticmethod
    def _fix_path(path):
        if not path:
            return ""
        fixed = path
        if fixed.startswith('/'):
            fixed = fixed[1:]
        if fixed.endswith('/'):
            fixed = fixed[:-1]
        return fixed

    def get_segments(self):
        return self.segments

    def with_end_tag(self):
        return self._with_end_tag
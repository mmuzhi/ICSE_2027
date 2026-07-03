class UrlPath:
    def __init__(self):
        self.segments = []
        self._with_end_tag = False

    def add(self, segment):
        self.segments.append(UrlPath.fix_path(segment))

    def parse(self, path, charset):
        if path:
            if path[-1] == '/':
                self._with_end_tag = True

            fixed_path = UrlPath.fix_path(path)
            if fixed_path:
                for segment in fixed_path.split('/'):
                    decoded_seg = ''.join(ch for ch in segment if ch != '%')
                    self.segments.append(decoded_seg)

    @staticmethod
    def fix_path(path):
        if not path:
            return ""
        segment_str = path
        if segment_str.startswith('/'):
            segment_str = segment_str[1:]
        if segment_str.endswith('/'):
            segment_str = segment_str[:-1]
        return segment_str

    def get_segments(self):
        return self.segments

    def with_end_tag(self):
        return self._with_end_tag
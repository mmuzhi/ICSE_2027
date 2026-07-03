class UrlPath:
    def __init__(self):
        self.segments = []  # list of bytes
        self._with_end_tag = False

    def add(self, segment):
        fixed = self.fix_path(segment)
        self.segments.append(fixed)

    def parse(self, path, charset):
        if not path:
            return
        
        if path.endswith(b'/'):
            self._with_end_tag = True
        
        fixed_path = self.fix_path(path)
        if fixed_path == b"":
            seg_list = [b""]
        else:
            seg_list = fixed_path.split(b'/')
        
        for seg in seg_list:
            try:
                unicode_seg = seg.decode('utf-8')
            except UnicodeDecodeError as e:
                raise e
            clean_unicode = unicode_seg.replace('%', '')
            byte_vals = [ord(c) & 0xFF for c in clean_unicode]
            decoded_seg = bytes(byte_vals)
            self.segments.append(decoded_seg)

    @staticmethod
    def fix_path(path):
        if path == b"":
            return b""
        if path.startswith(b'/'):
            path = path[1:]
        if path.endswith(b'/'):
            path = path[:-1]
        return path

    def get_segments(self):
        return self.segments

    def with_end_tag(self):
        return self._with_end_tag
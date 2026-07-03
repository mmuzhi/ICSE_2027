class UrlPath:
    def __init__(self):
        self.segments = []
        self.withEndTag = False

    def add(self, segment):
        fixed_segment = self._fix_path(segment)
        if fixed_segment is not None:
            self.segments.append(fixed_segment)

    def parse(self, path, charset):
        if path is not None and path != "":
            if path.endswith("/"):
                self.withEndTag = True
            fixed_path = self._fix_path(path)
            if fixed_path is not None and fixed_path != "":
                segments = fixed_path.split("/")
                for seg in segments:
                    try:
                        decoded_seg = seg.decode(charset) if isinstance(seg, bytes) else seg
                        self.segments.append(decoded_seg)
                    except Exception as e:
                        import traceback
                        traceback.print_exc()

    @staticmethod
    def _fix_path(path):
        if path is None or path == "":
            return ""
        path_stripped = path.strip()
        path_stripped = path_stripped.replace("^/+|/+$", "", 1).strip()
        return path_stripped

    def get_segments(self):
        return self.segments

    def is_with_end_tag(self):
        return self.withEndTag
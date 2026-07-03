import urllib.parse

class UrlPath:
    def __init__(self):
        self.segments = []
        self.with_end_tag = False

    def add(self, segment):
        fixed_segment = self.fix_path(segment)
        self.segments.append(fixed_segment)

    def parse(self, path, charset):
        if path is not None and path != "":
            if path.endswith('/'):
                self.with_end_tag = True

            fixed_path = self.fix_path(path)
            if fixed_path != "" and fixed_path is not None:
                segments = fixed_path.split('/')
                for seg in segments:
                    try:
                        decoded_seg = urllib.parse.unquote(seg, encoding=charset)
                        self.segments.append(decoded_seg)
                    except Exception as e:
                        import traceback
                        traceback.print_exc()

    @staticmethod
    def fix_path(path):
        if path is None or path == "":
            return ""
        path_stripped = path.strip()
        if path_stripped == "":
            return ""
        return path_stripped.lstrip('/').rstrip('/')

    def get_segments(self):
        return self.segments

    def is_with_end_tag(self):
        return self.with_end_tag
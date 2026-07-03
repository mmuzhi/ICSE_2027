import urllib.parse
import traceback

class UrlPath:
    def __init__(self):
        self.segments = []
        self.withEndTag = False

    def add(self, segment):
        fixed_segment = self.fixPath(segment)
        self.segments.append(fixed_segment)

    def parse(self, path, charset):
        if path is not None and path != '':
            if path.endswith('/'):
                self.withEndTag = True
            fixed_path = self.fixPath(path)
            if fixed_path != '':
                split_segments = fixed_path.split('/')
                for seg in split_segments:
                    try:
                        decoded_seg = urllib.parse.unquote(seg, encoding=charset)
                        self.segments.append(decoded_seg)
                    except Exception:
                        traceback.print_exc()

    @staticmethod
    def fixPath(path):
        if path is None or path == '':
            return ''
        path = path.strip()
        path = path.lstrip('/')
        path = path.rstrip('/')
        return path

    def getSegments(self):
        return self.segments

    def isWithEndTag(self):
        return self.withEndTag
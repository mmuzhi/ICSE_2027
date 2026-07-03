import urllib.parse
import re
import traceback

class UrlPath:
    def __init__(self):
        self.segments = []
        self.withEndTag = False

    def add(self, segment):
        self.segments.append(self.fixPath(segment))

    def parse(self, path, charset):
        if path is not None and path != "":
            if path.endswith("/"):
                self.withEndTag = True
            path = self.fixPath(path)
            if path is not None and path != "":
                for seg in path.split("/"):
                    try:
                        decoded_seg = urllib.parse.unquote(seg, encoding=charset)
                        self.segments.append(decoded_seg)
                    except Exception:
                        traceback.print_exc()

    @staticmethod
    def fixPath(path):
        if path is None or path == "":
            return ""
        segment_str = path.strip()
        segment_str = re.sub(r'^/+|/+$', '', segment_str)
        return segment_str

    def getSegments(self):
        return self.segments

    def isWithEndTag(self):
        return self.withEndTag
import re
import traceback
from urllib.parse import unquote_to_bytes


class UrlPath:
    def __init__(self):
        self.segments = []
        self.with_end_tag = False

    def add(self, segment: str):
        self.segments.append(UrlPath.fix_path(segment))

    def parse(self, path: str, charset: str):
        if path is not None and path != "":
            if path.endswith("/"):
                self.with_end_tag = True

            path = UrlPath.fix_path(path)
            if path:
                for seg in path.split("/"):
                    try:
                        decoded = unquote_to_bytes(seg).decode(charset)
                        self.segments.append(decoded)
                    except Exception:
                        traceback.print_exc()

    @staticmethod
    def fix_path(path: str) -> str:
        if path is None or path == "":
            return ""
        return re.sub(r'^/+|/+$', '', path.strip())

    def get_segments(self):
        return self.segments

    def is_with_end_tag(self):
        return self.with_end_tag
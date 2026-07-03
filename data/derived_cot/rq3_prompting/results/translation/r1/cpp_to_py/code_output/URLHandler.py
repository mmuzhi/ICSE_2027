class URLHandler:
    def __init__(self, url: str):
        self.url = url

    def get_scheme(self) -> str:
        pos = self.url.find("://")
        if pos != -1:
            return self.url[:pos]
        return ""

    def get_host(self) -> str:
        pos = self.url.find("://")
        if pos != -1:
            without_scheme = self.url[pos + 3:]
            host_end = without_scheme.find("/")
            if host_end != -1:
                return without_scheme[:host_end]
            return without_scheme
        return ""

    def get_path(self) -> str:
        pos = self.url.find("://")
        if pos != -1:
            without_scheme = self.url[pos + 3:]
            host_end = without_scheme.find("/")
            if host_end != -1:
                return without_scheme[host_end:]
        return ""

    def get_query_params(self) -> dict:
        params = {}
        qmark = self.url.find("?")
        hash_pos = self.url.find("#")
        if qmark != -1:
            # Determine the query string exactly as C++ does:
            # If fragment exists and is after the '?', use it as end; otherwise take rest.
            if hash_pos != -1 and hash_pos > qmark:
                query_string = self.url[qmark + 1:hash_pos]
            else:
                query_string = self.url[qmark + 1:]

            if query_string:
                # Split by '&' and then by '=' (last occurrence wins)
                items = []
                for token in query_string.split("&"):
                    eq = token.find("=")
                    if eq != -1:
                        key = token[:eq]
                        value = token[eq + 1:]
                        items.append((key, value))
                # Sort by key to match std::map ordering
                items.sort(key=lambda x: x[0])
                params = dict(items)
        return params

    def get_fragment(self) -> str:
        pos = self.url.find("#")
        if pos != -1:
            return self.url[pos + 1:]
        return ""
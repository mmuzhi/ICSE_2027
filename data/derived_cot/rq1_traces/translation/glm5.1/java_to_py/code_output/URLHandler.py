class URLHandler:
    def __init__(self, url):
        self.url = url

    def getScheme(self):
        scheme_end = self.url.find("://")
        if scheme_end != -1:
            return self.url[:scheme_end]
        return None

    def getHost(self):
        scheme_end = self.url.find("://")
        if scheme_end != -1:
            url_without_scheme = self.url[scheme_end + 3:]
            host_end = url_without_scheme.find("/")
            if host_end != -1:
                return url_without_scheme[:host_end]
            return url_without_scheme
        return None

    def getPath(self):
        scheme_end = self.url.find("://")
        if scheme_end != -1:
            url_without_scheme = self.url[scheme_end + 3:]
            host_end = url_without_scheme.find("/")
            if host_end != -1:
                return url_without_scheme[host_end:]
        return None

    def getQueryParams(self):
        query_start = self.url.find("?")
        fragment_start = self.url.find("#")
        if query_start != -1:
            end = fragment_start if fragment_start != -1 else len(self.url)
            query_string = self.url[query_start + 1:end]
            params = {}
            if query_string:
                param_pairs = query_string.split("&")
                for pair in param_pairs:
                    # Mimic Java's split("=") behavior which discards trailing empty strings
                    key_value = pair.split("=")
                    while len(key_value) > 0 and key_value[-1] == "":
                        key_value.pop()
                    
                    if len(key_value) == 2:
                        params[key_value[0]] = key_value[1]
            return params
        return None

    def getFragment(self):
        fragment_start = self.url.find("#")
        if fragment_start != -1:
            return self.url[fragment_start + 1:]
        return None
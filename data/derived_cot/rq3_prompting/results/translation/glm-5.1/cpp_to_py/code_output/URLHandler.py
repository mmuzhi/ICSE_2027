class URLHandler:
    def __init__(self, url):
        self.url = url

    def get_scheme(self):
        scheme_end = self.url.find("://")
        if scheme_end != -1:
            return self.url[:scheme_end]
        return ""

    def get_host(self):
        scheme_end = self.url.find("://")
        if scheme_end != -1:
            url_without_scheme = self.url[scheme_end + 3:]
            host_end = url_without_scheme.find("/")
            if host_end != -1:
                return url_without_scheme[:host_end]
            return url_without_scheme
        return ""

    def get_path(self):
        scheme_end = self.url.find("://")
        if scheme_end != -1:
            url_without_scheme = self.url[scheme_end + 3:]
            host_end = url_without_scheme.find("/")
            if host_end != -1:
                return url_without_scheme[host_end:]
        return ""

    def get_query_params(self):
        params = {}
        query_start = self.url.find("?")
        fragment_start = self.url.find("#")
        if query_start != -1:
            if fragment_start != -1:
                query_string = self.url[query_start + 1:fragment_start]
            else:
                query_string = self.url[query_start + 1:]
            if query_string:
                pos = query_string.find("&")
                while pos != -1:
                    token = query_string[:pos]
                    equal_pos = token.find("=")
                    if equal_pos != -1:
                        key = token[:equal_pos]
                        value = token[equal_pos + 1:]
                        params[key] = value
                    query_string = query_string[pos + 1:]
                    pos = query_string.find("&")
                equal_pos = query_string.find("=")
                if equal_pos != -1:
                    key = query_string[:equal_pos]
                    value = query_string[equal_pos + 1:]
                    params[key] = value
        return params

    def get_fragment(self):
        fragment_start = self.url.find("#")
        if fragment_start != -1:
            return self.url[fragment_start + 1:]
        return ""
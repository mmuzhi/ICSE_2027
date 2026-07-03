class URLHandler:
    def __init__(self, url: str):
        self.url = url

    def get_scheme(self) -> str:
        scheme_end = self.url.find("://")
        if scheme_end != -1:
            return self.url[:scheme_end]
        return ""

    def get_host(self) -> str:
        scheme_end = self.url.find("://")
        if scheme_end != -1:
            url_without_scheme = self.url[scheme_end + 3:]
            host_end = url_without_scheme.find('/')
            if host_end != -1:
                return url_without_scheme[:host_end]
            return url_without_scheme
        return ""

    def get_path(self) -> str:
        scheme_end = self.url.find("://")
        if scheme_end != -1:
            url_without_scheme = self.url[scheme_end + 3:]
            host_end = url_without_scheme.find('/')
            if host_end != -1:
                return url_without_scheme[host_end:]
        return ""

    def get_query_params(self) -> dict:
        params = {}
        query_start = self.url.find('?')
        if query_start == -1:
            return params
        
        fragment_start = self.url.find('#')
        end_index = fragment_start if fragment_start != -1 else len(self.url)
        query_string = self.url[query_start + 1:end_index]
        
        tokens = query_string.split('&')
        for token in tokens:
            equal_pos = token.find('=')
            if equal_pos != -1:
                key = token[:equal_pos]
                value = token[equal_pos + 1:]
                params[key] = value
        return params

    def get_fragment(self) -> str:
        fragment_start = self.url.find('#')
        if fragment_start != -1:
            return self.url[fragment_start + 1:]
        return ""
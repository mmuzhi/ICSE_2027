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
            host_end = url_without_scheme.find("/")
            if host_end != -1:
                return url_without_scheme[:host_end]
            return url_without_scheme
        return ""

    def get_path(self) -> str:
        scheme_end = self.url.find("://")
        if scheme_end != -1:
            url_without_scheme = self.url[scheme_end + 3:]
            host_end = url_without_scheme.find("/")
            if host_end != -1:
                return url_without_scheme[host_end:]
        return ""

    def get_query_params(self) -> dict:
        params = {}
        query_start = self.url.find("?")
        fragment_start = self.url.find("#")
        
        if query_start != -1:
            # In C++, if fragment_start is npos, substr automatically goes to the end of the string.
            # In Python, a -1 index in slicing drops the last character, so we must handle it explicitly.
            if fragment_start != -1:
                query_string = self.url[query_start + 1 : fragment_start]
            else:
                query_string = self.url[query_start + 1 :]
            
            if query_string:
                # The C++ while loop erasing up to '&' is equivalent to splitting by '&'
                tokens = query_string.split("&")
                for token in tokens:
                    equal_pos = token.find("=")
                    if equal_pos != -1:
                        key = token[:equal_pos]
                        value = token[equal_pos + 1:]
                        params[key] = value
        return params

    def get_fragment(self) -> str:
        fragment_start = self.url.find("#")
        if fragment_start != -1:
            return self.url[fragment_start + 1:]
        return ""
import math

class PageUtil:
    class PageInfo:
        def __init__(self, currentPage, perPage, totalPages, totalItems, hasPrevious, hasNext, data):
            self.currentPage = currentPage
            self.perPage = perPage
            self.totalPages = totalPages
            self.totalItems = totalItems
            self.hasPrevious = hasPrevious
            self.hasNext = hasNext
            self.data = list(data) if data is not None else []
        
        def __eq__(self, other):
            if self is other:
                return True
            if type(other) is not type(self):
                return False
            return (self.currentPage == other.currentPage and
                    self.perPage == other.perPage and
                    self.totalPages == other.totalPages and
                    self.totalItems == other.totalItems and
                    self.hasPrevious == other.hasPrevious and
                    self.hasNext == other.hasNext and
                    self.data == other.data)
        
        def __hash__(self):
            result = self.currentPage
            result = (31 * result + self.perPage) & 0xFFFFFFFF
            result = (31 * result + self.totalPages) & 0xFFFFFFFF
            result = (31 * result + self.totalItems) & 0xFFFFFFFF
            result = (31 * result + (1 if self.hasPrevious else 0)) & 0xFFFFFFFF
            result = (31 * result + (1 if self.hasNext else 0)) & 0xFFFFFFFF
            
            list_hash = 1
            for e in self.data:
                list_hash = (31 * list_hash + e) & 0xFFFFFFFF
            result = (31 * result + list_hash) & 0xFFFFFFFF
            
            if result >= 0x80000000:
                result -= 0x100000000
            return result

    class SearchResult:
        def __init__(self, keyword, totalResults, totalPages, results):
            self.keyword = keyword
            self.totalResults = totalResults
            self.totalPages = totalPages
            self.results = list(results) if results is not None else []
        
        def __eq__(self, other):
            if self is other:
                return True
            if type(other) is not type(self):
                return False
            return (self.keyword == other.keyword and
                    self.totalResults == other.totalResults and
                    self.totalPages == other.totalPages and
                    self.results == other.results)
        
        def __hash__(self):
            h = 0
            for c in self.keyword:
                h = (31 * h + ord(c)) & 0xFFFFFFFF
            h = (31 * h + self.totalResults) & 0xFFFFFFFF
            h = (31 * h + self.totalPages) & 0xFFFFFFFF
            
            list_hash = 1
            for e in self.results:
                list_hash = (31 * list_hash + e) & 0xFFFFFFFF
            h = (31 * h + list_hash) & 0xFFFFFFFF
            
            if h >= 0x80000000:
                h -= 0x100000000
            return h

    def __init__(self, data, pageSize):
        self.data = data
        self.pageSize = pageSize
        self.totalItems = len(data)
        self.totalPages = int(math.ceil(self.totalItems / pageSize))
    
    def getPage(self, pageNumber):
        if pageNumber < 1 or pageNumber > self.totalPages:
            return []
        startIndex = (pageNumber - 1) * self.pageSize
        endIndex = min(startIndex + self.pageSize, self.totalItems)
        return self.data[startIndex:endIndex]
    
    def getPageInfo(self, pageNumber):
        if pageNumber < 1 or pageNumber > self.totalPages:
            return PageUtil.PageInfo(0, self.pageSize, self.totalPages, self.totalItems, False, False, [])
        startIndex = (pageNumber - 1) * self.pageSize
        endIndex = min(startIndex + self.pageSize, self.totalItems)
        pageData = self.data[startIndex:endIndex]
        hasPrevious = pageNumber > 1
        hasNext = pageNumber < self.totalPages
        return PageUtil.PageInfo(
            pageNumber,
            self.pageSize,
            self.totalPages,
            self.totalItems,
            hasPrevious,
            hasNext,
            pageData
        )
    
    def search(self, keyword):
        results = []
        for item in self.data:
            if keyword in str(item):
                results.append(item)
        numResults = len(results)
        numPages = int(math.ceil(numResults / self.pageSize)) if self.pageSize != 0 else 0
        return PageUtil.SearchResult(
            keyword,
            numResults,
            numPages,
            results
        )
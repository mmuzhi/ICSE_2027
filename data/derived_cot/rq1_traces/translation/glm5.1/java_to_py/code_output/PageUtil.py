import math
from typing import List, Optional


def _to_java_int(n):
    """Simulate Java 32-bit signed integer overflow."""
    n = n & 0xFFFFFFFF
    if n >= 0x80000000:
        n -= 0x100000000
    return n


def _java_list_hashcode(lst):
    """Replicate Java's List.hashCode() for List<Integer>."""
    result = 1
    for item in lst:
        result = 31 * result + item  # Integer.hashCode() returns the int value itself
        result = _to_java_int(result)
    return result


def _java_string_hashcode(s):
    """Replicate Java's String.hashCode()."""
    h = 0
    for c in s:
        h = 31 * h + ord(c)
        h = _to_java_int(h)
    return h


class PageInfo:
    def __init__(self, current_page: int, per_page: int, total_pages: int,
                 total_items: int, has_previous: bool, has_next: bool,
                 data: Optional[List[int]] = None):
        self.currentPage = current_page
        self.perPage = per_page
        self.totalPages = total_pages
        self.totalItems = total_items
        self.hasPrevious = has_previous
        self.hasNext = has_next
        self.data = list(data) if data is not None else []

    def __eq__(self, obj):
        if self is obj:
            return True
        if obj is None or type(self) is not type(obj):
            return False
        other = obj
        return (self.currentPage == other.currentPage and
                self.perPage == other.perPage and
                self.totalPages == other.totalPages and
                self.totalItems == other.totalItems and
                self.hasPrevious == other.hasPrevious and
                self.hasNext == other.hasNext and
                self.data == other.data)

    def __hash__(self):
        result = self.currentPage
        result = 31 * result + self.perPage
        result = 31 * result + self.totalPages
        result = 31 * result + self.totalItems
        result = 31 * result + (1 if self.hasPrevious else 0)
        result = 31 * result + (1 if self.hasNext else 0)
        result = 31 * result + _java_list_hashcode(self.data)
        return _to_java_int(result)


class SearchResult:
    def __init__(self, keyword: str, total_results: int, total_pages: int,
                 results: Optional[List[int]] = None):
        self.keyword = keyword
        self.totalResults = total_results
        self.totalPages = total_pages
        self.results = list(results) if results is not None else []

    def __eq__(self, obj):
        if self is obj:
            return True
        if obj is None or type(self) is not type(obj):
            return False
        other = obj
        return (self.totalResults == other.totalResults and
                self.totalPages == other.totalPages and
                self.keyword == other.keyword and
                self.results == other.results)

    def __hash__(self):
        result = _java_string_hashcode(self.keyword)
        result = 31 * result + self.totalResults
        result = 31 * result + self.totalPages
        result = 31 * result + _java_list_hashcode(self.results)
        return _to_java_int(result)


class PageUtil:
    def __init__(self, data: List[int], page_size: int):
        self.data = data
        self.pageSize = page_size
        self.totalItems = len(data)
        self.totalPages = math.ceil(self.totalItems / page_size)

    def getPage(self, page_number: int) -> List[int]:
        if page_number < 1 or page_number > self.totalPages:
            return []
        start_index = (page_number - 1) * self.pageSize
        end_index = min(start_index + self.pageSize, self.totalItems)
        return self.data[start_index:end_index]

    def getPageInfo(self, page_number: int) -> PageInfo:
        if page_number < 1 or page_number > self.totalPages:
            return PageInfo(0, self.pageSize, self.totalPages, self.totalItems, False, False, [])
        start_index = (page_number - 1) * self.pageSize
        end_index = min(start_index + self.pageSize, self.totalItems)
        page_data = self.data[start_index:end_index]
        has_previous = page_number > 1
        has_next = page_number < self.totalPages
        return PageInfo(
            page_number,
            self.pageSize,
            self.totalPages,
            self.totalItems,
            has_previous,
            has_next,
            page_data
        )

    def search(self, keyword: str) -> SearchResult:
        results = [item for item in self.data if keyword in str(item)]
        num_results = len(results)
        num_pages = math.ceil(num_results / self.pageSize)
        return SearchResult(
            keyword,
            num_results,
            num_pages,
            results
        )
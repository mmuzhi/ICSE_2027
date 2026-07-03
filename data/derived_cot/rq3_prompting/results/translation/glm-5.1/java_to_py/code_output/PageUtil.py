import math
from typing import List, Optional


class PageInfo:
    def __init__(self, current_page: int, per_page: int, total_pages: int,
                 total_items: int, has_previous: bool, has_next: bool,
                 data: Optional[List[int]] = None):
        self.current_page = current_page
        self.per_page = per_page
        self.total_pages = total_pages
        self.total_items = total_items
        self.has_previous = has_previous
        self.has_next = has_next
        self.data = list(data) if data is not None else []

    def __eq__(self, obj):
        if self is obj:
            return True
        if obj is None or type(self) is not type(obj):
            return False
        other = obj
        return (self.current_page == other.current_page and
                self.per_page == other.per_page and
                self.total_pages == other.total_pages and
                self.total_items == other.total_items and
                self.has_previous == other.has_previous and
                self.has_next == other.has_next and
                self.data == other.data)

    def __hash__(self):
        result = self.current_page
        result = 31 * result + self.per_page
        result = 31 * result + self.total_pages
        result = 31 * result + self.total_items
        result = 31 * result + (1 if self.has_previous else 0)
        result = 31 * result + (1 if self.has_next else 0)
        result = 31 * result + hash(tuple(self.data))
        return result


class SearchResult:
    def __init__(self, keyword: str, total_results: int, total_pages: int,
                 results: Optional[List[int]] = None):
        self.keyword = keyword
        self.total_results = total_results
        self.total_pages = total_pages
        self.results = list(results) if results is not None else []

    def __eq__(self, obj):
        if self is obj:
            return True
        if obj is None or type(self) is not type(obj):
            return False
        other = obj
        return (self.total_results == other.total_results and
                self.total_pages == other.total_pages and
                self.keyword == other.keyword and
                self.results == other.results)

    def __hash__(self):
        result = hash(self.keyword)
        result = 31 * result + self.total_results
        result = 31 * result + self.total_pages
        result = 31 * result + hash(tuple(self.results))
        return result


class PageUtil:
    def __init__(self, data: List[int], page_size: int):
        self.data = data
        self.page_size = page_size
        self.total_items = len(data)
        self.total_pages = math.ceil(self.total_items / page_size)

    def get_page(self, page_number: int) -> List[int]:
        if page_number < 1 or page_number > self.total_pages:
            return []
        start_index = (page_number - 1) * self.page_size
        end_index = min(start_index + self.page_size, self.total_items)
        return self.data[start_index:end_index]

    def get_page_info(self, page_number: int) -> PageInfo:
        if page_number < 1 or page_number > self.total_pages:
            return PageInfo(0, self.page_size, self.total_pages, self.total_items,
                            False, False, [])
        start_index = (page_number - 1) * self.page_size
        end_index = min(start_index + self.page_size, self.total_items)
        page_data = self.data[start_index:end_index]
        has_previous = page_number > 1
        has_next = page_number < self.total_pages
        return PageInfo(
            page_number,
            self.page_size,
            self.total_pages,
            self.total_items,
            has_previous,
            has_next,
            page_data
        )

    def search(self, keyword: str) -> SearchResult:
        results = [item for item in self.data if keyword in str(item)]
        num_results = len(results)
        num_pages = math.ceil(num_results / self.page_size)
        return SearchResult(
            keyword,
            num_results,
            num_pages,
            results
        )
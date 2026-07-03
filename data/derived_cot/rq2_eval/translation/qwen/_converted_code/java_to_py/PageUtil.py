class PageUtil:
    class PageInfo:
        def __init__(self, current_page, per_page, total_pages, total_items, has_previous, has_next, data):
            self.current_page = current_page
            self.per_page = per_page
            self.total_pages = total_pages
            self.total_items = total_items
            self.has_previous = has_previous
            self.has_next = has_next
            self.data = data.copy() if data is not None else []

        def __eq__(self, other):
            if not isinstance(other, PageUtil.PageInfo):
                return False
            return (
                self.current_page == other.current_page and
                self.per_page == other.per_page and
                self.total_pages == other.total_pages and
                self.total_items == other.total_items and
                self.has_previous == other.has_previous and
                self.has_next == other.has_next and
                self.data == other.data
            )

        def __hash__(self):
            return hash((
                self.current_page,
                self.per_page,
                self.total_pages,
                self.total_items,
                self.has_previous,
                self.has_next,
                tuple(self.data)
            ))

    class SearchResult:
        def __init__(self, keyword, total_results, total_pages, results):
            self.keyword = keyword
            self.total_results = total_results
            self.total_pages = total_pages
            self.results = results.copy() if results is not None else []

        def __eq__(self, other):
            if not isinstance(other, PageUtil.SearchResult):
                return False
            return (
                self.keyword == other.keyword and
                self.total_results == other.total_results and
                self.total_pages == other.total_pages and
                self.results == other.results
            )

        def __hash__(self):
            return hash((
                self.keyword,
                self.total_results,
                self.total_pages,
                tuple(self.results)
            ))

    def __init__(self, data, page_size):
        self.data = list(data)  # Ensure we work with a copy
        self.page_size = page_size
        self.total_items = len(self.data)
        self.total_pages = (self.total_items + page_size - 1) // page_size

    def get_page(self, page_number):
        if page_number < 1 or page_number > self.total_pages:
            return []
        start_index = (page_number - 1) * self.page_size
        end_index = min(start_index + self.page_size, self.total_items)
        return self.data[start_index:end_index]

    def get_page_info(self, page_number):
        if page_number < 1 or page_number > self.total_pages:
            return PageUtil.PageInfo(
                0, self.page_size, self.total_pages, self.total_items,
                False, False, []
            )
        start_index = (page_number - 1) * self.page_size
        end_index = min(start_index + self.page_size, self.total_items)
        page_data = self.data[start_index:end_index]

        has_previous = page_number > 1
        has_next = page_number < self.total_pages

        return PageUtil.PageInfo(
            page_number, self.page_size, self.total_pages, self.total_items,
            has_previous, has_next, page_data
        )

    def search(self, keyword):
        if keyword is None:
            keyword = ""
        results = [item for item in self.data if str(item).find(keyword) != -1]
        num_results = len(results)
        num_pages = (num_results + self.page_size - 1) // self.page_size
        return PageUtil.SearchResult(keyword, num_results, num_pages, results)
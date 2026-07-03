class PageUtil:
    def __init__(self, data, page_size):
        self.data = data
        self.page_size = page_size
        self.total_items = len(data)
        self.total_pages = (self.total_items + page_size - 1) // page_size

    def get_page(self, page_number):
        if page_number < 1 or page_number > self.total_pages:
            return []
        start = (page_number - 1) * self.page_size
        end = start + self.page_size
        if end > self.total_items:
            end = self.total_items
        return self.data[start:end]

    def get_page_info(self, page_number):
        if page_number < 1 or page_number > self.total_pages:
            return {}
        start = (page_number - 1) * self.page_size
        end = start + self.page_size
        if end > self.total_items:
            end = self.total_items
        page_data = self.data[start:end]
        return {
            "current_page": page_number,
            "per_page": self.page_size,
            "total_pages": self.total_pages,
            "total_items": self.total_items,
            "has_previous": page_number > 1,
            "has_next": page_number < self.total_pages,
            "data": page_data
        }

    def search(self, keyword):
        results = []
        for item in self.data:
            if str(item).find(keyword) != -1:
                results.append(item)
        total_results = len(results)
        total_pages = (total_results + self.page_size - 1) // self.page_size
        return {
            "keyword": keyword,
            "total_results": total_results,
            "total_pages": total_pages,
            "results": results
        }
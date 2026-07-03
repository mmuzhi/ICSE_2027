class PageUtil:
    def __init__(self, data, page_size):
        self.data = data
        self.page_size = page_size
        self.total_items = len(data)
        if page_size > 0:
            self.total_pages = (self.total_items + page_size - 1) // page_size
        else:
            self.total_pages = 0

    def get_page(self, page_number):
        if page_number < 1 or page_number > self.total_pages:
            return []
        
        start_index = (page_number - 1) * self.page_size
        end_index = start_index + self.page_size
        if end_index > self.total_items:
            end_index = self.total_items
        
        return self.data[start_index:end_index]

    def get_page_info(self, page_number):
        if page_number < 1 or page_number > self.total_pages:
            return {}
        
        start_index = (page_number - 1) * self.page_size
        end_index = start_index + self.page_size
        if end_index > self.total_items:
            end_index = self.total_items
        page_data = self.data[start_index:end_index]
        
        page_info = {
            "current_page": page_number,
            "per_page": self.page_size,
            "total_pages": self.total_pages,
            "total_items": self.total_items,
            "has_previous": page_number > 1,
            "has_next": page_number < self.total_pages,
            "data": page_data
        }
        return page_info

    def search(self, keyword):
        results = []
        for item in self.data:
            if keyword in str(item):
                results.append(item)
        
        num_results = len(results)
        if self.page_size > 0:
            num_pages = (num_results + self.page_size - 1) // self.page_size
        else:
            num_pages = 0
        
        search_info = {
            "keyword": keyword,
            "total_results": num_results,
            "total_pages": num_pages,
            "results": results
        }
        return search_info
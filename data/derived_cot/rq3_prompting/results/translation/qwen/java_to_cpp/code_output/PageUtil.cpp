#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <optional>
#include <functional>

namespace org::example {

class PageUtil {
public:
    using PageData = std::vector<int>;
    using PageInfo = struct PageInfo {
        int currentPage;
        int perPage;
        int totalPages;
        int totalItems;
        bool hasPrevious;
        bool hasNext;
        PageData data;

        PageInfo(int currentPage, int perPage, int totalPages, int totalItems, bool hasPrevious, bool hasNext, const PageData& data)
            : currentPage(currentPage), perPage(perPage), totalPages(totalPages), totalItems(totalItems),
              hasPrevious(hasPrevious), hasNext(hasNext), data(data) {}
    };

    using SearchResult = struct SearchResult {
        std::string keyword;
        int totalResults;
        int totalPages;
        PageData results;

        SearchResult(const std::string& keyword, int totalResults, int totalPages, const PageData& results)
            : keyword(keyword), totalResults(totalResults), totalPages(totalPages), results(results) {}
    };

    PageUtil(PageData data, int pageSize)
        : data(std::move(data)), pageSize(pageSize), totalItems(data.size()),
          totalPages((totalItems + pageSize - 1) / pageSize) {}

    PageData getPage(int pageNumber) {
        if (pageNumber < 1 || pageNumber > totalPages) {
            return PageData();
        }
        int startIndex = (pageNumber - 1) * pageSize;
        int endIndex = std::min(startIndex + pageSize, totalItems);
        PageData result(data.begin() + startIndex, data.begin() + endIndex);
        return result;
    }

    PageInfo getPageInfo(int pageNumber) {
        if (pageNumber < 1 || pageNumber > totalPages) {
            return PageInfo(0, pageSize, totalPages, totalItems, false, false, PageData());
        }
        int startIndex = (pageNumber - 1) * pageSize;
        int endIndex = std::min(startIndex + pageSize, totalItems);
        PageData pageData(data.begin() + startIndex, data.begin() + endIndex);
        bool hasPrevious = pageNumber > 1;
        bool hasNext = pageNumber < totalPages;
        return PageInfo(pageNumber, pageSize, totalPages, totalItems, hasPrevious, hasNext, std::move(pageData));
    }

    SearchResult search(const std::string& keyword) {
        auto results = data;
        auto it = std::remove_if(results.begin(), results.end(), [&keyword](int item) {
            return std::string(std::to_string(item)).find(keyword) == std::string::npos;
        });
        results.erase(it, results.end());
        int numResults = results.size();
        int numPages = (numResults + pageSize - 1) / pageSize;
        return SearchResult(keyword, numResults, numPages, std::move(results));
    }

private:
    PageData data;
    int pageSize;
    int totalItems;
    int totalPages;
};

} // namespace org::example

#endif // ORG_EXAMPLE_PAGE_UTIL_HPP
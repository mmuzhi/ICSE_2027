#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

class PageUtil {
public:
    struct PageInfo {
        int currentPage;
        int perPage;
        int totalPages;
        int totalItems;
        bool hasPrevious;
        bool hasNext;
        std::vector<int> data;

        PageInfo(int currentPage, int perPage, int totalPages, int totalItems,
                 bool hasPrevious, bool hasNext, const std::vector<int>& data)
            : currentPage(currentPage), perPage(perPage), totalPages(totalPages),
              totalItems(totalItems), hasPrevious(hasPrevious), hasNext(hasNext),
              data(data) {}

        bool operator==(const PageInfo& other) const {
            return currentPage == other.currentPage &&
                   perPage == other.perPage &&
                   totalPages == other.totalPages &&
                   totalItems == other.totalItems &&
                   hasPrevious == other.hasPrevious &&
                   hasNext == other.hasNext &&
                   data == other.data;
        }

        int hashCode() const {
            int result = currentPage;
            result = 31 * result + perPage;
            result = 31 * result + totalPages;
            result = 31 * result + totalItems;
            result = 31 * result + (hasPrevious ? 1 : 0);
            result = 31 * result + (hasNext ? 1 : 0);
            int dataHash = 1;
            for (int item : data) {
                dataHash = 31 * dataHash + item;
            }
            result = 31 * result + dataHash;
            return result;
        }
    };

    struct SearchResult {
        std::string keyword;
        int totalResults;
        int totalPages;
        std::vector<int> results;

        SearchResult(const std::string& keyword, int totalResults, int totalPages,
                     const std::vector<int>& results)
            : keyword(keyword), totalResults(totalResults), totalPages(totalPages),
              results(results) {}

        bool operator==(const SearchResult& other) const {
            return totalResults == other.totalResults &&
                   totalPages == other.totalPages &&
                   keyword == other.keyword &&
                   results == other.results;
        }

        int hashCode() const {
            int keywordHash = 0;
            for (char c : keyword) {
                keywordHash = 31 * keywordHash + static_cast<int>(c);
            }
            int result = keywordHash;
            result = 31 * result + totalResults;
            result = 31 * result + totalPages;
            int resultsHash = 1;
            for (int item : results) {
                resultsHash = 31 * resultsHash + item;
            }
            result = 31 * result + resultsHash;
            return result;
        }
    };

private:
    std::vector<int> data;
    int pageSize;
    int totalItems;
    int totalPages;

public:
    PageUtil(const std::vector<int>& data, int pageSize)
        : data(data), pageSize(pageSize),
          totalItems(static_cast<int>(data.size())),
          totalPages(static_cast<int>(std::ceil(static_cast<double>(totalItems) / pageSize))) {}

    std::vector<int> getPage(int pageNumber) {
        if (pageNumber < 1 || pageNumber > totalPages) {
            return std::vector<int>();
        }
        int startIndex = (pageNumber - 1) * pageSize;
        int endIndex = std::min(startIndex + pageSize, totalItems);
        return std::vector<int>(data.begin() + startIndex, data.begin() + endIndex);
    }

    PageInfo getPageInfo(int pageNumber) {
        if (pageNumber < 1 || pageNumber > totalPages) {
            return PageInfo(0, pageSize, totalPages, totalItems, false, false, std::vector<int>());
        }
        int startIndex = (pageNumber - 1) * pageSize;
        int endIndex = std::min(startIndex + pageSize, totalItems);
        std::vector<int> pageData(data.begin() + startIndex, data.begin() + endIndex);
        bool hasPrevious = pageNumber > 1;
        bool hasNext = pageNumber < totalPages;
        return PageInfo(pageNumber, pageSize, totalPages, totalItems, hasPrevious, hasNext, pageData);
    }

    SearchResult search(const std::string& keyword) {
        std::vector<int> results;
        for (int item : data) {
            if (std::to_string(item).find(keyword) != std::string::npos) {
                results.push_back(item);
            }
        }
        int numResults = static_cast<int>(results.size());
        int numPages = static_cast<int>(std::ceil(static_cast<double>(numResults) / pageSize));
        return SearchResult(keyword, numResults, numPages, results);
    }
};
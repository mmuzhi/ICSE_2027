#ifndef PAGE_UTIL_H
#define PAGE_UTIL_H

#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

class PageUtil {
public:
    class PageInfo {
    public:
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
            result = 31 * result + listHashCode(data);
            return result;
        }

    private:
        static int listHashCode(const std::vector<int>& list) {
            int h = 1;
            for (int e : list) {
                h = 31 * h + e;
            }
            return h;
        }
    };

    class SearchResult {
    public:
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
            int result = stringHashCode(keyword);
            result = 31 * result + totalResults;
            result = 31 * result + totalPages;
            result = 31 * result + listHashCode(results);
            return result;
        }

    private:
        static int stringHashCode(const std::string& s) {
            int h = 0;
            for (char c : s) {
                h = 31 * h + c;
            }
            return h;
        }

        static int listHashCode(const std::vector<int>& list) {
            int h = 1;
            for (int e : list) {
                h = 31 * h + e;
            }
            return h;
        }
    };

private:
    std::vector<int> data_;
    int pageSize_;
    int totalItems_;
    int totalPages_;

public:
    PageUtil(const std::vector<int>& data, int pageSize)
        : data_(data), pageSize_(pageSize),
          totalItems_(static_cast<int>(data.size())),
          totalPages_(static_cast<int>(std::ceil(static_cast<double>(totalItems_) / pageSize_))) {}

    std::vector<int> getPage(int pageNumber) {
        if (pageNumber < 1 || pageNumber > totalPages_) {
            return std::vector<int>();
        }

        int startIndex = (pageNumber - 1) * pageSize_;
        int endIndex = std::min(startIndex + pageSize_, totalItems_);
        return std::vector<int>(data_.begin() + startIndex, data_.begin() + endIndex);
    }

    PageInfo getPageInfo(int pageNumber) {
        if (pageNumber < 1 || pageNumber > totalPages_) {
            return PageInfo(0, pageSize_, totalPages_, totalItems_, false, false, std::vector<int>());
        }

        int startIndex = (pageNumber - 1) * pageSize_;
        int endIndex = std::min(startIndex + pageSize_, totalItems_);
        std::vector<int> pageData(data_.begin() + startIndex, data_.begin() + endIndex);

        bool hasPrevious = pageNumber > 1;
        bool hasNext = pageNumber < totalPages_;

        return PageInfo(
            pageNumber,
            pageSize_,
            totalPages_,
            totalItems_,
            hasPrevious,
            hasNext,
            pageData
        );
    }

    SearchResult search(const std::string& keyword) {
        std::vector<int> results;
        for (int item : data_) {
            if (std::to_string(item).find(keyword) != std::string::npos) {
                results.push_back(item);
            }
        }

        int numResults = static_cast<int>(results.size());
        int numPages = static_cast<int>(std::ceil(static_cast<double>(numResults) / pageSize_));

        return SearchResult(
            keyword,
            numResults,
            numPages,
            results
        );
    }
};

#endif // PAGE_UTIL_H
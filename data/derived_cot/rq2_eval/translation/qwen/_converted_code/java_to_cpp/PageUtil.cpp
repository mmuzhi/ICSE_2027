#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <utility>

namespace org {
    namespace example {

        class PageUtil {
        private:
            std::vector<int> data;
            int pageSize;
            int totalItems;
            int totalPages;

        public:
            explicit PageUtil(const std::vector<int>& data, int pageSize) {
                this->data = data;
                this->pageSize = pageSize;
                this->totalItems = data.size();
                this->totalPages = (int) std::ceil(static_cast<double>(totalItems) / pageSize);
            }

            std::vector<int> getPage(int pageNumber) {
                if (pageNumber < 1 || pageNumber > totalPages) {
                    return std::vector<int>();
                }

                int startIndex = (pageNumber - 1) * pageSize;
                int endIndex = std::min(startIndex + pageSize, totalItems);
                std::vector<int> pageData(data.begin() + startIndex, data.begin() + endIndex);
                return pageData;
            }

            struct PageInfo {
                int currentPage;
                int perPage;
                int totalPages;
                int totalItems;
                bool hasPrevious;
                bool hasNext;
                std::vector<int> data;

                PageInfo(int currentPage, int perPage, int totalPages, int totalItems, bool hasPrevious, bool hasNext, const std::vector<int>& data)
                    : currentPage(currentPage),
                      perPage(perPage),
                      totalPages(totalPages),
                      totalItems(totalItems),
                      hasPrevious(hasPrevious),
                      hasNext(hasNext),
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
            };

            std::vector<PageInfo> getPageInfo(int pageNumber) {
                if (pageNumber < 1 || pageNumber > totalPages) {
                    return { PageInfo(0, pageSize, totalPages, totalItems, false, false, std::vector<int>()) };
                }

                int startIndex = (pageNumber - 1) * pageSize;
                int endIndex = std::min(startIndex + pageSize, totalItems);
                std::vector<int> pageData(data.begin() + startIndex, data.begin() + endIndex);

                bool hasPrevious = (pageNumber > 1);
                bool hasNext = (pageNumber < totalPages);

                return { PageInfo(pageNumber, pageSize, totalPages, totalItems, hasPrevious, hasNext, pageData) };
            }

            struct SearchResult {
                std::string keyword;
                int totalResults;
                int totalPages;
                std::vector<int> results;

                SearchResult(const std::string& keyword, int totalResults, int totalPages, const std::vector<int>& results)
                    : keyword(keyword),
                      totalResults(totalResults),
                      totalPages(totalPages),
                      results(results) {}

                bool operator==(const SearchResult& other) const {
                    return keyword == other.keyword &&
                           totalResults == other.totalResults &&
                           totalPages == other.totalPages &&
                           results == other.results;
                }
            };

            SearchResult search(const std::string& keyword) {
                std::vector<int> results;
                for (int item : data) {
                    if (std::to_string(item).find(keyword) != std::string::npos) {
                        results.push_back(item);
                    }
                }

                int numResults = results.size();
                int numPages = (int) std::ceil(static_cast<double>(numResults) / pageSize);

                return SearchResult(keyword, numResults, numPages, results);
            }
        };

    } // namespace example
} // namespace org

// For equality and hash in C++11 and later
namespace std {
    template<>
    struct hash<org::example::PageInfo> {
        size_t operator()(const org::example::PageInfo& pageInfo) const {
            size_t result = pageInfo.currentPage;
            result ^= pageInfo.perPage << 1;
            result ^= pageInfo.totalPages << 2;
            result ^= pageInfo.totalItems << 3;
            result ^= (pageInfo.hasPrevious ? 1 : 0) << 4;
            result ^= (pageInfo.hasNext ? 1 : 0) << 5;
            std::hash<std::vector<int>> hasher;
            result ^= hasher(pageInfo.data) << 6;
            return result;
        }
    };

    template<>
    struct hash<org::example::SearchResult> {
        size_t operator()(const org::example::SearchResult& searchResult) const {
            size_t result = std::hash<std::string>{}(searchResult.keyword);
            result ^= searchResult.totalResults << 1;
            result ^= searchResult.totalPages << 2;
            std::hash<std::vector<int>> hasher;
            result ^= hasher(searchResult.results) << 3;
            return result;
        }
    };
}
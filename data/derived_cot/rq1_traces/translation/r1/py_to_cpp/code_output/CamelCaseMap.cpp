#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <any>
#include <stdexcept>

class CamelCaseMap {
private:
    std::map<std::string, std::any> _data;

    class Proxy {
    public:
        Proxy(CamelCaseMap& map, const std::string& key)
            : map_(map), key_(key) {}

        operator std::any&() {
            return map_.at(key_);
        }

        Proxy& operator=(const std::any& value) {
            map_.set(key_, value);
            return *this;
        }

    private:
        CamelCaseMap& map_;
        std::string key_;
    };

    class ConstProxy {
    public:
        ConstProxy(const CamelCaseMap& map, const std::string& key)
            : map_(map), key_(key) {}

        operator const std::any&() const {
            return map_.at(key_);
        }

    private:
        const CamelCaseMap& map_;
        std::string key_;
    };

    class key_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::string;
        using difference_type = std::ptrdiff_t;
        using pointer = const std::string*;
        using reference = const std::string&;

        key_iterator() = default;
        explicit key_iterator(typename std::map<std::string, std::any>::const_iterator it)
            : it_(it) {}

        reference operator*() const { return it_->first; }
        pointer operator->() const { return &it_->first; }

        key_iterator& operator++() { ++it_; return *this; }
        key_iterator operator++(int) { key_iterator tmp = *this; ++it_; return tmp; }

        friend bool operator==(const key_iterator& a, const key_iterator& b) {
            return a.it_ == b.it_;
        }
        friend bool operator!=(const key_iterator& a, const key_iterator& b) {
            return a.it_ != b.it_;
        }

    private:
        typename std::map<std::string, std::any>::const_iterator it_;
    };

    static std::string _to_camel_case(const std::string& key) {
        if (key.empty()) {
            return "";
        }
        std::istringstream iss(key);
        std::string part;
        std::vector<std::string> parts;
        while (std::getline(iss, part, '_')) {
            parts.push_back(part);
        }
        if (parts.empty()) {
            return "";
        }
        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); ++i) {
            if (parts[i].empty()) {
                continue;
            }
            std::string transformed = parts[i];
            transformed[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(transformed[0])));
            for (size_t j = 1; j < transformed.size(); ++j) {
                transformed[j] = static_cast<char>(std::tolower(static_cast<unsigned char>(transformed[j])));
            }
            result += transformed;
        }
        return result;
    }

    std::string _convert_key(const std::string& key) const {
        return _to_camel_case(key);
    }

    void set(const std::string& key, const std::any& value) {
        std::string converted = _convert_key(key);
        _data[converted] = value;
    }

public:
    Proxy operator[](const std::string& key) {
        return Proxy(*this, key);
    }

    ConstProxy operator[](const std::string& key) const {
        return ConstProxy(*this, key);
    }

    std::any& at(const std::string& key) {
        std::string converted = _convert_key(key);
        return _data.at(converted);
    }

    const std::any& at(const std::string& key) const {
        std::string converted = _convert_key(key);
        return _data.at(converted);
    }

    void erase(const std::string& key) {
        std::string converted = _convert_key(key);
        _data.erase(converted);
    }

    size_t size() const {
        return _data.size();
    }

    key_iterator begin() const {
        return key_iterator(_data.begin());
    }

    key_iterator end() const {
        return key_iterator(_data.end());
    }
};
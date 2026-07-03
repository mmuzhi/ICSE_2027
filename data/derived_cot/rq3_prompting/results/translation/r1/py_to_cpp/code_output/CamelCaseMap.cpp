#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iterator>

class CamelCaseMap {
public:
    // ------------------------------------------------------------
    // Proxy class for operator[] (non-const): supports get and set.
    // ------------------------------------------------------------
    class Proxy {
    public:
        Proxy(CamelCaseMap* m, const std::string& k) : map_(m), key_(k) {}

        // set: map_["key"] = value
        Proxy& operator=(const std::string& value) {
            map_->set(key_, value);
            return *this;
        }

        // get: std::string val = map_["key"]
        operator std::string() const {
            return map_->get(key_);
        }

    private:
        CamelCaseMap* map_;
        std::string key_;
    };

    // ------------------------------------------------------------
    // Const proxy – only reading allowed.
    // ------------------------------------------------------------
    class ConstProxy {
    public:
        ConstProxy(const CamelCaseMap* m, const std::string& k) : map_(m), key_(k) {}

        operator std::string() const {
            return map_->get(key_);
        }

    private:
        const CamelCaseMap* map_;
        std::string key_;
    };

    // ------------------------------------------------------------
    // Iterator over keys (camelCase).
    // ------------------------------------------------------------
    class KeyIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::string;
        using difference_type = std::ptrdiff_t;
        using pointer = const std::string*;
        using reference = const std::string&;

        KeyIterator(std::map<std::string, std::string>::const_iterator it) : it_(it) {}

        reference operator*() const { return it_->first; }
        pointer operator->() const { return &(it_->first); }

        KeyIterator& operator++() { ++it_; return *this; }
        KeyIterator operator++(int) { KeyIterator tmp = *this; ++it_; return tmp; }

        bool operator==(const KeyIterator& other) const { return it_ == other.it_; }
        bool operator!=(const KeyIterator& other) const { return it_ != other.it_; }

    private:
        std::map<std::string, std::string>::const_iterator it_;
    };

    // ------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------
    CamelCaseMap() = default;

    // ------------------------------------------------------------
    // Public interface (mimicking Python dunders)
    // ------------------------------------------------------------
    // __getitem__ and __setitem__ via operator[]
    Proxy operator[](const std::string& key) {
        return Proxy(this, key);
    }
    ConstProxy operator[](const std::string& key) const {
        return ConstProxy(this, key);
    }

    // __delitem__
    void del(const std::string& key) {
        std::string camel = convert_key(key);
        auto it = data_.find(camel);
        if (it == data_.end()) {
            throw std::out_of_range("Key not found: " + key);
        }
        data_.erase(it);
    }

    // __len__
    size_t size() const {
        return data_.size();
    }

    // __iter__ (range-for support)
    KeyIterator begin() const {
        return KeyIterator(data_.cbegin());
    }
    KeyIterator end() const {
        return KeyIterator(data_.cend());
    }

    // ------------------------------------------------------------
    // Internal helpers
    // ------------------------------------------------------------
private:
    // Access with conversion, throws if not found
    std::string get(const std::string& key) const {
        std::string camel = convert_key(key);
        auto it = data_.find(camel);
        if (it == data_.end()) {
            throw std::out_of_range("Key not found: " + key);
        }
        return it->second;
    }

    // Set with conversion (inserts if needed)
    void set(const std::string& key, const std::string& value) {
        data_[convert_key(key)] = value;
    }

    // Convert underscore key to camelCase
    std::string convert_key(const std::string& key) const {
        // In the Python version, if key is not a string it is returned unchanged.
        // Here we assume all keys are std::string.
        return to_camel_case(key);
    }

    static std::string to_camel_case(const std::string& key) {
        // Split by '_'
        std::vector<std::string> parts;
        std::istringstream stream(key);
        std::string part;
        while (std::getline(stream, part, '_')) {
            parts.push_back(part);
        }
        if (parts.empty()) {
            return "";
        }
        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); ++i) {
            if (!parts[i].empty()) {
                result += static_cast<char>(std::toupper(parts[i][0]));
                result += parts[i].substr(1);
            }
        }
        return result;
    }

    std::map<std::string, std::string> data_;
};